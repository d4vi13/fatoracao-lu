#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

#include "common.h"

void copy_result_to_solution(pLU ls, int column){
    for(int i = 0; i < ls->order; i++){
        ls->solution[i][column] = ls->X[i];
    }
}

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
}

void copy_matrix(int n, double** source, double** destination) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

void multiply_matrices(int n, double** A, double** B) {
    double result[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = result[i][j];
        }
    }
}

void subtract_identity(int n, double** A){
    for(int i = 0; i < n; i++)
        A[i][i] -= 1.0;
}

rtime_t timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (rtime_t) tp.tv_sec*1.0e3 + (rtime_t) tp.tv_nsec*1.0e-6 );
}

