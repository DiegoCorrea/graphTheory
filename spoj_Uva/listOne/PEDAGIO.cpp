# include <stdio.h>
# include <vector>
# include <queue>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 51

typedef struct Vertex {
  int color;
  int countDistance;
  int edgeCount;
  std::vector<int> edge;
}Vertex;

struct Vertex vertexList[MAXVERTEX];

void makeList();
void printAll();
void bfs();

  
int m = 0, n = 0, s = 0, p = 0;
int teste = 0;
std::queue<int> queueVertex;

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
    vertexList[i].edge.clear();
  }

  for(i = 0; i < m;i++){
    scanf("%d %d", &v, &w);

    vertexList[v].edge.push_back(w);
    vertexList[v].edgeCount++;

    vertexList[w].edge.push_back(v);
    vertexList[w].edgeCount++;
  }
}

void bfs(){
  int i, u, v;

  vertexList[s].color = GRAY;
  vertexList[s].countDistance = 0;

  queueVertex.push(s);

  while(!queueVertex.empty()){
    u = queueVertex.front();
    queueVertex.pop();

    for(i = 0;i < vertexList[u].edgeCount;i++){
      v = vertexList[u].edge[i];

      if(vertexList[v].color == WHITE || vertexList[u].countDistance + 1 < vertexList[v].countDistance){
        vertexList[v].color = GRAY;
        vertexList[v].countDistance = vertexList[u].countDistance + 1;

        queueVertex.push(v);
      }
    }
    vertexList[u].color = BLACK;
  }
}

void printAll(){
  if(teste > 1)
    printf("\n");
  printf("Teste %d\n", teste);

  for(int i = 0; i <= n;i++){
    if(vertexList[i].countDistance <= p && i != s && vertexList[i].countDistance != 0)
      queueVertex.push(i);
  }

  while(!queueVertex.empty()){
    printf("%d ", queueVertex.front());
    queueVertex.pop();
  }

  printf("\n");
}