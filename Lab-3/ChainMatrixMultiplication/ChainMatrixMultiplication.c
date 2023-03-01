#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include <omp.h>

typedef struct Matrix {
    int rows;
    int cols;
    int** ele;
} Matrix;

Matrix* createMatrix(int rows, int cols) {
    Matrix* mat = (Matrix*) malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->ele = (int**) malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++) {
        mat->ele[i] = (int*) calloc(cols, sizeof(int));
    }
    return mat;
}



void freeMatrix(Matrix* mat) {
    for(int i=0; i<mat->rows; i++) {
        free(mat->ele[i]);
    }
    free(mat->ele);
    free(mat);
}

void readMatrix(Matrix* mat) {
    for(int i=0; i<mat->rows; i++) {
        for(int j=0; j<mat->cols; j++) {
            mat->ele[i][j] = 1;
        }
    }
}

Matrix* multiply(Matrix* mat1, Matrix* mat2, int num_threads) {
    Matrix* res = createMatrix(mat1->rows, mat2->cols);
    #pragma omp parallel for num_threads(num_threads)
    for(int i=0; i<mat1->rows; i++) {
        for(int j=0; j<mat2->cols; j++) {
            for(int k=0; k<mat1->cols; k++) {
                res->ele[i][j] += mat1->ele[i][k] * mat2->ele[k][j];
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    int num_threads= atoi(argv[1]);
    struct timeval tv1, tv2;
    struct timezone tz;
    

    int n = 10;
    int* p = (int*) malloc((n+1) * sizeof(int));
    for(int i=0; i<=n; i++) {
        p[i] = 1000;
    }

    Matrix** matrices = (Matrix**) malloc(n * sizeof(Matrix*));
    for(int i=0; i<n; i++) {
        matrices[i] = createMatrix(p[i], p[i+1]);
        readMatrix(matrices[i]);
    }

    Matrix* temp = multiply(matrices[0], matrices[1], num_threads);
     gettimeofday(&tv1, &tz);
    for(int i=2; i<n; i++) {
      
        Matrix* res = multiply(temp, matrices[i], num_threads);
        freeMatrix(temp);
        temp = res;
    }
    gettimeofday(&tv2, &tz);

    double elapsed_time = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("Elapsed time = %f seconds |no.of threads is %d\n", elapsed_time, atoi(argv[1]));

    free(p);
    free(matrices);

  
    freeMatrix(temp);

    return 0;
}