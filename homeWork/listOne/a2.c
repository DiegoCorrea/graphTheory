# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2


# define MAXVERTEX 101
# define MAXEDGE 101

int m, n;
int time = 0, s = 1, queue[MAXVERTEX] = {0}, scc = 0, teste = 0;

struct Vertex {
  int color;
  int start;
  int finish;
  int father;
  int egde[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void dfs();
void dfsVisit();

int main() {

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){
    teste++;

    makeList();

    dfs();

    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, v, w;

  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].start = 0;
    vertexList[i].finish = 0;
    vertexList[i].father = 0;
    bzero(vertexList[i].egde, MAXEDGE*(sizeof(int)));
  }

  for(i = 0; i < m;i++){
    scanf("%d %d", &v, &w);
    
    for(j = 0;vertexList[v].egde[j] != 0;j++);
    vertexList[v].egde[j] = w;
    for(j = 0;vertexList[w].egde[j] != 0;j++);
    vertexList[w].egde[j] = v;
    
  }
}

void dfsVisit(int u){
  int v, i;
  
  time++;
  vertexList[u].start = time;
  vertexList[u].color = GRAY;

  for(i = 0;vertexList[u].egde[i] != 0;i++){
    v = vertexList[u].egde[i];

    if(vertexList[v].color == WHITE){
      vertexList[v].father = u;
      dfsVisit(v);
    }
  }
  vertexList[u].color = BLACK;
  time++;
  vertexList[u].finish = time;
}

void dfs(){
  int i;

  scc = 0;
  time = 0;
  for(i = 1; i <= n;i++){
    if(vertexList[i].color == WHITE){
      dfsVisit(i);
      scc++;
    }
  }
}

void printAll(){

  if(teste > 1)
    printf("\n");
  printf("Teste %d\n", teste);
  if(scc == 1)
    printf("normal\n");
  else
    printf("falha\n");
}