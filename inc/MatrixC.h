#ifndef PROJECT03_MATRIXC_H
#define PROJECT03_MATRIXC_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define TYPE float
#define float_equal(x, y) ((x-y)<1e-5&&(y-x)<1e-5)
#define MATRIX_MAX_CAPACITY 100000000

typedef struct MatrixC
{
    size_t row;
    size_t col;
    TYPE *data;
} Matrix;

//Functions For Creating Matrices
Matrix *create_empty(size_t row, size_t col);

Matrix *create_full(size_t row, size_t col, TYPE value);

Matrix *create_from_array(TYPE *src, size_t row, size_t col);

Matrix *create_from_string(char *src, size_t row, size_t col);

Matrix *create_from_file(char *f_path, size_t row, size_t col);

Matrix *create_copy(Matrix *src);

Matrix *create_identity(size_t order);

Matrix *create_diagonal(TYPE *src, size_t order);

Matrix *create_random(size_t row, size_t col);

Matrix *sub_matrix(Matrix *src, size_t row_begin, size_t col_begin, size_t row_end, size_t col_end);

//Functions For Matrix Operations
bool delete_matrix(Matrix **pmat);

bool reshape_matrix(Matrix *src, size_t row, size_t col);

bool copy_matrix(Matrix **dest, Matrix *src);

bool ref_matrix(Matrix **dest, Matrix *src);

bool swap_matrix(Matrix *first, Matrix *second);

Matrix *col_concat(Matrix *first, Matrix *second);

Matrix *row_concat(Matrix *first, Matrix *second);

bool set_value(Matrix *pmat, size_t row, size_t col, TYPE value);


//Functions For Querying In Matrices
size_t size_of(Matrix *pmat);

size_t rank(Matrix *pmat);

TYPE get_value(Matrix *src, size_t row, size_t col);

TYPE max(Matrix *src);

TYPE min(Matrix *src);

TYPE extreme_value(Matrix *src, bool (*cmp)(TYPE, TYPE));

bool equal(Matrix *first, Matrix *second);

//Functions For Customized Calculation

TYPE plus(TYPE first, TYPE second);

TYPE minus(TYPE first, TYPE second);

TYPE mul(TYPE first, TYPE second);

TYPE divide(TYPE first, TYPE second);

//Functions For Matrix Calculation

Matrix *unary_calc(Matrix *pmat, TYPE(*fun)(TYPE));

Matrix *binary_calc(Matrix *first, Matrix *second, TYPE (*fun)(TYPE, TYPE));

Matrix *scalar_calc(Matrix *pmat, TYPE scalar, TYPE(*fun)(TYPE, TYPE));

bool add_by(Matrix **augend, Matrix *addend);

Matrix *matrix_add(Matrix *augend, Matrix *addend);

bool subtract_by(Matrix **minuend, Matrix *subtrahend);

Matrix *matrix_subtract(Matrix *minuend, Matrix *subtrahend);

bool multiply_by(Matrix **multiplicand, Matrix *multiplier);

bool multiply_to(Matrix *multiplicand, Matrix **multiplier);

Matrix *matrix_multiply(Matrix *multiplicand, Matrix *multiplier);

Matrix *matrix_pow(Matrix *base, int power);

bool add_scalar(Matrix *pmat, TYPE scalar);

bool subtract_scalar(Matrix *pmat, TYPE scalar);

bool multiply_scalar(Matrix *pmat, TYPE scalar);

bool divide_scalar(Matrix *pmat, TYPE scalar);

//Functions For Matrix Transformations

TYPE determinant(Matrix *pmat);

Matrix *inverse(Matrix *pmat);

Matrix *transpose(Matrix *pmat);

Matrix *Uptriangular(Matrix *pmat);

//Functions For Debugging, Error & Warning
void print_matrix(Matrix *pmat, int precision);

void print_error(char *err_type, char *err_info);

void print_warning(char *w_type, char *w_info);

//File & String Operation

bool regex(char *str, size_t len);

TYPE to_float(char *str, size_t len);


#endif
