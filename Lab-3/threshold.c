#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h> 
#include <limits.h>
#include <string.h>
#include <omp.h>


void generate(int r, int c, int **arr) {
    srand(time(NULL));
    for (int i = 0; i < r; i++) { 
        for (int j = 0; j < c; j++) {
            arr[i][j] = rand() % 301;
        }
    }
}

int check(int r, int c, int **arr, int x, int per) {
    int count = 0;
    for (int i = 0; i < r; i++) {   
        for (int j = 0; j < c; j++) {
            if (arr[i][j] > x) {
                count = count + 1;
                if (count > per)
                    return count;
            }
        } 
    } 
    return count;
}

void threshold(int p, int r, int c, int **arr, int **img) {
    int prod = r * c * p;
    int x = prod / 100;
    int k; 

    #pragma omp parallel for shared(r,c,arr,img,x) private(k) num_threads(6)
    for (int i = 0; i < r; i++) {   
        for (int j = 0; j < c; j++) {
            k = arr[i][j];
            int count = check(r, c, arr, k, x);
            // printf("%d ",count);
            if (count <= x) {
                img[i][j] = 1;
            } 
            else {
                img[i][j] = 0;
            }
        } 
        // printf("\n");
    }
}

void print(int r, int c, int **arr) {
    for (int i = 0; i < r; i++) { 
        for (int j = 0; j < c; j++) {
            printf("%d ", arr[i][j]);
        } 
        printf("\n");
    }
} 

int main(int argc, char* argv[]) {
    // argv 1 is size of matrix and 2 is percentage of matrix
    int r = atoi(argv[1]);
    int c = atoi(argv[2]);
    int p = 10;

    int **matrix;
    matrix = (int **) malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++) {
        matrix[row] = (int *) malloc(c * sizeof(int));
    }  
    int **bin_img;
    bin_img = (int **) malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++) {
        bin_img[row] = (int *) malloc(c * sizeof(int));
    } 
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed; 
    

    generate(r, c, matrix);  
    printf("Original matrix:\n");
    print(r, c, matrix); 
    printf("-----------------------------------------\n");
    gettimeofday(&tv1, &tz);
    threshold(p, r, c, matrix, bin_img); 
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("%4.2lf\n",elapsed);
    printf("Binary image:\n");
    print(r, c, bin_img);
}