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
  int visitedTime, id;
  vector<Edge> edges;

  public:     

    Vertex(int i){
      this->visitedTime = INFINITE;
      this->id = i;
    }

    void addEdge(int master, int distance) {
      Edge edge(master, distance);
      edges.push_back(edge);
    }

    int getVisitedTime(){
      return this->visitedTime;
    }

    int getId(){
      return this->id;
    }

    void setVisitedTime(int dis){
      this->visitedTime = dis;
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

    void clearValues(){
      for(int i = 0; i <= this->numberOfVertex; i++){
        vertexVector[i].setVisitedTime(INFINITE);
      }
    }

    void initialize(){
      //Initialize single source
      for(int i = 0; i <= this->numberOfVertex; i++){
        Vertex v(i);        
        vertexVector.push_back(v);
      }
    }

    int extractMin(){
      int queueSize = priorityQueue.size();
      Vertex walker = vertexVector[priorityQueue.front()];
      Vertex min = vertexVector[priorityQueue.front()];
      int eraseVertex = 0;

      for(int i = 0; i < queueSize ; i++){
        walker = vertexVector[priorityQueue[i]];
        if(walker.getVisitedTime() <= min.getVisitedTime() ){
          min = walker;
          eraseVertex = i;
        }
      }
      priorityQueue.erase(priorityQueue.begin() + eraseVertex);
      return min.getId();
    }

    void relax(int origin, int master, int positionMasterToRelax){
      if(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(positionMasterToRelax) < vertexVector[master].getVisitedTime()){
        vertexVector[master].setVisitedTime(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(positionMasterToRelax));
      }
    }

    void dijkstra(int cityDistance){
      vertexVector[this->start].setVisitedTime(0);
      for(int i = 0; i <= this->numberOfVertex;i++) {priorityQueue.push_back(i);}

      int city = 0;
      while(!priorityQueue.empty() && city <= cityDistance){
        int walker = extractMin();
        int grau = vertexVector[walker].getGrau();
        for(int i = 0, id = vertexVector[walker].getId(); i < grau;i++){
          relax(id,vertexVector[walker].getEdgeMaster(i), i);
        }
        city++;
      }
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
  int n, m;
  int origin, master, distance, lookTrip, cityDistance, test = 0;

  while(scanf("%d %d", &n, &m) != EOF){
    if(test >= 1)
      printf("\n");
    test++;
    Graph g(n);
    g.initialize();

    for(int i = 0; i < m; i++){
      scanf(" %d %d %d", &origin, &master, &distance);
      g.addVertex(origin, master, distance);
    }

    printf("Instancia %d\n", test);
    scanf("%d", &lookTrip);
    for(int i = 0; i < lookTrip;i++){
      scanf("%d %d %d", &origin, &master, &cityDistance);
      g.startAndFinish(origin, master);
      g.clearValues();
      g.dijkstra(cityDistance);
      g.result();
    }
  }
  return 0;
}