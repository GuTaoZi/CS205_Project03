#include <stdio.h>
#include <math.h>
#include "MatrixC.h"

int main()
{
    int row = 7;
    int col = 7;
    float k[] = {7, 0, 0, 4, 4,
                 0, 4, 0, 0, 0,
                 0, 0, 0, 3, 3,
                 0, 4, 0, 4, 2,
                 0, 0, 4, 0, 1};
//    float ff[] = {1, 0};
//    Matrix *f = create_from_array(ff, 2, 1);
//    float tt[] = {1, 1, 1, 0};
//    Matrix *b = create_from_array(tt, 2, 2);
//    for (int i = 0; i <= 100; i++)
//    {
//        printf("%.0f\n", get_value(matrix_multiply(matrix_pow(b, i), f), 1, 1));
//    }
    Matrix *f = create_from_file("1.txt",4,3);
    print_matrix(f,2);
}