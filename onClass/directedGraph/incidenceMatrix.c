# include <stdio.h>
# define MAX 10

int m, n;
int incidence[MAX][MAX] = {0};

int main(){
  int i, j, start, finish;

  printf("Quantas Vertices e Arestas tem o Grafo?\n");
  scanf("%d %d", &n, &m);

  for(i = 1;i <= m ;i++) {
    scanf("%d %d", &start, &finish);
    incidence[start][i]++;
    incidence[finish][i]--;
  }

  for (i = 1; i <= n; i++) {
    printf("%d | ", i);
    for(j = 1; j <= m; j++){
      printf("%d ", incidence[i][j]);
    }
    printf("\n");
  }

  return 0;
}