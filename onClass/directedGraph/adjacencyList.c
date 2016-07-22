# include <stdio.h>
# include <stdlib.h>
# define MAX 10

int m, n;

struct Vertex {
  int id;
  Vertex *next;
};

Vertex *vertexList[MAX];

void makeList(int);
void addVertex(int n, int start, int finish);

int main() {
  int i, j;
  int start, finish;
  Vertex *walker;

  printf("Quantas Vertices e Arestas tem o Grafo?\n");
  scanf("%d %d", &n, &m);

  makeList(n);

  for(i = 1; i <= m; i++) {
    scanf("%d %d", &start, &finish);
    addVertex(n,start,finish);
  }

  for (i = 1; i <= n; i++) {
    printf("Vertice: %d |", vertexList[i]->id);
    for(walker = vertexList[i]->next;walker != NULL ;walker = walker->next) {
      printf("%d -> ", walker->id);
    }
    printf("NULL\n");
  }

  return 0;
}

void makeList(int n) {
  int i;

  for(i = 1; i <= n ;i++) {
    vertexList[i] = (Vertex*)malloc(sizeof(Vertex));
    vertexList[i]->id = i;
    vertexList[i]->next = NULL;
  }
}

void addVertex(int n, int start, int finish) {
  int i;
  Vertex *newVertex, *walker;

  newVertex = (Vertex*)malloc(sizeof(Vertex));
  newVertex->id = finish;
  newVertex->next = NULL;
  
  if(vertexList[start]->next == NULL) {
    vertexList[start]->next = newVertex;
  } else {
    walker = vertexList[start]->next;
    for(;walker->next != NULL ;walker = walker->next);
    walker->next = newVertex;
  }
}