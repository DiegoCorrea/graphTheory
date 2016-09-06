# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 101
# define MAXEDGE 101

struct Vertex {
  int edge[MAXEDGE];
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();

int m = 0, n = 0;

int main() {

  scanf("%d %d", &n, &m);
  while(n != 0 && m != 0){

    makeList();
    
    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, j, v, w;

  for(i = 0; i <= n; i++){
    bzero(vertexList[i].edge, MAXEDGE*(sizeof(int)));
  }

  for(i = 0; i < m;i++){
    scanf("%d %d", &v, &w);
    
    for(j = 0;vertexList[v].edge[j] != 0;j++);
    vertexList[v].edge[j] = w;

    for(j = 0;vertexList[w].edge[j] != 0;j++);
    vertexList[w].edge[j] = v;
  }
}
void printAll(){

}