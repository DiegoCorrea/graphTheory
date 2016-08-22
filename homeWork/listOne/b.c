# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2

const int MAXVERTEX = 2001;
const int MAXEDGE = 2000;
int m, n, s = 1, queue[MAXVERTEX] = {0};

struct Vertex {
  int color;
  int time;
  int father;
  int egde[MAXEDGE];
};

Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void bfs();

int main() {
  int i, j;

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){
    makeList();
    
    bfs();

    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, v, w, p;

  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].time = 0;
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

void bfs(){
  int i, nq = 0, u, v;
  vertexList[s].color = GRAY;
  vertexList[s].time = 0;

  nq++;
  queue[nq] = s;
  
  while(nq != 0){
    u = queue[nq];
    nq--;

    for(i = 0;vertexList[u].egde[i] != 0;i++){
      v = vertexList[u].egde[i];

      if(vertexList[v].color == WHITE){
        vertexList[v].color = GRAY;
        vertexList[v].time = vertexList[u].time++;
        vertexList[v].father = u;
        nq++;
        queue[nq] = v;
      }
    }
    vertexList[u].color = BLACK;
  }
}

void printAll(){
  int i, j;
  for(i = 1; i <= n;i++){
    printf("ID: %d | Color: %d | Time: %d| Father: %d\n", i,vertexList[i].color, vertexList[i].time, vertexList[i].father);
    for(j = 0; vertexList[i].egde[j] != 0;j++){
      printf("\tEdge %d|", vertexList[i].egde[j]);
    }
    printf("\n");
  }
  printf("-------------------\n");
}