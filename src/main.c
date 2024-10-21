#include "common.h"
#include "assert.h"

void read_matrix(double **m, int order){
    for(int i = 0; i < order; i++)
        for(int j = 0; j < order; j++)
            scanf("%lf", &m[i][j]);
}

void print_matrix(double **m, int order){
    for(int i = 0; i < order; i++){
        for(int j = 0; j < order; j++)
            printf("%.15e ", m[i][j]);
        printf("\n");
    }
}

double** malloc_matrix(int order){
    double **m = calloc(order, sizeof *m);
    for(int i = 0; i < order; i++)
        m[i] = calloc(order, sizeof **m);

    return m;
}

void free_matrix(double **m, int order){
    for(int i = 0; i < order; i++)
        free(m[i]);
    free(m);

    return;
}

void malloc_dependencies(pLU ls){
    scanf("%d", &ls->order);

    ls->coeficientes = malloc_matrix(ls->order);
    ls->solution = malloc_matrix(ls->order);

    ls->Y = calloc(ls->order, sizeof * ls->Y);
    ls->X = calloc(ls->order, sizeof * ls->X);
    ls->B = calloc(ls->order, sizeof * ls->B);
    ls->access_mask = calloc(ls->order, sizeof * ls->access_mask);
    
    return;
}

void free_dependencies(pLU ls){
    free_matrix(ls->coeficientes, ls->order);
    free_matrix(ls->solution, ls->order);
    free(ls->Y);
    free(ls->B);
    free(ls->X);

    return;
}

void init_LU(pLU ls){
    malloc_dependencies(ls);

    read_matrix(ls->coeficientes, ls->order);
    
    for(int i = 0; i < ls->order; i++)
        ls->access_mask[i] = i;
    
    return;
}


void partial_pivoting(double **A, int i, int order, int *mask){
    int aux, max_index = i, max = access_m(A, i, i);
    for(int j = 0; j < order; j++){
        if(access_m(A, j, i) > max){
            max = access_m(A, j,i);
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
            for (int j = i+1; j <order; j++)
                access_m(A, k, j) -= access_m(A, i, j) * m; 
        }
    }
}

void copy_result_to_solution(pLU ls, int column){
    for(int i = 0; i < ls->order; i++){
        ls->solution[i][column] = ls->X[i];
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

int main(){
    
    LU ls;

    init_LU(&ls);

    find_inverse(&ls);
    
    print_matrix(ls.solution, ls.order);

    free_dependencies(&ls); 
    return 0;
}
