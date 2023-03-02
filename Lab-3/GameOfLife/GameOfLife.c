#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>

//for alive cells-:
//any cell with less than 2 live neigbors dies (underpopulation) 
//2-3 neigbors lives 
//more than 3 neigbors dies  

//foe dead cells-:
//with 3 neigbors cell becomes alive

//0 is dead 
//1 is alive

// void seed(int r,int c,int **arr)
// {
//     #pragma omp parallel for
//     for(int i=0;i<r;i++)
//     { 
//         for(int j=0;j<c;j++)
//         { 
//             arr[i][j] = rand()%2;
//         }
//     }

// } 

void update(int r,int col, int **arr,int **new)
{
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < col; j++)
        {   int c=0;
            //up and down 
            if(i>0)
            {
                 if(arr[i-1][j]==1)
                 {c=c+1;}
            }
           
           if(i<r-1)
           {
                if(arr[i+1][j]==1)
                {c=c+1;}
           }
    
            //left and right
            if(j>0)
            {
                if(arr[i][j-1]==1)
                {c=c+1;}
            } 

            if(j<col-1)
            {
                if(arr[i][j+1]==1)
                {c=c+1;} 
            }
            
            //left diagonal
            if(i>0 && j>0)
            {
                if(arr[i-1][j-1]==1)//left-top
                {c=c+1;}
            }

            if(i<r-1 && j<col-1)
            {
                if(arr[i+1][j+1]==1)//left-bottom
                {c=c+1;} 
            }

            //right diagonal
            if(i>0 && j<col-1)
            {
                if(arr[i-1][j+1]==1)//right-bottom
                {c=c+1;}
            }

            if(i<r-1 && j>0)
            {
                if(arr[i+1][j-1]==1)//right top
                {c=c+1;} 
            }
        
            //conditions for life-:

            //underpopulation
            if(c<2 && arr[i][j]==1)
            {new[i][j]=0;}

            //overpopulation
            if(c>3 && arr[i][j]==1)
            {new[i][j]=0;}

            //reproduction
            if(c==3 && arr[i][j]==0)
            {new[i][j]=1;}  

            //continous existance
            if((c==2 || c==3) && arr[i][j]==1)
            {new[i][j]=1;} 

            //else it dies
            if(c>4 && arr[i][j]==1)
            {new[i][j]=0;}

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

void copy_arr(int r,int c,int **arr1,int **arr2)
{
    #pragma omp parallel for
    for(int i=0;i<r;i++)
    { 
        for(int j=0;j<c;j++)
        {
            arr2[i][j]=arr1[i][j];
        }
    }

}

int main(int argc,char *argv[])
{
    int th = atoi(argv[2]); // number of threads 
    int r,c;
    int **board;
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: could not open input file\n");
        return 1;
    }
    fscanf(fp, "%d %d", &r, &c);
    board = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        board[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j++) {
            fscanf(fp, "%d", &board[i][j]);
        }
    }
    fclose(fp);

    int **dup;
    dup = (int **)malloc(r * sizeof(int *));
    // making it two dimensional
    for (int row = 0; row < r; row++)
    {
        dup[row] = (int *)malloc(c * sizeof(int));
    }  
     
   
    omp_set_num_threads(th);
    int gen = 10;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed; 
    double sum=0.0;
    gettimeofday(&tv1, &tz);
    copy_arr(r,c,board,dup);
    for(int i=0;i<gen;i++)
    {
        update(r,c,board,dup);
        printf("\n");
        printf("----------\n");
        print_array(r,c,dup);
        copy_arr(r,c,board,dup);
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("%4.2lf",elapsed);
}