#include "init.h"





void read_matrix(double **m, int order){
    for(int i = 0; i < order; i++){
        for(int j = 0; j < order; j++){
            scanf("%lf", &m[i][j]);
        }
    }
}
