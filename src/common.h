#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>


struct LU{

    union{
        double** L;
        double** U;
        double** coeficientes;
    };

    double* Y;
    double* X;
    

    int order;
    double error;

    double** solution; 
}

typedef struct LU LU, *pLU;

#endif

