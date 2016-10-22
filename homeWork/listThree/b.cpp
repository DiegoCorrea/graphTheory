# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>
using namespace std;

# define MAXVERTEX 252
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

    int extractRoute(){
      int city = priorityQueue.front();
      priorityQueue.erase(priorityQueue.begin() + 0);
      return city;
    }

    void relax(int origin, int master, int positionMasterToRelax){
      if(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(positionMasterToRelax) < vertexVector[master].getVisitedTime()){
        vertexVector[master].setVisitedTime(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(positionMasterToRelax));
        vertexVector[master].setFather(vertexVector[origin].getId());
      }
    }

    void dijkstra(){
      vertexVector[this->start].setVisitedTime(0);
      //vector<int> solution;
      bool outRoute = true;

      for(int i = 0; i <= this->numberOfVertex;i++) {priorityQueue.push_back(i);}
      
      while(!priorityQueue.empty()){
        int walker;
        if(outRoute){
          walker = extractMin();
        }
        if(walker <= this->finish && outRoute){
          outRoute = false;
          priorityQueue.clear();
          for(int i = walker; i < this->finish;i++) {priorityQueue.push_back(i);}
        }
        if(!outRoute && !priorityQueue.empty()){
          walker = extractRoute();
        }
        if(outRoute){
          for(int i = 0; i < vertexVector[walker].getGrau();i++){
            relax(vertexVector[walker].getId(),vertexVector[walker].getEdgeMaster(i), i);
            //printf("Relando: origin: %d master: %d distance: %d\n", vertexVector[walker].getId(),vertexVector[walker].getEdgeMaster(i),vertexVector[walker].getEdgeDistance(i));
          }
        }
        if(!outRoute){
          for(int i = 0; i < vertexVector[walker].getGrau(); i++){
            if(vertexVector[walker].getId() < vertexVector[walker].getEdgeMaster(i) && (priorityQueue.empty() || vertexVector[walker].getEdgeMaster(i) < this->finish)){
              relax(vertexVector[walker].getId(),vertexVector[walker].getEdgeMaster(i), i);
              //printf("Relando: origin: %d master: %d distance: %d\n", vertexVector[walker].getId(),vertexVector[walker].getEdgeMaster(i),vertexVector[walker].getEdgeDistance(i));
            }
          }
        }
        //solution.push_back(walker);
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
  int n = 1, m = 1, c = 1, k = 1;
  int origin, master, distance;

  scanf("%d %d %d %d", &n, &m, &c, &k);

  while(n != 0){

    Graph g(n);
    g.initialize();

    for(int i = 0; i < m; i++){
      scanf(" %d %d %d", &origin, &master, &distance);
      g.addVertex(origin, master, distance);
      g.addVertex(master, origin, distance);
    }
    g.startAndFinish(k, c-1);

    g.calcFather();

    g.dijkstra();
    g.result();
    scanf("%d %d %d %d", &n, &m, &c, &k);
  }

  return 0;
}