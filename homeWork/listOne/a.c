# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 101
# define MAXEDGE 101

struct Vertex {
  int color;
  int time;
  int father;
  int edge[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void bfs();
void verify();


int m = 0, n = 0, s = 1;
int queueVertex[MAXVERTEX], teste = 0, isDown = 0;

int main() {

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){
    teste++;

    makeList();
    
    bfs();

    verify();

    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, v, w;

  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].time = 0;
    vertexList[i].father = 0;
    bzero(vertexList[i].edge, MAXEDGE*(sizeof(int)));
    
    bzero(queueVertex, MAXVERTEX*(sizeof(int)));
  }

  for(i = 0; i < m;i++){
    scanf("%d %d", &v, &w);
    
    for(j = 0;vertexList[v].edge[j] != 0;j++);
    vertexList[v].edge[j] = w;

    for(j = 0;vertexList[w].edge[j] != 0;j++);
    vertexList[w].edge[j] = v;
  }
}

void bfs(){
  int i, nq = 0, u, v;
  vertexList[s].color = GRAY;
  vertexList[s].time = 0;

  nq++;
  queueVertex[nq] = s;
  
  while(nq != 0){
    u = queueVertex[nq];
    nq--;

    for(i = 0;vertexList[u].edge[i] != 0;i++){
      v = vertexList[u].edge[i];

      if(vertexList[v].color == WHITE){
        vertexList[v].color = GRAY;
        vertexList[v].time = vertexList[u].time++;
        vertexList[v].father = u;
        nq++;
        queueVertex[nq] = v;
      }
    }
    vertexList[u].color = BLACK;
  }
}

void verify(){
  int i;
  for(i = 1; i <= n;i++){
    if(vertexList[i].color != BLACK)
      isDown = 1;
  }
}

void printAll(){

  if(teste > 1)
    printf("\n");
  printf("Teste %d\n", teste);
  if(isDown == 0)
    printf("normal\n");
  else
    printf("falha\n");
}