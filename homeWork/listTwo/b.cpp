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

  public:
    vector<Edge> edges;

    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      edges.clear();
    }

    void addEdge(int origin, int master, int distance) {
      Edge edge(origin, master, distance);
      edges.push_back(edge);
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
      vector<Edge> tree;
      int size_edges = edges.size();

      sort(edges.begin(), edges.end());

      int * subset = new int[edges.size()];

      memset(subset, ALONE, sizeof(int) * edges.size());

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
      printf("%d\n", result);
    }
};

int main(){
  int n, m;
  int origin, master, distance;
  int test = 0;

  scanf("%d %d", &n, &m);

  while(n != 0){    
    test++;
    Graph g(n);

    for(int i = 0; i < m; i++){
      scanf("%d %d %d", &origin, &master, &distance);
      g.addEdge(origin, master, distance);
    }

    g.kruskal();
  
    scanf("%d %d", &n, &m);
  }  return 0;
}