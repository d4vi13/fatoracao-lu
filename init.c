#include "init.h"
#include "utils.h"

void malloc_dependencies(pLU ls){
    scanf("%d", &ls->order);

    ls->coeficientes = malloc_matrix(ls->order);
    ls->original = malloc_matrix(ls->order);
    ls->solution = malloc_matrix(ls->order);

    ls->Y = calloc(ls->order, sizeof * ls->Y);
    ls->X = calloc(ls->order, sizeof * ls->X);
    ls->B = calloc(ls->order, sizeof * ls->B);
    ls->access_mask = calloc(ls->order, sizeof * ls->access_mask);
}

void free_dependencies(pLU ls){
    free_matrix(ls->coeficientes, ls->order);
    free_matrix(ls->solution, ls->order);
    free(ls->Y);
    free(ls->B);
    free(ls->X);
    free(ls->access_mask);
}

void init_LU(pLU ls){
    malloc_dependencies(ls);

    read_matrix(ls->coeficientes, ls->order);
    copy_matrix(ls->order, ls->coeficientes, ls->original);

    for(int i = 0; i < ls->order; i++)
        ls->access_mask[i] = i;
}

