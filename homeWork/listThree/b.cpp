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
      vector<int> solution;
      int walker;
      
      for(int i = 0; i <= this->numberOfVertex;i++) {priorityQueue.push_back(i);}
      
      while(!priorityQueue.empty()){
        walker = extractMin();

        //printf("Extract Min: id: %d distance: %d\n", vertexVector[walker].getId(), vertexVector[walker].getVisitedTime());

        if(walker < this->finish && (vertexVector[walker].getSonDistance() + vertexVector[walker].getVisitedTime() < vertexVector[this->finish].getVisitedTime())){
          vertexVector[this->finish].setVisitedTime(vertexVector[walker].getSonDistance() + vertexVector[walker].getVisitedTime());
        }
        if(walker < this->finish)
           break;

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

    void calcFather(){
      vertexVector[this->finish].setSonDistance(0);
      for(int son = this->finish, father = son - 1; father >= 0;son--, father--){
        vertexVector[father].setSonDistance(vertexVector[son].getSonDistance() + vertexVector[son].searchEdgeDistance(father));
      }
    }

    void result(){
      if(vertexVector[this->finish].getVisitedTime() != INFINITE){
        printf("%d\n", vertexVector[this->finish].getVisitedTime());
      }
    }

    void printAllGraph(){
      printf("start: %d finish: %d\n", this->start, this->finish);
      for(int i = 0; i <= this->numberOfVertex;i++){
        printf("id: %d\n", vertexVector[i].getId());
        printf("Father: %d Visited Time: %d Son Distance: %d\n", vertexVector[i].getFather(), vertexVector[i].getVisitedTime(), vertexVector[i].getSonDistance());
        for(int j = 0; j < vertexVector[i].getGrau();j++){
          printf("\tmaster: %d distance: %d\n", vertexVector[i].getEdgeMaster(j),vertexVector[i].getEdgeDistance(j));
        }
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
    //g.printAllGraph();
    g.dijkstra();
    g.result();
    scanf("%d %d %d %d", &n, &m, &c, &k);
  }
  return 0;
}