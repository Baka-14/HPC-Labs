#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h> 
#include <limits.h>
#include <string.h>
#include <omp.h>


void generate(int r, int c, int **arr) 
{
    srand(time(NULL));
    for (int i = 0; i < r; i++) 
    { 
        for (int j = 0; j < c; j++) 
        {
            arr[i][j] = rand() % 301;
        }
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
    int r = atoi(argv[1]);
    int c = atoi(argv[2]);
    int **matrix;
    matrix = (int **) malloc(r * sizeof(int *));
    // matrix allocation
    for (int row = 0; row < r; row++) 
    {
        matrix[row] = (int *) malloc(c * sizeof(int));
    } 
    generate(r, c, matrix);
    char *filename = argv[3];
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    fprintf(fp, "%d %d\n", r, c);
    for (int i = 0; i < r; i++) 
    {
        for (int j = 0; j < c; j++) 
        {
            fprintf(fp, "%d ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return 0;
}