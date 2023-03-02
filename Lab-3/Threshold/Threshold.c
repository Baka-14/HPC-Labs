#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<math.h>
#include<string.h>
#include<limits.h>
#include<omp.h>

//void generate(int n,int** arr){ 
 //   srand(time(NULL));
 //   #pragma omp parallel for
 //   for(int i=0;i<n;i++)
  //  { 
  //      for(int j=0;j<n;j++)
 //       {
  //          arr[i][j]=rand() % 51;
  //      }
 //   }
//}  

void count_distribution(int* arr,int** image,int r,int c){
    #pragma omp parallel for collapse(3)
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            for(int k=0;k<=300;k++)
            {       
                if(image[i][j]==k)
                    {
                        arr[k]=arr[k]+1;
                    }
            }
        }
    }
} 

int cutoff(int *arr,float p,int r,int c){
    int x=(r*c)*(p/100);
    //printf("%d\n",x);
    int c=0;
    int value=0;

    for(int i=300;i>-1 ;i--)
    { 
        c=c+arr[i];
        if(c>=x)
        {   
            if(c==x)
            {
                return i;
            }
            else
            {
                return i-1;
            }
        } 
    }

}


void threshold(int r,int c,int** org,int** bin_img,int value){
    #pragma omp parallel for collapse(2)
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(org[i][j]>=value)
            {
                bin_img[i][j]=1;
            }

            else
            {
                bin_img[i][j]=0;
            }
        }

    }

}

void print(int r,int c,int** arr){
   for(int i=0;i<r;i++)
    { 
        for(int j=0;j<c;j++)
        {
            printf("%d ",arr[i][j]);
        } 
        printf("\n");
    }
} 

int main(int argc, char *argv[]){
    //argv 1 is size of matrix and 2 is percentage of matrix
    int r;
    int c;
    float p=atof(argv[2]); 
    int th=atoi(argv[3]);
    omp_set_num_threads(th);
    // int n=8192;
    // float p=10.0;

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed; 
    double sum=0.0;

    int **matrix;
    matrix = (int **)malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++)
    {
        matrix[row] = (int *)malloc(c * sizeof(int));
    }  

    int **bin_img;
    bin_img = (int **)malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++)
    {
        bin_img[row] = (int *)malloc(c * sizeof(int));
    }  

    int arr[301]={0};
    //generate(n,matrix);  
    //print(n,matrix);
    gettimeofday(&tv1, &tz);
    count_distribution(arr,matrix,r,c);//Works like a charm
    //print(n,matrix);
    int val=cutoff(arr,p,r,c);
    //for(int i=0;i<=50;i++){
       // printf("%d:%d\n",i,arr[i]);
    //}
    //print(n,matrix);
    //printf("\n");
    //printf("%d\n",val); 
    threshold(r,c,matrix,bin_img,val); 
    //print(n,bin_img);
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("%4.2lf",elapsed);
    free(matrix);
    free(bin_img);
    

}