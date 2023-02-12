#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

//Returns a True or False value in terms of 0 and 1
int can_place(int rows[16], int n)
{
    for(int i = 0;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            //Checks to see if 2 queens are in the same row or not
            if(rows[i] == rows[j])
                return 0;
            //Checks to see if 2 queens are in the same diagnol or not
            if(rows[i] - rows[j] == i - j)
                return 0;
            if(rows[i] - rows[j] == j - i)
                return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    int n_queens, n_threads;
    double start_time, end_time;
    int n_solutions = 0;
    n_queens = atoi(argv[1]);//Enter the Number of Queens after .\exe <n_queens>
    n_threads = atoi(argv[2]);//Enter the Number of Threads after .\exe <n_queens> <n_threads>
    int **solutions = (int **)calloc(sizeof(int *), 1000);

    
    omp_set_num_threads(n_threads);
    int max_iter = 1;
    for(int i = 0; i<n_queens;i++)
        max_iter = max_iter*n_queens;
    
    gettimeofday(&tv1, &tz);


    int iter;
#pragma omp parallel for
    for(iter = 0;iter < max_iter;iter++)
    {
        int code = iter;
        int i;
        int chessboard[16];
        for(i = 0;i<n_queens;i++)
        {
            chessboard[i]  = code % n_queens;
            code = code/n_queens;
        }
        if(can_place(chessboard, n_queens))
        {
#pragma omp atomic
            n_solutions++;

#pragma omp critical
            {
                printf("[");
                for (i = 0; i < n_queens; i++)
                {   
                    int j;
                    for (j = 0; j < n_queens; j++)
                    {
                        if (chessboard[i] == j)	
                            printf("(%d,%d) ", j, i);
                    }
                }
                printf("]\n");
            }
        }
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("\nNumber of Solutions %d | Execution Time %4.2lf seconds\n",n_solutions ,elapsed );
    return 0;
}