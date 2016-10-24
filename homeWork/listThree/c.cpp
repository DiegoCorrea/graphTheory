# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>
using namespace std;

# define MAXVERTEX 1001
# define INFINITE 99999999

class Edge{
  int master, distance;

  public:

    Edge(int master, int distance){
      this->master = master;
      this->distance = distance;
    }

    int getMaster(){
      return master;
    }

    int getDistance(){
      return distance;
    }
};

class Vertex{
  int father, visitedTime, id, sonDistance;
  vector<Edge> edges;

  public:     

    Vertex(int i){
      this->visitedTime = INFINITE;
      this->father = INFINITE;
      this->id = i;
      this->sonDistance = 0;
    }

    void addEdge(int master, int distance) {
      Edge edge(master, distance);
      edges.push_back(edge);
    }

    int getVisitedTime(){
      return this->visitedTime;
    }
    int getFather(){
      return this->father;
    }

    int getId(){
      return this->id;
    }
    int getSonDistance(){
      return this->sonDistance;
    }

    void setSonDistance(int value){
      this->sonDistance = value;
    }

    void setVisitedTime(int dis){
      this->visitedTime = dis;
    }

    void setFather(int fa){
      this->father = fa;
    }

    int getGrau(){
      return edges.size();
    }

    Edge getEdge(int position){
      return edges[position];
    }
    int getEdgeMaster(int position){
      return edges[position].getMaster();
    }

    int getEdgeDistance(int position){
      return edges[position].getDistance();
    }

    int searchEdgeDistance(int master){
      for(int i = 0; i < edges.size();i++){
        if(edges[i].getMaster() == master)
          return edges[i].getDistance();
      }
      return 0;
    }
};

class Graph {
  int numberOfVertex;
  vector<Vertex> vertexVector;

  public:
    
    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      vertexVector.clear();
    }

    void addVertex(int origin, int master, int distance){
      vertexVector[origin].addEdge(master,distance);
    }

    void initialize(){
      //Initialize single source
      for(int i = 0; i <= MAXVERTEX; i++){
        Vertex v(i);        
        vertexVector.push_back(v);
      }
    }

    void relax(int origin, int master, int positionMasterToRelax){
      if(vertexVector[origin].getVisitedTime() + vertexVector[origin].searchEdgeDistance(master) < vertexVector[master].getVisitedTime()){
        vertexVector[master].setVisitedTime(vertexVector[origin].getVisitedTime() + vertexVector[origin].searchEdgeDistance(master));
        vertexVector[master].setFather(vertexVector[origin].getId());
      }
    }

    bool bellManFord(){
      vertexVector[0].setVisitedTime(0);

      for(int walker = 0; walker < this->numberOfVertex ;walker++){
        for(int i = 0; i < vertexVector[walker].getGrau();i++){
          relax(vertexVector[walker].getId(),vertexVector[walker].getEdgeMaster(i), i);
        }
      }
      for(int walker = 0; walker < this->numberOfVertex ;walker++){
        for(int i = 0; i < vertexVector[walker].getGrau();i++){
          if(vertexVector[walker].getVisitedTime() + vertexVector[walker].searchEdgeDistance(vertexVector[walker].getEdgeMaster(i)) < vertexVector[vertexVector[walker].getEdgeMaster(i)].getVisitedTime()){
            return false;
          }
        }
      }
      return true;
    }
};

int main(){
  int n = 1, m = 1, test = 0;
  int origin, master, distance;

  scanf("%d",&test);

  for(int i = 0; i < test;i++){
    scanf("%d %d", &n, &m);
    Graph g(n);    
    g.initialize();

    for(int i = 0; i < m; i++){
      scanf(" %d %d %d", &origin, &master, &distance);
      g.addVertex(origin, master, distance);
    }

    if(!g.bellManFord()){
      printf("possible\n");
    }else{
      printf("not possible\n");
    }

  }

  return 0;
}