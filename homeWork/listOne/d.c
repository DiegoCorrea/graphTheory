# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 51
# define MAXEDGE 2501

typedef struct Vertex {
  int color;
  int countDistance;
  int edgeCount;
  int edge[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void bfs();

  
int m = 0, n = 0, s = 0, p = 0;
int queueVertex[MAXVERTEX], teste = 0;

int main() {

  scanf("%d %d %d %d", &n, &m, &s, &p);
  while(n != 0){
    teste++;

    makeList();
    
    bfs();

    printAll();

    scanf("%d %d %d %d", &n, &m, &s, &p);
  }

  return 0;
}

void makeList() {
  int i, v, w;

  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].countDistance = 0;
    vertexList[i].edgeCount = 0;
    bzero(vertexList[i].edge, MAXEDGE*(sizeof(int)));
    
    bzero(queueVertex, MAXVERTEX*(sizeof(int)));
  }

  for(i = 0; i < m;i++){
    scanf("%d %d", &v, &w);

    vertexList[v].edge[vertexList[v].edgeCount] = w;
    vertexList[v].edgeCount++;

    vertexList[w].edge[vertexList[w].edgeCount] = v;
    vertexList[w].edgeCount++;
  }
}

void bfs(){
  int i, nq = 0, u, v;

  vertexList[s].color = GRAY;
  vertexList[s].countDistance = 0;

  nq++;
  queueVertex[nq] = s;

  while(nq != 0){
    u = queueVertex[nq];
    queueVertex[nq] = 0;
    nq--;

    for(i = 0;i < vertexList[u].edgeCount;i++){
      v = vertexList[u].edge[i];

      if(vertexList[v].color == WHITE || vertexList[u].countDistance + 1 <= vertexList[v].countDistance){
        vertexList[v].color = GRAY;
        vertexList[v].countDistance = vertexList[u].countDistance + 1;

        nq++;
        queueVertex[nq] = v;
      }
    }
    vertexList[u].color = BLACK;
  }
}

void printAll(){
  int i, j, count = 0;

  if(teste > 1)
    printf("\n");
  printf("Teste %d\n", teste);

  bzero(queueVertex, MAXVERTEX*(sizeof(int)));

  for(i = 1; i <= n;i++){
    if(vertexList[i].countDistance <= p && i != s){
      queueVertex[count] = i;
      count++;
    }
  }
  printf("%d", queueVertex[0]);

  for(i = 1; i < count; i++){
    printf(" %d", queueVertex[i]);
  }
  printf("\n");
}