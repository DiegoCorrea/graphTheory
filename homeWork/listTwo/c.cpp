# include <iostream>
# include <vector>
# include <algorithm>

# include <string.h>
# include <stdio.h>
# include <math.h>
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
  double geoCoordinateX, geoCoordinateY;

  public:
    Vertice(double x, double y){
      this->geoCoordinateX = x;
      this->geoCoordinateY = y;
    }

    double getGeoCoordinateX(){
      return geoCoordinateX;
    }

    double getGeoCoordinateY(){
      return geoCoordinateY;
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

    void addVertice(double GeoCoordinateX, double GeoCoordinateY) {
      Vertice vertice(GeoCoordinateX, GeoCoordinateY);
      vertices.push_back(vertice);
    }

    double calcVerticesDistance(int origin, int master){
      return sqrt( pow((vertices[origin].getGeoCoordinateX() - vertices[master].getGeoCoordinateX()),2) + pow((vertices[origin].getGeoCoordinateY() - vertices[master].getGeoCoordinateY()),2));
    }

    void allVertices(){
      printf("Todos os Vertices\n");
      for (int i = 0; i < numberOfVertex; ++i) {
        printf("\t%d: X: %lf Y: %lf \n", i,vertices[i].getGeoCoordinateX(),vertices[i].getGeoCoordinateY());
      }
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

      printf("Todas as Arestas\n");
      for (int i = 0; i < size_edges; ++i) {
        printf("\t%d %d : %.4lf\n", edges[i].getOrigin(), edges[i].getMaster(), edges[i].getDistance());
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
      double result = 0.0;
      printf("Arestas da Arvore:\n");
      for(int i = 0; i < size_tree; i++) {
        if(tree[i].getDistance() > result)
          result = tree[i].getDistance();
      }
      printf("%.4lf\n", result);
    }
};

int main(){
  int n;
  int origin, master;
  double distance, x, y;

  scanf("%d", &n);

  while(n != 0){
    Graph g(n);
    
    for(int i = 0; i < n; i++){
      scanf("%lf %lf", &x, &y);
      g.addVertice(x,y);
    }
    if(n > 1){
      g.allVertices();
  
      for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
          distance = g.calcVerticesDistance(i,j);
          g.addEdge(i, j, distance);  
        }      
      }
  
      g.kruskal();
    }else{ printf("0.0000\n"); }

    scanf("%d", &n);
  }  
  return 0;
}
