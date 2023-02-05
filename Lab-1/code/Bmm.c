#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <sys/time.h>
int main(int argc, char *argv[])
{
  struct timeval tv1, tv2;
  struct timezone tz;
  double elapsed;
  int i, j, k,ii,kk,jj;

  int n = atoi(argv[1]);
  int c = 2;
  double **A = (double **)calloc(sizeof(double *), n);
  double **B = (double **)calloc(sizeof(double *), n);
  double **C = (double **)calloc(sizeof(double *), n);
  for (i = 0; i < n; i++)
  {
    A[i] = (double *)calloc(n, sizeof(double));
    B[i] = (double *)calloc(n, sizeof(double));
    C[i] = (double *)calloc(n, sizeof(double));
  }
  omp_set_num_threads(atoi(argv[2]));
  gettimeofday(&tv1, &tz);
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      A[i][j] = (double)rand() / (double)RAND_MAX;
      B[i][j] = A[i][j];
    }
  }
  int b = 4;
  while (b <=64)
  {
    c=2;
    while (c < 17)
    {
#pragma omp parallel for private(i, j, k,ii,jj,kk) shared(A, B, C)
      // block matrix mulitplication

      for (int ii = 0; ii < n; ii += b)
      {
        for (int jj = 0; jj < n; jj += b)
        {
          for (int kk = 0; kk < n; kk += b)
          {
            for (int i = ii; i < ii + b; ++i)
            {
              for (int j = jj; j < jj + b; ++j)
              {
                for (int k = kk; k < kk + b; ++k)
                {
                  C[i][j] += A[i][k] * B[k][j];
                }
              }
            }
          }
        }
      }
      // block matrix multiplication
      for (int i = 0; i < n; ++i)
      {
        for (int j = 0; j < n; ++j)
        {
          A[i][j] = C[i][j];
        }
      }
      gettimeofday(&tv2, &tz);
      elapsed = (double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6;
      printf("elapsed time = %4.2lf | seconds power is %d | number of threads is %d | block size is %d\n", elapsed, c, atoi(argv[2]), b);
      c++;
    }
    b = b * 2;
  }
}