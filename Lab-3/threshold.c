#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h> 
#include<limits.h>
#include<string.h>

void generate(int r,int c,int **arr){ 
    srand(time(NULL));
    for(int i=0;i<r;i++)
    { 
        for(int j=0;j<c;j++)
        {
            arr[i][j]=rand() % 301;
        }
    }
} 

int check(int r, int c,int **arr,int x, int per) {
    int count=0;
    for(int i=0;i<r;i++)
    {   
        for(int j=0;j<c;j++)
        {
            if(arr[i][j]>x)
            {
                count=count+1;
                if(count>per)
                    return count;
            }
        } 
    } 
    return count;
}


void threshold(int p,int r, int c,int** arr,int** img){
    int prod = r*c*p;
    int x=prod/100;
    int k; 
    // int min=INT_MIN;
    
    for(int i=0;i<r;i++)
    {   int count=0;
        for(int j=0;j<c;j++)
        { 
            k = arr[i][j];
            // if(k>min){
            //     img[i][j]=0;
            //     min=k;
            //     continue;
            // }
            count=check(r, c, arr, k, x);
            printf("%d ",count);
             if(count<=x)
            {
                img[i][j]=1;
            } 
            else
            {
                img[i][j]=0;
            }
        } 
        printf("\n");
    }
}


void print(int r, int c,int **arr){
   for(int i=0;i<r;i++)
    { 
        for(int j=0;j<c;j++)
        {
            printf("%d ",arr[i][j]);
        } 
        printf("\n");
    }
} 

int main(int argc,char* argv[]){
    // argv 1 is size of matrix and 2 is percentage of matrix
    int r=5;
    int c=5;
    int p=10;
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

    generate(r,c,matrix);  
    print(r,c,matrix); 
    printf("-----------------------------------------");
    printf("\n");
    threshold(p,r,c,matrix,bin_img); 
    printf("-----------------------------------------");
    printf("\n");
    print(r,c,bin_img);
}