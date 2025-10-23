#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "basic_matrix_multiplier.h"

double **allocate_matrix(int n) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    if (!matrix) return NULL;
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) {
               free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(double **matrix, int n) {
    if (!matrix) return;
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void generate_matrices(double **A, double **B, int n) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = ((double)rand() / RAND_MAX) * 100.0;
            B[i][j] = ((double)rand() / RAND_MAX) * 100.0;
        }
    }
}

void multiply(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}