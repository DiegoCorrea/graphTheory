# include <stdio.h>
# define MAX 10

int m, n;
int incidencia[MAX][MAX] = {0};


int main(){
  int i, j, inicio, termino;

  printf("Quantas Vertices e Arestas tem o Grafo?\n");
  scanf("%d %d", &n, &m);

  for(i = 1;i <= m ;i++) {
    scanf("%d %d", &inicio, &termino);
    incidencia[inicio][termino]++;
    incidencia[termino][inicio]++;
  }

  for (i = 1; i <= n; i++) {
    for(j = 1; j <= n; j++){
      printf("%d ", incidencia[i][j]);
    }
    printf("\n");
  }

  return 0;
}