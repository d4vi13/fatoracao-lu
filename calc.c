#include "calc.h"
#include "utils.h"
#include <math.h>

// Realiza o pivoteamento parcial de uma matriz
void partial_pivoting(double **A, int i, int order, int *mask){
    int aux, max_index = i, max = access_m(A, i, i);
    for(int j = 0; j < order; j++){
        if(access_m(A, j, i) > max){
            max = access_m(A, j, i);
            max_index = j;
        }
    }
    aux = mask[i];
    mask[i] = mask[max_index];
    mask[max_index] = aux;
}

void fatoracaoLU(double **A, int order, int *mask){
    for (int i = 0; i < order; i++){
        partial_pivoting(A, i, order, mask);

        for (int k = i+1; k < order; k++) {
            double m = access_m(A, k, i) / access_m(A, i, i);
            access_m(A, k, i) = m;
            for (int j = i+1; j < order; j++)
                access_m(A, k, j) -= access_m(A, i, j) * m; 
        }
    }
}

void resolveSL(pLU ls){
    for (int i = 0; i < ls->order; i++) {
        ls->Y[ls->access_mask[i]] = ls->B[ls->access_mask[i]];
        for (int j = 0; j < i; j++)
            ls->Y[ls->access_mask[i]] -= accessL(ls, i, j)*ls->Y[ls->access_mask[j]];
    }

    for (int i = ls->order-1; i >= 0; --i) {
        ls->X[ls->access_mask[i]] = ls->Y[ls->access_mask[i]];
        for (int j = i+1; j < ls->order; j++)
            ls->X[ls->access_mask[i]] -= accessU(ls, i, j) * ls->X[ls->access_mask[j]];
        ls->X[ls->access_mask[i]] /= accessU(ls, i, i);
    }
}

void find_inverse(pLU ls){
    fatoracaoLU(ls->coeficientes, ls->order, ls->access_mask);

    for(int i = 0; i < ls->order; i++){
        ls->B[i] = 1;
        resolveSL(ls);
        copy_result_to_solution(ls, i);
        ls->B[i] = 0;
    }
}

double normaL2(double** A, int n, int line){
    double norma = 0;
    for(int i = 0; i < n; i++)
        norma += A[line][i]*A[line][i];
    return sqrt(norma);
}

void calculate_error(pLU ls){
    double media = 0;
    multiply_matrices(ls->order, ls->original, ls->solution);
    subtract_identity(ls->order, ls->original);
    
    for(int i = 0; i < ls->order; i++)
        media += normaL2(ls->original, ls->order, i);
    media /= ls->order;

    ls->error = media;
}

