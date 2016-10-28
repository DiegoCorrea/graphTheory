# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>
using namespace std;

# define MAXVERTEX 101
# define INFINITE 99999

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
  int father, visitedTime, id;
  vector<Edge> edges;

  public:     

    Vertex(int i){
      this->visitedTime = INFINITE;
      this->father = INFINITE;
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
  int numberOfVertex;
  int start;
  int finish;
  vector<Vertex> vertexVector;
  vector<int> priorityQueue;

  public:
    
    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      vertexVector.clear();
      priorityQueue.clear();
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
      for(int i = 0; i <= MAXVERTEX; i++){
        Vertex v(i);        
        vertexVector.push_back(v);
      }
    }

    void printAllGraph(){
      printf("start: %d finish: %d\n", this->start, this->finish);
      for(int i = 0; i <= this->numberOfVertex;i++){
        printf("id: %d\n", vertexVector[i].getId());
        printf("Father: %d Visited Time: %d \n", vertexVector[i].getFather(), vertexVector[i].getVisitedTime());
        for(int j = 0; j < vertexVector[i].getGrau();j++){
          printf("\tmaster: %d distance: %d\n", vertexVector[i].getEdgeMaster(j),vertexVector[i].getEdgeDistance(j));
        }
      }
    }

    int extractMin(){
      int queueSize = priorityQueue.size();
      Vertex walker = vertexVector[priorityQueue.front()];
      Vertex min = vertexVector[priorityQueue.front()];
      int eraseVertex = 0;

      //printf("ee\n");
      for(int i = 0; i < queueSize ; i++){
        walker = vertexVector[priorityQueue[i]];
        //printf("fff\n");
        if(walker.getVisitedTime() <= min.getVisitedTime() ){
          min = walker;
          eraseVertex = i;
        }
      }
      //printf("dededede\n");
      priorityQueue.erase(priorityQueue.begin() + eraseVertex);
      return min.getId();
    }

    void relax(int origin, int master, int positionMasterToRelax){
      if(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(positionMasterToRelax) < vertexVector[master].getVisitedTime()){
        vertexVector[master].setVisitedTime(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(positionMasterToRelax));
        vertexVector[master].setFather(vertexVector[origin].getId());
      }
    }

    void dijkstra(){
      vertexVector[this->start].setVisitedTime(0);
      vector<int> solution;
      for(int i = 0; i <= this->numberOfVertex;i++) {priorityQueue.push_back(i);}
      
      while(!priorityQueue.empty()){
        int walker = extractMin();
        //printf("Extract Min: id: %d distance: %d\n", vertexVector[walker].getId(), vertexVector[walker].getVisitedTime());

        for(int i = 0; i < vertexVector[walker].getGrau();i++){
          relax(vertexVector[walker].getId(),vertexVector[walker].getEdgeMaster(i), i);
        }
        solution.push_back(walker);
      }
      /*
      for (int i = 0; i <= this->numberOfVertex; ++i){
        printf("id: %d Visited time: %d\n", vertexVector[i].getId(), vertexVector[i].getVisitedTime());
      }
      */
    }

    void result(){
      if(vertexVector[this->finish].getVisitedTime() != INFINITE){
        printf("%d\n", vertexVector[this->finish].getVisitedTime());
      } else{
        printf("-1\n");
      }
    }
};

int main(){
  int n = 1, m = 1;
  int origin, master, distance;

  scanf("%d %d", &n, &m);

  while(n != 0){

    Graph g(n);
    g.initialize();

    for(int i = 0; i < m; i++){
      scanf(" %d %d %d", &origin, &master, &distance);
      g.addVertex(origin, master, distance);
      //printf("==origin %d master %d distance: %d\n", origin,master,distance);
    }

    scanf("%d %d", &origin, &master);
    //printf("origin %d master %d\n", origin,master);
    g.startAndFinish(origin, master);

    //g.printAllGraph();

    g.dijkstra();
    g.result();
    //printf("====================\t=======================\n");
    scanf("%d %d", &n, &m);
    //printf("vertex: %d edges: %d\n", n,m);
  }

  return 0;
}