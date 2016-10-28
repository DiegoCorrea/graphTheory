# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>
using namespace std;

# define MAXVERTEX 252
# define INFINITE 999999

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

    void setDistance(int distance){
      this->distance = distance;
    }
    void setMaster(int master){
      this->master = master;
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
      this->sonDistance = INFINITE;
    }

    void initialize(int maxEdges){
      for(int i = 0; i < maxEdges; i++){
        Edge edge(i, INFINITE);
        edges.push_back(edge);
      }
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

    void setSonDistance(int value){
      this->sonDistance = value;
    }

    void setVisitedTime(int dis){
      this->visitedTime = dis;
    }

    void setFather(int fa){
      this->father = fa;
    }

    void setEdgeDistance(int master, int distance){
      edges[master].setDistance(distance);
      edges[master].setMaster(master);
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

    void initialize(int s, int f){
      //Initialize single source
      this->start = s;
      this->finish = f;
      for(int i = 0; i < this->numberOfVertex; i++){
        Vertex v(i);
        v.initialize(this->numberOfVertex);
        vertexVector.push_back(v);
      }
    }

    void addConection(int origin, int master, int distance){
      vertexVector[origin].setEdgeDistance(master,distance);
    }

    int extractMin(){
      int queueSize = priorityQueue.size();
      Vertex walker = vertexVector[priorityQueue.front()];
      Vertex min = vertexVector[priorityQueue.front()];
      int toDelete = 0;
      
      for(int i = 0; i < queueSize ; i++){
        walker = vertexVector[priorityQueue[i]];
        if(walker.getVisitedTime() < min.getVisitedTime()){
          min = walker;
          toDelete = i;
        }
      }
      priorityQueue.erase(priorityQueue.begin() + toDelete);
      return min.getId();
    }

    void relax(int origin, int master){
      if(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(master) < vertexVector[master].getVisitedTime()){
        vertexVector[master].setVisitedTime(vertexVector[origin].getVisitedTime() + vertexVector[origin].getEdgeDistance(master));
        vertexVector[master].setFather(vertexVector[origin].getId());
      }
    }

    void dijkstra(){
      int walker;
      vertexVector[this->start].setVisitedTime(0);

      for(int i = 0; i < this->numberOfVertex;i++) {priorityQueue.push_back(i);}

      while(!priorityQueue.empty()){
        walker = extractMin();

        if(walker <= this->finish && (vertexVector[walker].getSonDistance() + vertexVector[walker].getVisitedTime() < vertexVector[this->finish].getVisitedTime())){
          vertexVector[this->finish].setVisitedTime(vertexVector[walker].getSonDistance() + vertexVector[walker].getVisitedTime());
        }
        if(walker <= this->finish)
          break;

        for(int i = 0; i < numberOfVertex;i++){
          if(vertexVector[walker].getEdgeDistance(i) != INFINITE){
            relax(vertexVector[walker].getId(),i);
          }
        }
      }
    }

    void calcFather(){
      vertexVector[this->finish].setSonDistance(0);
      for(int son = this->finish, father = son - 1; father >= 0;son--, father--){
        vertexVector[father].setSonDistance(vertexVector[son].getSonDistance() + vertexVector[father].getEdgeDistance(son));
      }
    }

    void result(){
      if(vertexVector[this->finish].getVisitedTime() != INFINITE){
        printf("%d\n", vertexVector[this->finish].getVisitedTime());
      }
    }
};

int main(){
  int n, m, c, k;
  int origin, master, distance;

  scanf("%d %d %d %d", &n, &m, &c, &k);

  while(n != 0){
    Graph g(n);
    g.initialize(k, c-1);

    for(int i = 0; i < m; i++){
      scanf("%d %d %d", &origin, &master, &distance);
      g.addConection(origin, master, distance);
      g.addConection(master, origin, distance);
    }

    g.calcFather();

    g.dijkstra();
    g.result();
    scanf("%d %d %d %d", &n, &m, &c, &k);
  }
  return 0;
}