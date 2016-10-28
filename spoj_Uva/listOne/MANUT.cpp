# include <stdio.h>
# include <vector>
# include <queue>

# define WHITE 0
# define GRAY 1
# define BLACK 2

# define MAXVERTEX 401

# define NIL -1

# define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct Vertex {
  int color;
  int time;
  int low;
  int father;
  bool cut;
  int edgeCount;
  std::vector<int> edge;
}Vertex;

struct Vertex vertexList[MAXVERTEX];

int m = 0, n = 0;
int teste = 0, countTime = 0;

void makeList();
void printAll();
void dfsVisit(int u);
void dfs();
int main() {

  scanf("%d %d", &n, &m);
  while(n != 0){
    teste++;
    makeList();

    dfs();

    printAll();

    scanf("%d %d", &n, &m);
  }

  return 0;
}

void makeList() {
  int i, v, w;
  
  for(i = 0; i <= n; i++){
    vertexList[i].color = WHITE;
    vertexList[i].low = 0;
    vertexList[i].time = 0;
    vertexList[i].cut = false;
    vertexList[i].edgeCount = 0;
    vertexList[i].father = NIL;
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

void printAll(){
  std::queue<int> queueVertex;

  if(teste > 1)
    printf("\n");
  printf("Teste %d\n", teste);

  for(int i = 0; i <= n;i++){
    if(vertexList[i].cut == true)
      queueVertex.push(i);
  }
  if (queueVertex.empty()) {
    printf("nenhum");
  }else{
    while(!queueVertex.empty()){
      printf("%d ", queueVertex.front());
      queueVertex.pop();
    }
  }

  printf("\n");
}

void dfsVisit(int father){
  int dfschild = 0;
  countTime++;
  vertexList[father].low = countTime;
  vertexList[father].time = countTime;
  vertexList[father].color = GRAY;

  for(int i = 0, son = 0; i < vertexList[father].edge.size(); i++){
    son = vertexList[father].edge[i];

    if(vertexList[son].color == WHITE){
      dfschild++;
      vertexList[son].father = father;
      dfsVisit(son);

      vertexList[father].low = MIN(vertexList[father].low,vertexList[son].low);

      if(vertexList[father].father != NIL && vertexList[son].low >= vertexList[father].time){
        vertexList[father].cut = true;
      }
      if(vertexList[father].father == NIL && dfschild > 1){
        vertexList[father].cut = true;
      }
    } else if(vertexList[father].father != son){
        vertexList[father].low = MIN(vertexList[father].low,vertexList[son].time);
      }
  }
  vertexList[father].color = BLACK;
}

void dfs(){
  countTime = 0;

  for(int i = 0; i <= n;i++){
    if(vertexList[i].color == WHITE)
      dfsVisit(i);
  }
}