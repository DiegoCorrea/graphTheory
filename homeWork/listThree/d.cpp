# include <iostream>
# include <vector>
# include <algorithm>

# include <stdio.h>
using namespace std;

# define MAXVERTEX 101
# define INFINITE 999999
# define STARTVertex 0

class Graph {
  int numberOfVertex;
  //std::vector< std::vector<int> > distanceMatrix;
  int distanceMatrix[MAXVERTEX][MAXVERTEX];
  int distanceMatrixResult[MAXVERTEX][MAXVERTEX];

  public:
    
    Graph(int numberOfVertex){
      this->numberOfVertex = numberOfVertex;
    }
    void initialize(){
      printf("initialize\n");
      for(int i = STARTVertex; i <= numberOfVertex; i++){
        for (int j = STARTVertex; j <= numberOfVertex; ++j){
          distanceMatrix[i][j] = INFINITE;
          if(i == j){
            distanceMatrix[i][j] = 0;
          }
        }
      }
      printf("initialize finish\n");
    }

    void printMatrix(){
      printf("imprimindo matriz\n");
      for(int i = STARTVertex; i <= numberOfVertex; i++){
        for (int j = STARTVertex; j <= numberOfVertex; ++j){
          printf("%d ",distanceMatrix[i][j]);
        }
        printf("\n");
      }
    }

    void addConection(int origin, int master, int distance){
      distanceMatrix[origin][master] = distance;
    }
    void copyMatrix(){
      for(int i = STARTVertex; i <= numberOfVertex; i++){
        for (int j = STARTVertex; j <= numberOfVertex; ++j){
          distanceMatrixResult[i][j] = distanceMatrix[i][j];
        }
      }
    }
    void floydWarshall(){
      //int distanceMatrixResult[MAXVERTEX][MAXVERTEX];
      copyMatrix();
      for(int k = STARTVertex; k <= this->numberOfVertex; k++){
        for(int i = STARTVertex; i <= this->numberOfVertex; i++){
          for(int j= STARTVertex; j <= this->numberOfVertex; j++){
            if(distanceMatrixResult[i][j] > distanceMatrixResult[i][k] + distanceMatrixResult[k][j]){
              distanceMatrixResult[i][j] = distanceMatrixResult[i][k] + distanceMatrixResult[k][j];
            }
          }
        }
        //copyMatrix();
      }
    }
};

int main(){
  int n = 1, m = 1;
  int origin, master, distance;


  scanf("%d %d", &n, &m);
  
  Graph g(n);
  g.initialize();
  g.printMatrix();

  for(int i = 0; i < m; i++){
    scanf(" %d %d %d", &origin, &master, &distance);
    g.addConection(origin, master, distance);
  }
  printf("\n");
  g.printMatrix();
  g.floydWarshall();
  printf("\n");
  g.printMatrix();
  return 0;
}