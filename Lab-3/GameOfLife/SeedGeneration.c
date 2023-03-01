#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>

void seed(int r,int c,int **arr)
{
    #pragma omp parallel for
    for(int i=0;i<r;i++)
    { 
        for(int j=0;j<c;j++)
        { 
            arr[i][j] = rand()%2;
        }
    }

} 

void print_array(int r,int c, int **arr)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
} 

int main(int argc,char *argv[])
{
    int r = atoi(argv[1]); 
    int c = atoi(argv[2]);
    int **board;
    board = (int **)malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++)
    {
        board[row] = (int *)malloc(c * sizeof(int));
    } 

    int **dup;
    dup = (int **)malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++)
    {
        dup[row] = (int *)malloc(c * sizeof(int));
    }  


    seed(r,c,board);
   // print_array(r,c,board);
    char *filename = argv[3];
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    fprintf(fp, "%d %d\n", r, c);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            fprintf(fp, "%d ", board[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return 0;
 }