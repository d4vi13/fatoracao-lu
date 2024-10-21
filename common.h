#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>
#include <likwid.h>

struct LU{

    union{
        double** L;
        double** U;
        double** coeficientes;
    };

    double* Y;
    double* X;
    double* B; 
    
    int* access_mask;

    int order;
    double error;

    double** solution; 
    double** original; 
};

typedef struct LU LU, *pLU;

//#define GET_MACRO(_1,_2,_3,NAME,...) NAME
//#define access(...) GET_MACRO(__VA_ARGS__, access_LU, access_vector)(__VA_ARGS__)
 
#define access_m(A, i, j) A[mask[i]][j]
#define access(A, i ,j) (A)[(A)->access_mask[i]][j]
#define accessU(ls, i, j) ls->U[ls->access_mask[i]][j]
#define accessL(ls, i, j) ls->L[ls->access_mask[i]][j]
#endif

