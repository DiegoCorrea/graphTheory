# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>
using namespace std;

# define INITIALVERTEX 1
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

  public: 
    int father, visitedTime, id;
    vector<Edge> edges;
    Vertex(int i){
      this->visitedTime = INFINITE;
      this-> father = INFINITE;
      this->id = i;
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
};

class Graph {

  public:
    int numberOfVertex;
    int start;
    int finish;
    vector<Vertex> vertexVector;
    vector<Vertex> vertexQueue;

    Graph(int numberOfVertex){
      vertexVector.clear();
      vertexQueue.clear();
      this->numberOfVertex = numberOfVertex;
    }

    void addVertex(int origin, int master, int distance){
      vertexVector[origin].addEdge(master,distance);
    }

    void startAndFinish(int s, int f){
      this->start = s;
      this->finish = f;
    }

    void initialize(){
      //Initialize single source
      for(int i = 0; i <= this->numberOfVertex; i++){
        
        Vertex v(i);
        
        vertexVector.push_back(v);
        //printf("Add Vertex: id: %d father: %d distance: %d\n", vertexVector[i].getId(), vertexVector[i].getFather(), vertexVector[i].getVisitedTime());
      }
    }

    void printAllGraph(){
      printf("start: %d finish: %d\n", this->start, this-> finish);
      for(int i = 0; i < vertexVector.size();i++){
        printf("id: %d\n", vertexVector[i].getId());
        printf("Father: %d Visited Time: %d \n", vertexVector[i].getFather(), vertexVector[i].getVisitedTime());
        for(int j = 0; j < vertexVector[i].getGrau();j++){
          printf("\tmaster: %d distance: %d\n", vertexVector[i].getEdgeMaster(j),vertexVector[i].getEdgeDistance(j));
        }
      }
    }

    Vertex extractMin(){
      int queueSize = vertexQueue.size();
      Vertex walker = vertexQueue.front();
      Vertex min = vertexQueue.front();
      int eraseVertex = 0;

      //printf("ee\n");
      for(int i = 0; i < queueSize ; i++){
        walker = vertexQueue[i];
        //printf("fff\n");
        if(min.getVisitedTime() > walker.getVisitedTime()){
          Vertex min = walker;
          eraseVertex = i;
        }
      }
      //printf("dededede\n");
      vertexQueue.erase(vertexQueue.begin() + eraseVertex);
      return min;
    }

    void relax(Vertex origin, int positionVertexToRelax){
      if(origin.getVisitedTime() + origin.getEdgeDistance(positionVertexToRelax) < vertexVector[positionVertexToRelax].getVisitedTime()){
        vertexVector[positionVertexToRelax].setVisitedTime(origin.getVisitedTime() + origin.getEdgeDistance(positionVertexToRelax));
        vertexVector[positionVertexToRelax].setFather(origin.getId());
      }
    }

    void dijkstra(){
      vertexVector[this->start].setVisitedTime(0);
      vector<Vertex> solution;
      vertexQueue = vertexVector;
      //printf("dd\n");

      Vertex walker = vertexVector[this->start];
      //printf("gg\n");
      while(!vertexQueue.empty()){
        Vertex walker = extractMin();
        printf("Extract Min: id: %d distance: %d\n", walker.getId(), walker.getVisitedTime());

        for(int i = 0; i < walker.getGrau();i++){
          relax(walker,i);
        }
        solution.push_back(walker);
      }
    }
};

int main(){
  int n, m;
  int origin, master, distance;

  while(n != 0){
    scanf("%d %d", &n, &m);

    Graph g(n);
    g.initialize();

    for(int i = 0; i < m; i++){
      scanf("%d %d %d", &origin, &master, &distance);
      g.addVertex(origin, master, distance);
    }

    scanf("%d %d", &origin, &master);
    g.startAndFinish(origin, master);

    g.printAllGraph();

    g.dijkstra();

    g.printAllGraph();

    scanf("%d %d", &n, &m);
  }

  return 0;
}