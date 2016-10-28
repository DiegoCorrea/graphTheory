#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100
int N;
int matadj[MAXN][MAXN];
int D[MAXN];
bool V[MAXN];

void djikstra() {
    int i,j,vs;
    memset(D, -1, sizeof(int)*N);
    memset(V, false, sizeof(int)*N);
    D[0] = 0;
    for(i=0; i<N; i++){
        vs = -1;
        for(j=0; j<N; j++)
            if (!V[j] && D[j] != -1)
                if (vs == -1 || D[j] < D[vs])
                    vs = j;
        if (vs == -1)
            break;
        V[vs] = true;
        for(j=0; j<N; j++)
            if (matadj[vs][j] != -1) {
                int v = D[vs] + matadj[vs][j];
                if (D[j] == -1 || v < D[j])
                    D[j] = v;
            }
    }
}

int main () {
    for(;;){
        scanf("%d", &N);
        if (!N) break;
        int X, Y, Z;
        memset(matadj, -1, sizeof(matadj));
        for(;;){ 
            scanf("%d %d %d", &X, &Y, &Z);
            if (!X && !Y && !Z)
                break;
            X--; Y--;
            matadj[X][Y] = Z;
            matadj[Y][X] = Z;
        }
        djikstra();
        printf("%d\n", D[N-1]);
    }
}
