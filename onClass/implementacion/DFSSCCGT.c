# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2


# define MAXVERTEX 2001
# define MAXEDGE 2001

int m, n;
int time = 0, s = 1, scc = 0, scct = 0, finishList[MAXVERTEX], fPosition;

typedef struct Vertex {
  int color;
  int start;
  int finish;
  int father;
  int egde[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX], vertexListTransposed[MAXVERTEX];

void makeList();
void printAll();
void dfsVisit();
void dfs();
void dfsVisitTransposed();
void dfsTransposed();

int main() {

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){

    makeList();
    
    dfs();

    dfsTransposed();

    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, v, w, p;

  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].start = 0;
    vertexList[i].finish = 0;
    vertexList[i].father = 0;
    bzero(vertexList[i].egde, MAXEDGE*(sizeof(int)));

    //Transposed
    vertexListTransposed[i].color = WHITE;
    vertexListTransposed[i].start = 0;
    vertexListTransposed[i].finish = 0;
    vertexListTransposed[i].father = 0;
    bzero(vertexListTransposed[i].egde, MAXEDGE*(sizeof(int)));
  }

  bzero(finishList, MAXVERTEX*(sizeof(int)));
  fPosition = 0;

  for(i = 0; i < m;i++){
    scanf("%d %d %d", &v, &w, &p);
    
    for(j = 0;vertexList[v].egde[j] != 0;j++);
    vertexList[v].egde[j] = w;
    if (p == 2) {
      for(j = 0;vertexList[w].egde[j] != 0;j++);
      vertexList[w].egde[j] = v;
    }
    //Transposed
    for(j = 0;vertexListTransposed[w].egde[j] != 0;j++);
    vertexListTransposed[w].egde[j] = v;
    if (p == 2) {
      for(j = 0;vertexListTransposed[v].egde[j] != 0;j++);
      vertexListTransposed[v].egde[j] = w;
    }
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

  fPosition++;
  finishList[fPosition] = u;
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

void dfsVisitTransposed(int u){
  int v, i;
  
  time++;
  vertexListTransposed[u].start = time;
  vertexListTransposed[u].color = GRAY;

  for(i = 0;vertexListTransposed[u].egde[i] != 0;i++){
    v = vertexListTransposed[u].egde[i];

    if(vertexListTransposed[v].color == WHITE){
      vertexListTransposed[v].father = u;
      dfsVisitTransposed(v);
    }
  }
  vertexListTransposed[u].color = BLACK;
  time++;
  vertexListTransposed[u].finish = time;
}

void dfsTransposed(){
  int i;

  scct = 0;
  time = 0;
  for(;fPosition > 0;fPosition--){
    if(vertexListTransposed[finishList[fPosition]].color == WHITE){
      dfsVisitTransposed(finishList[fPosition]);
      scct++;
    }
  }
}

void printAll(){
  int i, j;

  printf("Strong Connected Components: %d\n", scc);
  for(i = 1; i <= n;i++){
    printf("ID: %d | Color: %d \nStart: %d | Finish: %d | Father: %d\n", i,vertexList[i].color, vertexList[i].start, vertexList[i].finish, vertexList[i].father);
    for(j = 0; vertexList[i].egde[j] != 0;j++){
      printf("\tEdge %d|", vertexList[i].egde[j]);
    }
    printf("\n");
  }
  printf("\n\n");
  printf("Transposed: %d\n", scct);
  for(i = 1; i <= n;i++){
    printf("ID: %d | Color: %d \nStart: %d | Finish: %d | Father: %d\n", i,vertexListTransposed[i].color, vertexListTransposed[i].start, vertexListTransposed[i].finish, vertexListTransposed[i].father);
    for(j = 0; vertexListTransposed[i].egde[j] != 0;j++){
      printf("\tEdge %d|", vertexListTransposed[i].egde[j]);
    }
    printf("\n");
  }

  for(i = 1; i <= n; i++){
    printf("%d ", finishList[i]);
  }
  printf("\n");
  printf("-------------------\n");
}