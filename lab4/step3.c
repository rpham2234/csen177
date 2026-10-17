/*
Name: Richard Pham
Date: October 12, 2026
Title: Lab4 – Step 3 – Matrix multiplication with N row threads
Description: This program multiplies matrixA[N][M] by matrixB[M][L] into
matrixC[N][L] using N threads. Thread i computes the entire ith row of C.
N, M, and L are read from the command line.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int N, M, L;
double **matrixA, **matrixB, **matrixC;
pthread_t *threads;

double **initializeMatrix(int r, int c, double **matrix);
void printMatrix(int r, int c, double **matrix);
void *multiplyRow(void *arg);
void freeMatrix(double **matrix, int r);

int main(int argc, char *argv[]) {
    int i;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s N M L\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);
    if (N <= 0 || M <= 0 || L <= 0) {
        fprintf(stderr, "N, M, and L must be positive integers.\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    matrixA = initializeMatrix(N, M, matrixA);
    matrixB = initializeMatrix(M, L, matrixB);
    matrixC = initializeMatrix(N, L, matrixC);
    /* zero C; initializeMatrix fills with randoms — clear for result */
    for (i = 0; i < N; i++) {
        int j;
        for (j = 0; j < L; j++)
            matrixC[i][j] = 0.0;
    }

    threads = malloc(N * sizeof(pthread_t));
    if (threads == NULL) {
        perror("malloc threads");
        return 1;
    }

    for (i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i);

    for (i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("Matrix A (%d x %d):\n", N, M);
    printMatrix(N, M, matrixA);
    printf("\nMatrix B (%d x %d):\n", M, L);
    printMatrix(M, L, matrixB);
    printf("\nMatrix C = A * B (%d x %d):\n", N, L);
    printMatrix(N, L, matrixC);

    free(threads);
    freeMatrix(matrixA, N);
    freeMatrix(matrixB, M);
    freeMatrix(matrixC, N);
    return 0;
}

double **initializeMatrix(int r, int c, double **matrix) {
    int i, j;
    matrix = malloc(r * sizeof(double *));
    if (matrix == NULL) {
        perror("malloc rows");
        exit(1);
    }
    for (i = 0; i < r; i++) {
        matrix[i] = malloc(c * sizeof(double));
        if (matrix[i] == NULL) {
            perror("malloc cols");
            exit(1);
        }
        for (j = 0; j < c; j++)
            matrix[i][j] = (double)(rand() % 10); /* small values for readable output */
    }
    return matrix;
}

void printMatrix(int r, int c, double **matrix) {
    int i, j;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%8.1f ", matrix[i][j]);
        printf("\n");
    }
}

void *multiplyRow(void *arg) {
    int i = (int)(size_t)arg;
    int j, k;
    for (j = 0; j < L; j++) {
        double temp = 0.0;
        for (k = 0; k < M; k++)
            temp += matrixA[i][k] * matrixB[k][j];
        matrixC[i][j] = temp;
    }
    pthread_exit(0);
}

void freeMatrix(double **matrix, int r) {
    int i;
    for (i = 0; i < r; i++)
        free(matrix[i]);
    free(matrix);
}
