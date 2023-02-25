#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include<string.h>

void generate(int n,int** arr){ 
    // memset(arr[0], 0, n * n * sizeof(int)); 
    srand(time(NULL));
    for(int i=0;i<n;i++)
    { 
        for(int j=0;j<n;j++)
        {
            arr[i][j]=rand() % 301;
        }
    }
} 

int check(int n,int** arr,int x){
    int c=0;
    for(int i=0;i<n;i++)
    {   
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]>x)
            {
                c=c+1;
            }
        } 
    } 

    return c;
}


void threshold(int p,int n,int** arr,int** img){
    int x=round((n*n)*(p/100));
    
    for(int i=0;i<n;i++)
    {   //int c=0;
        for(int j=0;j<n;j++)
        { 
            int c=check(n,arr,arr[i][j]);
             if(c<=x)
            {
                img[i][j]=1;
            } 
            else
            {
                img[i][j]=0;
            }
        } 
       
    }
}


void print(int n,int** arr){
   for(int i=0;i<n;i++)
    { 
        for(int j=0;j<n;j++)
        {
            printf("%d ",arr[i][j]);
        } 
        printf("\n");
    }
} 

int main(int argc,char* argv[]){
    // argv 1 is size of matrix and 2 is percentage of matrix
    int n=atoi(argv[1]);
    int p=atoi(argv[2]);  
    int **matrix;
    matrix = (int **)malloc(n * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < n; row++)
    {
        matrix[row] = (int *)malloc(n * sizeof(int));
    }  

    int **bin_img;
    bin_img = (int **)malloc(n * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < n; row++)
    {
        bin_img[row] = (int *)malloc(n * sizeof(int));
    } 

    generate(n,matrix);  
    print(n,matrix); 
    threshold(p,n,matrix,bin_img); 
    print(n,bin_img);


    
   
}