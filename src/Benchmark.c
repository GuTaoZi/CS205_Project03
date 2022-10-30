#include <stdio.h>
#include <math.h>
#include "MatrixC.h"

// Benchmark.c (main function)
int main()
{
    //被加数为空
    Matrix *A=NULL;
    Matrix *B=create_full(3,4,5);
    printf("A=0+B=\n");
    add_by(&A,B);
    print_matrix(A,0);
    B=NULL;
    subtract_by(&B,A);
    printf("B=0-A=\n");
    print_matrix(B,0);
}