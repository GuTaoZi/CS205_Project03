#include <stdio.h>
#include <math.h>
#include "MatrixC.h"

int main()
{
    Matrix *A=create_from_file("matfile",6,6);
    printf("A:\n");
    print_matrix(A,0);
    Matrix *T=transpose(A);
    printf("T:\n");
    print_matrix(T,0);
    printf("The rank of A is: %d\nThe rank of T is: %d\n",rank(A),rank(T));
}