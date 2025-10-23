#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../basic_matrix/basic_matrix_multiplier.h"
#define DELTA 1e-10

int assert_matrix_almost_equal(double **expected, double **actual, int n, double delta) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fabs(expected[i][j] - actual[i][j]) > delta) {
                printf("Mismatch at [%d][%d]: expected %.10f, got %.10f\n", i, j, expected[i][j], actual[i][j]);
                return 0;
            }
        }
    }
    return 1;
}

void test_multiply() {
    printf("Running test_multiply...\n");
    int n = 2;
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **expected = allocate_matrix(n);
    double **result = allocate_matrix(n);
    if (!A || !B || !expected || !result) {
        printf("test_multiply FAILED: Memory allocation error\n");
        return;
    }
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;
    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;
    expected[0][0] = 19; expected[0][1] = 22;
    expected[1][0] = 43; expected[1][1] = 50;
    multiply(A, B, result, n);
    if (assert_matrix_almost_equal(expected, result, n, DELTA))
        printf("test_multiply PASSED\n");
    else
        printf("test_multiply FAILED\n");
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(expected, n);
    free_matrix(result, n);
}

void test_generate_matrices_shape() {
    printf("Running test_generate_matrices_shape...\n");
    int n = 5;
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    if (!A || !B) {
        printf("test_generate_matrices_shape FAILED: Memory allocation error\n");
        return;
    }
    generate_matrices(A, B, n);
    int passed = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] < 0.0 || A[i][j] > 100.0 || B[i][j] < 0.0 || B[i][j] > 100.0) {
                passed = 0;
                printf("Value out of range at [%d][%d]: A=%.2f, B=%.2f\n", i, j, A[i][j], B[i][j]);
                break;
            }
        }
        if (!passed) break;
    }
    if (passed)
        printf("test_generate_matrices_shape PASSED\n");
    else
        printf("test_generate_matrices_shape FAILED\n");
    free_matrix(A, n);
    free_matrix(B, n);
}

void test_random_matrices_multiplication() {
    printf("Running test_random_matrices_multiplication...\n");
    int n = 3;
    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **result = allocate_matrix(n);
    if (!A || !B || !result) {
        printf("test_random_matrices_multiplication FAILED: Memory allocation error\n");
        return;
    }
    generate_matrices(A, B, n);
    multiply(A, B, result, n);
    int correct_shape = 1;
    for (int i = 0; i < n; ++i) {
        if (!A[i] || !B[i] || !result[i]) {
            correct_shape = 0;
            break;
        }
    }
    if (correct_shape)
        printf("test_random_matrices_multiplication PASSED\n");
    else
        printf("test_random_matrices_multiplication FAILED\n");
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

int main() {
    printf("===========================================\n");
    printf("Running C Matrix Multiplication Tests\n");
    printf("===========================================\n\n");
    test_multiply();
    test_generate_matrices_shape();
    test_random_matrices_multiplication();
    printf("\n===========================================\n");
    printf("All tests completed\n");
    printf("===========================================\n");
    return 0;
}