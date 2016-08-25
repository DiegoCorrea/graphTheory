# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2


const int MAXVERTEX = 2001;
const int MAXEDGE = 2000;

int m, n;
int time = 0, s = 1, queue[MAXVERTEX] = {0};

struct Vertex {
  int color;
  int start;
  int finish;
  int father;
  int egde[MAXEDGE];
};

Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void dfs();
void dfsVisit();

int main() {
  int i, j;

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){
    makeList();

    dfs();

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
  }

  for(i = 0; i < m;i++){
    scanf("%d %d %d", &v, &w, &p);
    
    for(j = 0;vertexList[v].egde[j] != 0;j++);
    vertexList[v].egde[j] = w;
    if (p == 2) {
      for(j = 0;vertexList[w].egde[j] != 0;j++);
      vertexList[w].egde[j] = v;
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
}

void dfs(){
  int i;

  time = 0;
  for(i = 1; i <= n;i++){
    if(vertexList[i].color == WHITE)
      dfsVisit(i);
  }
}

void printAll(){
  int i, j;
  for(i = 1; i <= n;i++){
    printf("ID: %d | Color: %d \nStart: %d | Finish: %d | Father: %d\n", i,vertexList[i].color, vertexList[i].start, vertexList[i].finish, vertexList[i].father);
    for(j = 0; vertexList[i].egde[j] != 0;j++){
      printf("\tEdge %d|", vertexList[i].egde[j]);
    }
    printf("\n");
  }
  printf("-------------------\n");
}