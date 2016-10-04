#include <iostream>
#include <vector>
#include <algorithm>

#include <string.h>
#include <stdio.h>
using namespace std;

# define ALONE -1

class Edge{
  int origin, master, distance;

  public:

    Edge(int v, int w, int distance){
      origin = v;
      master = w;
      this->distance = distance;
    }

    int getOrigin(){
      return origin;
    }

    int getMaster(){
      return master;
    }

    int getDistance(){
      return distance;
    }

    bool operator < (const Edge& master) const{
      return (distance < master.distance);
    }
};

class Graph {
  int numberOfVertex;
  int finalResult;

  public:
    vector<Edge> edges;
    vector<Edge> tree;
    vector <int> bestestResult;

    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      edges.clear();
    }

    void addEdge(int origin, int master, int distance) {
      Edge edge(origin, master, distance);
      edges.push_back(edge);
    }

    void addNewWayValor(int newBest){
      bestestResult.push_back(newBest);
      sort(bestestResult.begin(), bestestResult.end());
    }

    int getNumberOfVertex(){
      return this->numberOfVertex;
    }
    
    int getNumberOfEdgesOnTree(){
      return tree.size();
    }

    int getResult(){
      return finalResult;
    }

    int getSecondResult(){
      return bestestResult[0];
    }
    
    int search(int subset[], int i){
      if(subset[i] == ALONE)
        return i;
      return search(subset, subset[i]);
    }

    void junction(int subset[], int origin, int master) {
      int origin_set = search(subset, origin);
      int master_set = search(subset, master);
      subset[origin_set] = master_set;
    }

    void kruskal() {
      tree.clear();
      int size_subset;
      int size_edges = edges.size();

      sort(edges.begin(), edges.end());

      if(size_edges > numberOfVertex){
        size_subset = size_edges+1;
      } else {
        size_subset = numberOfVertex+1;
      }

      int *subset = new int[size_subset];

      memset(subset, ALONE, sizeof(int) * (size_subset));

      for(int i = 0; i < size_edges; i++) {
        int origin = search(subset, edges[i].getOrigin());
        int master = search(subset, edges[i].getMaster());

        if(origin != master) {
          tree.push_back(edges[i]);
          junction(subset, origin, master);
        }
      }
      int size_tree = tree.size();
      int result = 0;

      for(int i = 0; i < size_tree; i++) {
        result += tree[i].getDistance();
      }
      finalResult = result;
    }

    bool haveMST(){
      if(this->getNumberOfEdgesOnTree() != this->getNumberOfVertex()-1){
        return false;
      } else {
        return true;
      }
    }

    void removeEdge(int edgeToRemove){
      edges.erase(edges.begin() + edgeToRemove);
    }
};

int main(){
  int n, m, input;
  int origin, master, distance;
  int ways;

  scanf("%d", &input);

  for(int test = 1; test <= input; test++){
    scanf("%d %d", &n, &m);

    Graph g(n);

    for(int i = 0; i < m; i++){
      scanf("%d %d %d", &origin, &master, &distance);
      g.addEdge(origin, master, distance);
    }
    g.kruskal();
    
    if(!g.haveMST()){
      ways = 0;
    } else{
      ways = 1;
      for(int edgeTree = 0; edgeTree < g.getNumberOfEdgesOnTree();edgeTree++){
        Graph tryNewWay = g;
        
        tryNewWay.removeEdge(edgeTree);
        tryNewWay.kruskal();
        if(tryNewWay.haveMST()){
          g.addNewWayValor(tryNewWay.getResult());
          ways = 2;
        }
      }
    }
  
    printf("Case #%d : ", test);

    switch(ways){
      case 0:
        printf("No way\n");
      break;

      case 1:
        printf("No second way\n");
      break;

      case 2:
        printf("%d\n", g.getSecondResult());
      break;

      default:
        printf("Opção 3\n");
      break;
    }
  }
  return 0;
}