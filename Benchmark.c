#include <stdio.h>
#include <math.h>
#include "MatrixC.h"

int main()
{
    TYPE arr[] = {0.1, -0.2, 0.3, -0.4};
    Matrix *mat = create_from_array(arr, 2, 2);
    Matrix *cpy=NULL;
    Matrix *ref=NULL;
    copy_matrix(&cpy,mat);
    ref_matrix(&ref,mat);
    set_value(mat,2,2,2);
    printf("copy:\n");
    print_matrix(cpy,1);
    printf("refernce:\n");
    print_matrix(ref,1);
}