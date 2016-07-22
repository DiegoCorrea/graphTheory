# include <stdio.h>
# define MAX 10

int m, n;
int adjacency[MAX][MAX] = {0};

int main(){
  int i, j, start, finish;

  printf("Quantas Vertices e Arestas tem o Grafo?\n");
  scanf("%d %d", &n, &m);

  for(i = 1;i <= m ;i++) {
    scanf("%d %d", &start, &finish);
    adjacency[start][finish]++;
    adjacency[finish][start]++;
  }

  for (i = 1; i <= n; i++) {
    printf("%d | ", i);
    for(j = 1; j <= n; j++){
      printf("%d ", adjacency[i][j]);
    }
    printf("\n");
  }

  return 0;
}