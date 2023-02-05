#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>

double **mult_Mat(int size);
double **create_Mat(int size);
void print_Mat(double **l, int size);
void input_Mat(double **A, int size);
double **multiply(double **matrix_A, double **matrix_B, int size);
double **OMM(double **A, int size);
void add_matrix(double **A, double **B, double **C, int split_index);


void add_matrix(double **matrix_A, double **matrix_B, double **matrix_C, int split_index) {
    for (int i = 0; i < split_index; i++) {
		for (int j = 0; j < split_index; j++) {
			matrix_C[i][j] = matrix_A[i][j] + matrix_B[i][j];
        }
    }
}


double **multiply(double **matrix_A, double **matrix_B, int size) {

    double **result_matrix;
    result_matrix = create_Mat(size);

    if(size == 1)
        result_matrix[0][0] = matrix_A[0][0] * matrix_A[0][0];

    else {
    int split_index = size / 2;

    double **result_matrix_00; double **result_matrix_01; double **result_matrix_10; double **result_matrix_11;

    result_matrix_00 = create_Mat(split_index);
    result_matrix_01 = create_Mat(split_index);
    result_matrix_10 = create_Mat(split_index);
    result_matrix_11 = create_Mat(split_index);

    double **a00; double **a01; double **a10; double **a11;

    a00 = create_Mat(split_index);
    a01 = create_Mat(split_index);
    a10 = create_Mat(split_index);
    a11 = create_Mat(split_index);

    for(int i = 0; i < split_index; i++) {
		for(int j = 0; j < split_index; j++) {
			a00[i][j] = matrix_A[i][j];
			a01[i][j] = matrix_A[i][j + split_index];
			a10[i][j] = matrix_A[split_index + i][j];
			a11[i][j] = matrix_A[i + split_index][j + split_index];
		}
    }
    
    add_matrix(multiply(a00, a00, split_index), multiply(a01, a10, split_index), result_matrix_00, split_index);
	add_matrix(multiply(a00, a01, split_index), multiply(a01, a11, split_index), result_matrix_01, split_index);
	add_matrix(multiply(a10, a00, split_index), multiply(a11, a10, split_index), result_matrix_10, split_index);
	add_matrix(multiply(a10, a01, split_index), multiply(a11, a11, split_index), result_matrix_11, split_index);

    for (int i = 0; i < split_index; i++) {
		for (int j = 0; j < split_index; j++) {
			result_matrix[i][j]	= result_matrix_00[i][j]; 
            result_matrix[i][j + split_index] = result_matrix_01[i][j];
			result_matrix[split_index + i][j] = result_matrix_10[i][j];
			result_matrix[i + split_index][j + split_index] = result_matrix_11[i][j];
		}
    }
    }
    return result_matrix;
}


double **OMM(double **A, int size) {
    double **matrix_k;
    matrix_k = create_Mat(size);

    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j ++) {  
            for (int k = 0; k < size; k++) {
                matrix_k[i][j] += A[i][k] * A[k][j];
            }
        }
    }
    return matrix_k;
}


double **create_Mat(int size) {
    double **Mat = (double **)calloc(sizeof(double *), size);

    for(int i=0; i<size; i++)
        Mat[i] = (double *)calloc(sizeof(double), size);

    return Mat;
}


void input_Mat(double **A, int size) {
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            A[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
}


double **mult_Mat(int size) {
    double **A; double **C; double **matrix_k;

    A = create_Mat(size);
    C = create_Mat(size);
    matrix_k = create_Mat(size);

    input_Mat(A, size);
    input_Mat(C, size);

    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j ++) {  
            for (int k = 0; k < size; k++) {
                matrix_k[i][j] += A[i][k] * C[k][j];
            }
        }
    }
    return matrix_k;
}


void print_Mat(double **l, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%f\t", l[i][j]); 
		}
        printf("\n");
	}
}



int main() {
    int size = 64;
    double **matrix_x;
    matrix_x = create_Mat(size);

    double **A;

    A = create_Mat(size);
    input_Mat(A, size);

    //matrix_x = mult_Mat(size);  This is OMM
    matrix_x = multiply(A, A, size);
    print_Mat(matrix_x, size);
}