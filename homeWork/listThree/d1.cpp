# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>

# define MAXVERTEX 101
# define VERTEXSTART 0

# define INFINITY 99999

void initialize(int resultanceMatrix[][MAXVERTEX], int size);
void printSolution(int result[][MAXVERTEX], int size);
int searchSolution(int resultanceMatrix[][MAXVERTEX], int size);

void floydWarshall (int resultanceMatrix[][MAXVERTEX], int size){
	int result[MAXVERTEX][MAXVERTEX], i, j, k;

	for (i = VERTEXSTART; i < size; i++)
		for (j = VERTEXSTART; j < size; j++)
			result[i][j] = resultanceMatrix[i][j];

	for (k = VERTEXSTART; k < size; k++){
		for (i = VERTEXSTART; i < size; i++){
			for (j = VERTEXSTART; j < size; j++){
				if (result[i][k] + result[k][j] < result[i][j])
					result[i][j] = result[i][k] + result[k][j];
			}
		}
	}
	//printSolution(result, size);
	for (i = VERTEXSTART; i < size; i++)
		for (j = VERTEXSTART; j < size; j++)
			resultanceMatrix[i][j] = result[i][j];
}

void printSolution(int result[][MAXVERTEX], int size){
	for (int i = VERTEXSTART; i < size; i++){
		for (int j = VERTEXSTART; j < size; j++){
			if (result[i][j] == INFINITY)
				printf("%7s", "INF");
			else
				printf ("%7d", result[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int resultanceMatrix[MAXVERTEX][MAXVERTEX] = {INFINITY};
	int n = 1, m = 1;
  int origin, master, resultance;


  scanf("%d %d", &n, &m);

  initialize(resultanceMatrix, n);

  for(int i = 0; i < m; i++){
    scanf(" %d %d %d", &origin, &master, &resultance);
    resultanceMatrix[origin][master] = resultance;
    resultanceMatrix[master][origin] = resultance;
  }

	floydWarshall(resultanceMatrix,n);
	printf("%d\n", searchSolution(resultanceMatrix,n));
	return 0;
}


void initialize(int resultanceMatrix[][MAXVERTEX], int size){
	for (int i = VERTEXSTART; i < size; i++)
		for (int j = VERTEXSTART; j < size; j++){
			resultanceMatrix[i][j] = INFINITY;
			if(i == j)
				resultanceMatrix[i][j] = 0;
		}
}

int searchSolution(int resultanceMatrix[][MAXVERTEX], int size){
	int value = INFINITY;
	for (int i = VERTEXSTART; i < size; i++){
		int lineResult;
		lineResult = resultanceMatrix[i][0];
		for (int j = VERTEXSTART; j < size; j++){
			if(resultanceMatrix[i][j] != INFINITY && resultanceMatrix[i][j] != 0 && resultanceMatrix[i][j] > lineResult){
				lineResult = resultanceMatrix[i][j];
			}
		}
		if(lineResult < value){
			value = lineResult;
		}
	}
	return value;
}