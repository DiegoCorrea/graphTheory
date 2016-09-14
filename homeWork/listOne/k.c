# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 401
# define MAXEDGE 79801

# define ENDLINE 1
# define ISBRIDGE 2
# define MARK 1
# define NORMAL 0

typedef struct Vertex {
  int color;
  int bridge;
  int father;
  int edgeCount;
  int edge[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX];

int m = 0, n = 0;
int teste = 0, start = 0, countTime = 0;

void makeList();
void printAll();
int dfsVisit();
void dfs();

int main() {

  scanf("%d %d", &n, &m);
  while(n != 0){
    teste++;
    makeList();

    dfs();

    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, v, w;
  start = 1;

  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].edgeCount = 0;
    vertexList[i].father = 0;
    vertexList[i].bridge = 0;

    bzero(vertexList[i].edge, MAXEDGE*(sizeof(int)));
  }

  for(i = 0; i < m;i++){
    scanf("%d %d", &v, &w);

    vertexList[v].edge[vertexList[v].edgeCount] = w;
    vertexList[v].edgeCount++;

    vertexList[w].edge[vertexList[w].edgeCount] = v;
    vertexList[w].edgeCount++;

    if(vertexList[w].edgeCount > start){
      start = w;
    }
    if(vertexList[v].edgeCount > start){
      start = v;
    }
  }
}

void printAll(){
  int i, j = 0;

  if(teste > 1)
    printf("\n");
  printf("Teste %d\n", teste);

  for(i = 0; i <= n;i++){
    if(vertexList[i].bridge == MARK && j >= 1){
      printf(" %d", i);
      j++;
    }
    if(vertexList[i].bridge == MARK && j == 0){
      printf("%d", i);
      j++;
    }
  }
  if (j == 0) {
    printf("nenhum");
  }
  printf("\n");
}

void dfsVisit(int u){
  countTime++;
  vertexList[u].
}