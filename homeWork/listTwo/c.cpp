# include <iostream>
# include <vector>
# include <algorithm>

# include <string.h>
# include <stdio.h>
using namespace std;

# define ALONE -1

class Edge{
  double float origin, master;

  public:

    Edge(double float v, double float w){
      this->origin = v;
      this->master = w;
    }

    int getOrigin(){
      return origin;
    }

    int getMaster(){
      return master;
    }  
};

bool sortOrigin(Edge &origin, Edge &master){
  return (origin.getOrigin() < master.getOrigin());
}

class Graph {
  int numberOfVertex;

  public:
    vector<Edge> edges;

    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      edges.clear();
    }

    void addEdge(double float origin, double float master) {
      Edge edge(origin, master);
      edges.push_back(edge);
    }

    int search(int subset[], int edge){
      if(subset[edge] == ALONE){
        return edge;
      }
      return search(subset, subset[edge]);
    }

    void junction(int subset[], double float origin, double float master) {
      int origin_set = search(subset, origin);
      int master_set = search(subset, master);
      subset[origin_set] = master_set;
    }

    void kruskal() {
      vector<Edge> tree;
      int size_edges = edges.size();

      sort(edges.begin(), edges.end());

      int * subset = new int[size_edges+1];

      memset(subset, ALONE, sizeof(int) * (size_edges+1));

      for(int i = 0; i < size_edges; i++) {
        int origin = search(subset, edges[i].getOrigin());
        int master = search(subset, edges[i].getMaster());

        if(origin != master) {
          tree.push_back(edges[i]);
          junction(subset, origin, master);
        }
      }

      int size_tree = tree.size();

      sort(tree.begin(), tree.end(), sortOrigin);

      //printf("%d\n", size_tree);
      for(int i = 0; i < size_tree; i++) {
        if(tree[i].getOrigin() < tree[i].getMaster())
          printf("%d %d\n", tree[i].getOrigin(), tree[i].getMaster());
        else
          printf("%d %d\n", tree[i].getMaster(), tree[i].getOrigin());
      }
    }
};

int main(){
  int n;
  double float origin, master;

  scanf("%d", &n);

  while(n != 0){    
    test++;
    Graph g(n);

    for(int i = 0; i < n; i++){
      scanf("%d %d %d", &origin, &master);
      g.addEdge(origin, master);
    }

    g.kruskal();

    scanf("%d", &n);
  }  
  return 0;
}