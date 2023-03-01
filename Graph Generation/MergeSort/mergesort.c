```
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define n 4000000

void merge(float *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    float *L = (float *)calloc(n1, sizeof(float));
    float *R = (float *)calloc(n2, sizeof(float));
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(float *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        if (r - l < 100000)
        {
            merge(arr, l, m, r);
        }
        else
        {
#pragma omp task shared(arr)
            mergeSort(arr, l, m);
#pragma omp task shared(arr)
            mergeSort(arr, m + 1, r);
#pragma omp taskwait
            merge(arr, l, m, r);
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j;
    float *arr = (float *)calloc(n, sizeof(float));
    float elapsed[16];
    double start_time, end_time;
    struct timeval tv1, tv2;
    struct timezone tz;

    for (i = 0; i < n; i++)
    {
        arr[i] = (float)rand() / RAND_MAX;
    }

    for (int num_threads = 1; num_threads <= 16; num_threads++)
    {
        omp_set_num_threads(num_threads);
        double avg = 0;
        for (i = 0; i < 5; i++)
        {
            // start_time = omp_get_wtime();
             gettimeofday(&tv1, &tz);

#pragma omp parallel shared(arr) num_threads(num_threads)
#pragma omp single
            mergeSort(arr, 0, n - 1);

            // end_time = omp_get_wtime();
             gettimeofday(&tv2, &tz);

            // double elapsed_time = end_time - start_time;
              double elapsed_time = ((double)(tv2.tv_sec - tv1.tv_sec) + (double)(tv2.tv_usec - tv1.tv_usec) * 1.e-6)*10;
            printf("Elapsed time = %f seconds | No. of threads = %d\n", elapsed_time, num_threads);
            avg += elapsed_time;
        }
        avg = avg / 5.0;
        printf("Average time elapsed for %d threads: %f\n", num_threads, avg);
        elapsed[num_threads-1] = avg;
        j++;
    }

    free(arr);
    return 0;
}
```