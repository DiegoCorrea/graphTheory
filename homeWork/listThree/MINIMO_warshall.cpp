# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>

# define MAXVERTEX 102
# define VERTEXSTART 0

# define INFINITY 99999

void initialize(int resultanceMatrix[MAXVERTEX][MAXVERTEX][MAXVERTEX], int size);
void printSolution(int result[MAXVERTEX][MAXVERTEX][MAXVERTEX], int start, int finish, int cities);
void printMatrix(int result[MAXVERTEX][MAXVERTEX][MAXVERTEX], int size, int cities);

void floydWarshall (int resultanceMatrix[MAXVERTEX][MAXVERTEX][MAXVERTEX], int size){
	int result[size+1][size+1], i, j, k;

	for (i = VERTEXSTART; i <= size; i++)
		for (j = VERTEXSTART; j <= size; j++)
			result[i][j] = resultanceMatrix[0][i][j];

	for (k = 1; k <= size; k++){
		for (i = VERTEXSTART; i <= size; i++){
			for (j = VERTEXSTART; j <= size; j++){
				if (result[i][k] + result[k][j] < result[i][j]){
					result[i][j] = result[i][k] + result[k][j];
				}
			}
		}
		for (i = VERTEXSTART; i <= size; i++){
			for (j = VERTEXSTART; j <= size; j++){
				resultanceMatrix[k][i][j] = result[i][j];
			}
		}
	}
}

void printSolution(int result[MAXVERTEX][MAXVERTEX][MAXVERTEX], int start, int finish, int cities, int size){
	if(result[cities][start][finish] != INFINITY){
		printf("%d\n", result[cities][start][finish]);
	}else{
		printf("-1\n");
	}
}

void printMatrix(int result[MAXVERTEX][MAXVERTEX][MAXVERTEX], int size, int cities){
	for(int k = 0; k <= cities; k++){
		printf("-------------------------------\n");
		for (int i = VERTEXSTART; i <= size; i++){
			for (int j = VERTEXSTART; j <= size; j++){
				if (result[k][i][j] == INFINITY)
					printf("%7s", "INF");
				else
					printf ("%7d", result[k][i][j]);
			}
			printf("\n");
		}
	}
}

int main(){
	int resultanceMatrix[MAXVERTEX][MAXVERTEX][MAXVERTEX];
	int n, m;
  int origin, master, distance, lookTrip, cityDistance, test = 0;
  
  while(scanf("%d %d", &n, &m) != EOF){
	  if(test >= 1)
      printf("\n");
    test++;

	  initialize(resultanceMatrix, n);

	  for(int i = 0; i < m; i++){
	    scanf("%d %d %d", &origin, &master, &distance);
	    if(resultanceMatrix[0][origin][master] > distance)
	    	resultanceMatrix[0][origin][master] = distance;
	  }

		floydWarshall(resultanceMatrix,n);

		printf("Instancia %d\n", test);
    scanf("%d", &lookTrip);
    for(int i = 0; i < lookTrip;i++){
      scanf(" %d %d %d", &origin, &master, &cityDistance);
      printSolution(resultanceMatrix,origin,master,cityDistance,n);
    }
	}
	return 0;
}

void initialize(int resultanceMatrix[MAXVERTEX][MAXVERTEX][MAXVERTEX], int size){
	for(int k = 0; k <= size;k++){
		for (int i = VERTEXSTART; i <= size; i++){
			for (int j = VERTEXSTART; j <= size; j++){
				resultanceMatrix[k][i][j] = INFINITY;
				if(i == j)
					resultanceMatrix[k][i][j] = 0;
			}
		}
	}
}