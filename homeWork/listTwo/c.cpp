# include <iostream>
# include <vector>
# include <algorithm>

# include <string.h>
# include <stdio.h>
using namespace std;

# define ALONE -1

class Edge{
  int origin, master;
  double distance;

  public:

    Edge(int v, int w, double distance){
      this->origin = v;
      this->master = w;
      this->distance = distance;
    }

    int getOrigin(){
      return origin;
    }

    int getMaster(){
      return master;
    }

    double getDistance(){
      return distance;
    }

    bool operator < (const Edge& master) const{
      return (distance < master.distance);
    }
};

class Vertice {
  double geoCoordinate1, geoCoordinate2;

  public:
    Vertice(double x1, double x2){
      this->geoCoordinate1 = x1;
      this->geoCoordinate2 = x2;
    }

    double getGeoCoordinate1(){
      return geoCoordinate1;
    }

    double getGeoCoordinate2(){
      return geoCoordinate2;
    }
};

class Graph {
  int numberOfVertex;

  public:
    vector<Edge> edges;
    vector<Vertice> vertices;

    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      edges.clear();
      vertices.clear();
    }

    void addEdge(int origin, int master, double distance) {
      Edge edge(origin, master, distance);
      edges.push_back(edge);
    }

    void addVertice(double GeoCoordinate1, double GeoCoordinate2) {
      Vertice vertice(GeoCoordinate1, GeoCoordinate2);
      vertices.push_back(vertice);
    }

    int search(int subset[], int edge){
      if(subset[edge] == ALONE){
        return edge;
      }
      return search(subset, subset[edge]);
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
      printf("Distancia Ordenada\n");
      for (int i = 0; i < size_edges; ++i) {
        printf("%.3f ", edges[i].getDistance());
      }
      printf("\n");

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
  int origin, master;
  double distance, x1, x2;

  scanf("%d", &n);

  while(n != 0){
    Graph g(n);

    for(int i = 0; i < n; i++){
      scanf("%lf %lf", &x1, &x2);
      g.addVertice(x1,x2);
    }

    for (int i = 1; i <= n; i++){
      for (int j = i+1; j <= n; j++){
        distance = 0.0;
        g.addEdge(i, j, distance);  
      }      
    }

    g.kruskal();

    scanf("%d", &n);
  }  
  return 0;
}
