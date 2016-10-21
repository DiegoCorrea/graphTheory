#include <iostream>
#include <vector>
#include <algorithm>

#include <string.h>
#include <stdio.h>
using namespace std;

# define ALONE -1

class Edge{
  int origin, master;

  public:

    Edge(int v, int w){
      origin = v;
      master = w;
    }

    int getOrigin(){
      return origin;
    }

    int getMaster(){
      return master;
    }
};

class Graph {
  int numberOfVertex;

  public:
    vector<Edge> edges;
    vector<Edge> circuit;

    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
      edges.clear();
    }

    void addEdge(int origin, int master) {
      Edge edge(origin, master);
      edges.push_back(edge);
    }

    void addEdgeOnCircuit(int origin, int master){
      Edge edge(origin, master);
      circuit.push_back(edge);
    }

    int getNumberOfVertex(){
      return this->numberOfVertex;
    }

    int getEdgesSize(){
      return edges.size();
    }

    int searchEdge(int vertex){
      //printf("Search: %d\n", vertex);
      for(int i = 0; i < edges.size();i++){
        if(edges[i].getOrigin() == vertex || edges[i].getMaster() == vertex){
          //printf("Found: %d %d",edges[i].getOrigin(), edges[i].getMaster());
          return i;
        }
      }
      return -1;
    }

    void removeEdge(int edgeToRemove){
      edges.erase(edges.begin() + edgeToRemove);
    }

    Edge copyInOrder(int local, int toCompare){
      if(edges[local].getMaster() == toCompare){
        Edge edge(edges[local].getMaster(), edges[local].getOrigin());
        return edge;
      } else{
        Edge edge(edges[local].getOrigin(), edges[local].getMaster());
        return edge;
      }
    }

    bool necklace(){
      Edge walker = edges[0];
      //printf("Add to Circuit: Origin: %d Master: %d\n",edges[0].getOrigin(), edges[0].getMaster());
      circuit.push_back(walker);
      int start = walker.getOrigin();
      //printf("Remove from Edges: Origin: %d Master: %d\n",walker.getOrigin(), walker.getMaster());
      removeEdge(0);

      for(int i = 1, size_edges = edges.size()+1, local; i < size_edges;i++){        
        local = searchEdge(walker.getMaster());
        //printf(" on Local: %d\n", local);
        if(local == -1) return false;

        walker = copyInOrder(local, walker.getMaster());

        //printf("Add to Circuit: Origin: %d Master: %d\n",walker.getOrigin(), walker.getMaster());
        addEdgeOnCircuit(walker.getOrigin(),walker.getMaster());

        //printf("Remove from Edges: Origin: %d Master: %d from Local: %d\n",edges[local].getOrigin(), edges[local].getMaster(), local);
        removeEdge(local);
        //printf("\n");
      }

      if(start == walker.getMaster()){
        return true;
      } else {
        return false;
      }
      
    }

    void printCircuit(){
      for(int i = 0; i < circuit.size(); i++){
        printf("%d %d\n",circuit[i].getOrigin(),circuit[i].getMaster());
      }
    }
};

int main(){
  int n, input;
  int origin, master;
  bool isCircuit;

  scanf("%d", &input);

  for(int test = 1; test <= input; test++){
    scanf("%d", &n);

    Graph g(n);

    for(int i = 0; i < n; i++){
      scanf("%d %d", &origin, &master);
      g.addEdge(origin, master);
    }
    isCircuit = false;
    if(g.getEdgesSize() > 0){
      isCircuit = g.necklace();
    }
  
    if(test > 1)
      printf("\n");
    printf("Case #%d\n", test);
    if (isCircuit){
      g.printCircuit();
    } else {
      printf("some beads may be lost\n");
    }
  }
  return 0;
}