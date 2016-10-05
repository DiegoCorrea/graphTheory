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

    void addEdgeOnCircuit(Edge edgeToCompare, int compare){
      if(edgeToCompare.getMaster() == compare){
        Edge edge(edgeToCompare.getMaster(), edgeToCompare.getOrigin());
        circuit.push_back(edge); 
      } else{
        Edge edge(edgeToCompare.getOrigin(), edgeToCompare.getMaster());
        circuit.push_back(edge); 
      }
    }

    int getNumberOfVertex(){
      return this->numberOfVertex;
    }

    int searchEdge(int vertex){
      for(int i = 0; i < edges.size();i++){
        if(edges[i].getOrigin() == vertex || edges[i].getMaster() == vertex){
          return i;
        }
      }
      return -1;
    }

    void removeEdge(int edgeToRemove){
      edges.erase(edges.begin() + edgeToRemove);
    }

    bool necklace(){
      int start;
      Edge walker = edges[0];
      removeEdge(0);
      circuit.push_back(walker);
      start = walker.getOrigin();

      for(int i = 1, local; i < edges.size();i++){        
        local = searchEdge(walker.getMaster());
        if(local == -1) return false;

        addEdgeOnCircuit(edges[local],walker.getMaster());

        walker = edges[local];
        
        removeEdge(local);       
      }
      /*
      int finish = walker.getMaster();
      if(start == finish){
        return true;
      } else {
        return false;
      }
      */
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

    isCircuit = g.necklace();
  
    printf("Case #%d\n", test);
    if (isCircuit){
      g.printCircuit();
    } else {
      printf("some beads may be lost\n");
    }
  }
  return 0;
}