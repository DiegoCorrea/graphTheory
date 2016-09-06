# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <vector>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 5001
# define MAXEDGE 5001
# define TAMNAME 31

int m, n;
int larger = 0, count = 0;

typedef struct Vertex {
  char name[TAMNAME];
  int color;
  int edgeNumber;
  std::vector<int> edge;
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void result();
void dfs();
void dfsVisit();

int main() {

  scanf("%d%d", &n, &m);
  while(n != 0 || m != 0){
    makeList();

    dfs();

    result();

    scanf("%d%d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, w, v;
  char origin[TAMNAME], master[TAMNAME];

  for(i = 0; i < n; i++){
    scanf("%s", vertexList[i].name);
    vertexList[i].color = WHITE;
    vertexList[i].edgeNumber = 0;
    vertexList[i].edge.clear();
  }

  i = 0;
  while(i < m){
    scanf("%s%s", origin, master);
    for(j = 0; j < n; j++){
      if(strcmp(vertexList[j].name,origin) == 0){
        v = j;
      }
      if(strcmp(vertexList[j].name,master) == 0){
        w = j;
      }
    }

    vertexList[v].edge.push_back(w);
    vertexList[v].edgeNumber++;

    vertexList[w].edge.push_back(v);
    vertexList[w].edgeNumber++;

    i++;
  }
}

void dfsVisit(int u){
  int v, i;

  vertexList[u].color = GRAY;

  for(i = 0;i < vertexList[u].edgeNumber;i++){
    v = vertexList[u].edge[i];

    if(vertexList[v].color == WHITE){
      count++;
      dfsVisit(v);
    }
  }
  vertexList[u].color = BLACK;
}

void dfs(){
  int i;
  count = 0;
  larger = 0;

  for(i = 0; i < n;i++){
    if(vertexList[i].color == WHITE){
      count = 1;

      dfsVisit(i);
      if (count > larger)
        larger = count;
    }
  }
}

void result(){
  printf("%d\n",larger);
}