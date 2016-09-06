# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 5001
# define MAXEDGE 5001
# define TAMNAME 31

int m, n;
int time = 0, s = 1, scc = 0, finishList[MAXVERTEX], larger = 0, count = 0;

typedef struct Vertex {
  char name[TAMNAME];
  int color;
  int start;
  int finish;
  int father;
  int egde[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void result();
void dfs();
void dfsVisit();

int main() {

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){
    makeList();

    dfs();

    result();

    //printAll();

    getchar();
    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, w, v;
  char origin[TAMNAME], master[TAMNAME];

  for(i = 1; i <= n; i++){
    scanf("%s", vertexList[i].name);
    vertexList[i].color = WHITE;
    vertexList[i].start = 0;
    vertexList[i].finish = 0;
    vertexList[i].father = 0;
    bzero(vertexList[i].egde, MAXEDGE*(sizeof(int)));
  }
  
  count = 0;
  larger = 0;

  for(i = 0; i < m;i++){
    scanf("%s %s", origin, master);
    for(j = 1; j <= n; j++){
      if(strcmp(vertexList[j].name,origin) == 0){
        v = j;
      }
      if(strcmp(vertexList[j].name,master) == 0){
        w = j;
      }
    }

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
      count++;
      if(count > larger)
        larger = count;
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
      count = 1;
      dfsVisit(i);
  }
}

void printAll(){
  int i, j;
  for(i = 1; i <= n;i++){
    printf("ID: %d | Name: %s\nColor: %d\nStart: %d | Finish: %d | Father: %d\n", i, vertexList[i].name,vertexList[i].color, vertexList[i].start, vertexList[i].finish, vertexList[i].father);
    for(j = 0; vertexList[i].egde[j] != 0;j++){
      printf("\tEdge %d|", vertexList[i].egde[j]);
    }
    printf("\n");
  }
  printf("-------------------\n");
}

void result(){
  int i, j;
  printf("%d\n",larger);
}