#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "MatrixC.h"

//Functions For Creating Matrices
inline Matrix *create_empty(size_t row, size_t col)
{
    if (row * col == 0)
    {
        print_error("Illegal matrix size", "Row and Col should be positive integers.");
        return NULL;
    }
    else if (row * col > MATRIX_MAX_CAPACITY)
    {
        print_error("Illegal matrix size", "The maximum size of matrix is row*col=1e8.");
        return NULL;
    }
    Matrix *new = malloc(sizeof(Matrix));
    new->row = row;
    new->col = col;
    new->data = malloc(sizeof(TYPE) * row * col);
    return new;
}

Matrix *create_full(size_t row, size_t col, TYPE value)
{
    Matrix *new = create_empty(row, col);
    if (new == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < row * col; i++)
    {
        new->data[i] = value;
    }
    return new;
}

Matrix *create_from_array(TYPE *src, size_t row, size_t col)
{
    Matrix *new = create_empty(row, col);
    if (new == NULL)
    {
        return NULL;
    }
    if (src == NULL)
    {
        print_error("NULL pointer exception", "The source array is null, creating process interrupted.");
    }
    for (size_t i = 0; i < row * col; i++)
    {
        new->data[i] = src[i];
    }
    return new;
}

Matrix *create_from_string(char *src, size_t row, size_t col)
{
    Matrix *new = create_empty(row, col);
    size_t cur_row = 1;
    size_t cur_col = 0;
    size_t cnt = 0;
    for (size_t i = 0; i < strlen(src); i++)
    {
        if (src[i] == ';')
        {
            cur_row++;
            if (cur_col != col)
            {
                print_error("Illegal matrix shape",
                            "The number of col mismatch the given col, matrix creation process interrupted.");
                delete_matrix(&new);
                return NULL;
            }
            cur_col = 0;
        }
        else if (src[i] == '+' || src[i] == '-' || isdigit(src[i]))
        {
            size_t len = 0;
            while (i + len < strlen(src) &&
                   (src[i + len] == '+' || src[i + len] == '-' || src[i + len] == '.' || isdigit(src[i + len])))
            {
                len++;
            }
            if (regex(src + i, len))
            {
                cur_col++;
                if (cur_col > col)
                {
                    print_error("Illegal matrix shape",
                                "The number of col mismatch the given col, matrix creation process interrupted.");
                    delete_matrix(&new);
                    return NULL;
                }
                new->data[cnt++] = to_float(src + i, len);
                i += len - 1;
            }
            else
            {
                print_error("Illegal format shape",
                            "The format of input matrix is illegal, matrix creation process interrupted.");
                delete_matrix(&new);
                return NULL;
            }
        }
        else if (src[i] != ' ' && src[i] != ',')
        {
            print_error("Illegal format shape",
                        "The format of input matrix is illegal, matrix creation process interrupted.");
            delete_matrix(&new);
            return NULL;
        }
    }
    if (cur_row != row)
    {
        print_error("Illegal matrix shape",
                    "The number of row mismatch the given row, matrix creation process interrupted.");
        delete_matrix(&new);
        return NULL;
    }
    return new;
}

Matrix *create_from_file(char *f_path, size_t row, size_t col)
{
    FILE *file = fopen(f_path, "r");
    if (file == NULL)
    {
        print_error("NULL pointer exception", "Source file not found, matrix creation process interrupted.");
        return NULL;
    }
    size_t str_len = 0;
    while (!feof(file))
    {
        char o = fgetc(file);
        str_len++;
    }
    fclose(file);
    file = fopen(f_path, "r");
    char *str = malloc(str_len * sizeof(char));
    str_len = 0;
    char last = ' ';
    while (!feof(file))
    {
        char o = fgetc(file);
        if (o == '\n')
        {
            if (last == ';')
            {
                o = ' ';
            }
            else
            {
                o = ';';
            }
        }
        if (o < 0)
        {
            break;
        }
        last = o;
        str[str_len++] = o;
    }
    while (str[str_len - 1] == ' ' || str[str_len - 1] == ';')
    {
        str_len--;
    }
    str[str_len] = '\0';
    return create_from_string(str, row, col);
}

Matrix *create_copy(Matrix *src)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception", "The source matrix is null, copy process interrupted.");
        return NULL;
    }
    Matrix *new = create_from_array(src->data, src->row, src->col);
    return new;
}

Matrix *sub_matrix(Matrix *src, size_t row_begin, size_t col_begin, size_t row_end, size_t col_end)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception", "The source matrix is null, copy process interrupted.");
        return NULL;
    }
    if (row_begin * col_begin == 0)
    {
        print_error("Illegal row/col index", "The starting index of row and col should be positive.");
        return NULL;
    }
    if (row_end > src->row)
    {
        print_error("Illegal row index", "The ending index of row exceeds the max row index of source matrix.");
        return NULL;
    }
    if (col_end > src->col)
    {
        print_error("Illegal col index", "The ending index of col exceeds the max col index of source matrix.");
        return NULL;
    }
    Matrix *new = create_empty(row_end - row_begin + 1, col_end - col_begin + 1);
    if (new == NULL)
    {
        return NULL;
    }
    for (size_t i = row_begin, siz = 0; i <= row_end; i++)
    {
        for (size_t j = col_begin; j <= col_end; j++)
        {
            new->data[siz++] = src->data[(i - 1) * src->col + j - 1];
        }
    }
    return new;
}

Matrix *create_identity(size_t order)
{
    Matrix *new = create_full(order, order, 0);
    if (new == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < order; i++)
    {
        new->data[i * order + i] = 1.0f;
    }
    return new;
}

Matrix *create_diagonal(TYPE *src, size_t order)
{
    Matrix *new = create_full(order, order, 0);
    if (new == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < order; i++)
    {
        new->data[i * order + i] = src[i];
    }
}

Matrix *create_random(size_t row, size_t col)
{
    srand(time(0));
    Matrix *new = create_empty(row, col);
    if (new == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < size_of(new); i++)
    {
        new->data[i] = 1.0f * rand() / 0x7fff;
    }
    return new;
}

//Functions For Matrix Operations
bool delete_matrix(Matrix **pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception",
                    "The address of the pointer to the matrix is null, delete process interrupted.");
        return false;
    }
    if ((*pmat) == NULL)
    {
        print_error("NULL pointer exception", "The pointer to the matrix is null, delete process interrupted.");
        return false;
    }
    free((*pmat)->data);
    free(*pmat);
    *pmat = NULL;
    return true;
}

bool reshape_matrix(Matrix *src, size_t row, size_t col)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to the source matrix is null, reshaping process interrupted.");
        return false;
    }
    Matrix *new = create_full(row, col, 0);
    if (new == NULL)
    {
        return false;
    }
    if (size_of(src) != row * col)
    {
        print_error("Illegal matrix size",
                    "The size of source matrix is not corresponding to the given row and col, reshaping process interrupted.");
        delete_matrix(&new);
        return false;
    }
    src->row = row;
    src->col = col;
    return true;
}

bool copy_matrix(Matrix **dest, Matrix *src)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, copy process interrupted.");
        return false;
    }
    if (*dest == NULL)
    {
        *dest = create_copy(src);
        if (*dest == NULL)
        {
            return false;
        }
        print_warning("Copy into null matrix",
                      "The pointer to destination matrix is null, the pointer will point to a copy matrix of source matrix.");
    }
    else
    {
        if (((*dest)->row != src->row) || ((*dest)->col != src->col))
        {
            print_warning("Copy into matrix of different sizes",
                          "The sizes of two matrices are different, the data of destination matrix will be covered by source matrix.");
        }
        delete_matrix(dest);
        *dest = create_copy(src);
        if (*dest == NULL)
        {
            return false;
        }
    }
    return true;
}

bool ref_matrix(Matrix **dest, Matrix *src)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, copy process interrupted.");
        return false;
    }
    if(*dest!=NULL)
    {
        delete_matrix(dest);
    }
    *dest = src;
    return true;
}

bool swap_matrix(Matrix *first, Matrix *second)
{
    if (first == NULL || second == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer of given matrix is null, swapping process interrupted.");
        return false;
    }
    TYPE *tmp = first->data;
    first->data = second->data;
    second->data = tmp;
    tmp = NULL;
    first->row ^= second->row;
    second->row ^= first->row;
    first->row ^= second->row;
    first->col ^= second->col;
    second->col ^= first->col;
    first->col ^= second->col;
    return true;
}

Matrix *col_concat(Matrix *first, Matrix *second)
{
    if (first == NULL || second == NULL)
    {
        print_error("NULL pointer exception", "The pointer to source matrix is null, concat process interrupted.");
        return NULL;
    }
    if (first->col != second->col)
    {
        print_error("Illegal matrix shape",
                    "The number of col of source matrices should be the same, concat process interrupted.");
        return NULL;
    }
    Matrix *new = create_empty(first->row + second->row, first->col);
    if (new == NULL)
    {
        return NULL;
    }
    size_t t = size_of(first);
    for (size_t i = 0; i < t; i++)
    {
        new->data[i] = first->data[i];
    }
    for (size_t i = t; i < size_of(new); i++)
    {
        new->data[i] = second->data[i - t];
    }
    return new;
}

Matrix *row_concat(Matrix *first, Matrix *second)
{
    if (first == NULL || second == NULL)
    {
        print_error("NULL pointer exception", "The pointer to source matrix is null, concat process interrupted.");
        return NULL;
    }
    if (first->row != second->row)
    {
        print_error("Illegal matrix shape",
                    "The number of row of source matrices should be the same, concat process interrupted.");
        return NULL;
    }
    Matrix *new = create_empty(first->row, first->col + second->col);
    if (new == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < first->row; i++)
    {
        for (size_t j = 0; j < first->col; j++)
        {
            new->data[i * new->col + j] = first->data[i * first->col + j];
        }
        for (size_t j = 0; j < second->col; j++)
        {
            new->data[i * new->col + j + first->col] = second->data[i * second->col + j];
        }
    }
    return new;
}

//Functions For Modifying Matrices
bool set_value(Matrix *pmat, size_t row, size_t col, TYPE value)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to matrix is null, value setting process interrupted.");
        return false;
    }
    if (row > pmat->row)
    {
        print_error("Illegal row index", "The index of row exceeds the max row index of matrix.");
        return false;
    }
    if (col > pmat->col)
    {
        print_error("Illegal col index", "The index of col exceeds the max col index of matrix.");
        return false;
    }
    pmat->data[(row - 1) * pmat->col + col - 1] = value;
    return true;
}

//Functions For Querying In Matrices
size_t size_of(Matrix *pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception", "Failed to get size of null matrix.");
        return -1;
    }
    return (pmat->row * pmat->col);
}

size_t rank(Matrix *pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, rank calculation interrupted.");
        return nan("");
    }
    Matrix *new = create_copy(pmat);
    if (new == NULL)
    {
        return nan("");
    }
    size_t lim = new->row < new->col ? new->row : new->col;
    size_t rk = lim;
    for (size_t i = 0; i < lim; i++)
    {
        if (float_equal(new->data[i * new->col + i], 0.0f))
        {
            for (size_t j = i + 1; j < new->row; j++)
            {
                if (!float_equal(new->data[j * new->col + i], 0.0f))
                {
                    for (size_t k = 0; k < new->col; k++)
                    {
                        TYPE t = new->data[i * new->col + k];
                        new->data[i * new->col + k] = new->data[j * new->col + k];
                        new->data[j * new->col + k] = t;
                    }
                    break;
                }
            }
        }
        if (float_equal(new->data[i * new->col + i], 0.0f))
        {
            rk--;
            continue;
        }
        for (size_t j = i + 1; j < new->row; j++)
        {
            TYPE t = new->data[j * new->col + i] / new->data[i * new->col + i];
            for (size_t k = 0; k < new->col; k++)
            {
                new->data[j * new->col + k] -= new->data[i * new->col + k] * t;
            }
        }
    }
    return rk;
}

TYPE get_value(Matrix *src, size_t row, size_t col)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, return NaN.");
        return nanf("");
    }
    if (row > src->row)
    {
        print_error("Illegal row index", "The index of row exceeds the max row index of source matrix.");
        return false;
    }
    if (col > src->col)
    {
        print_error("Illegal col index", "The index of col exceeds the max col index of source matrix.");
        return false;
    }
    return src->data[(row - 1) * src->col + col - 1];
}

TYPE max(Matrix *src)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, return NaN.");
        return nanf("");
    }
    TYPE ans = src->data[0];
    for (size_t i = 1; i < size_of(src); i++)
    {
        if (ans < src->data[i])
        {
            ans = src->data[i];
        }
    }
    return ans;
}

TYPE min(Matrix *src)
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, return NaN.");
        return nanf("");
    }
    TYPE ans = src->data[0];
    for (size_t i = 1; i < size_of(src); i++)
    {
        if (ans > src->data[i])
        {
            ans = src->data[i];
        }
    }
    return ans;
}

TYPE extreme_value(Matrix *src, bool (*cmp)(TYPE, TYPE))
{
    if (src == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, return NaN.");
        return nanf("");
    }
    TYPE ans = src->data[0];
    for (size_t i = 1; i < size_of(src); i++)
    {
        if (cmp(src->data[i], ans))
        {
            ans = src->data[i];
        }
    }
    return ans;
}

bool equal(Matrix *first, Matrix *second)
{
    if (first == NULL || second == NULL)
    {
        print_error("NULL pointer exception", "Trying to compare two null matrices, return false.");
        return false;
    }
    if (first->row != second->row || first->col != second->col)
    {
        return false;
    }
    for (size_t i = 0; i < size_of(first); i++)
    {
        if (!float_equal(first->data[i], second->data[i]))
        {
            return false;
        }
    }
    return true;
}

//Functions For Customized Calculation

TYPE plus(TYPE first, TYPE second)
{
    return (first + second);
}

TYPE minus(TYPE first, TYPE second)
{
    return (first - second);
}

TYPE mul(TYPE first, TYPE second)
{
    return (first * second);
}

TYPE divide(TYPE first, TYPE second)
{
    return (first / second);
}

//Functions For Matrix Calculation

Matrix *unary_calc(Matrix *pmat, TYPE(*fun)(TYPE))
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception", "The pointer to the source matrix is null, calculation interrupted.");
        return NULL;
    }
    Matrix *new = create_copy(pmat);
    for (size_t i = 0; i < size_of(new); i++)
    {
        new->data[i] = fun(new->data[i]);
    }
    return new;
}

Matrix *binary_calc(Matrix *first, Matrix *second, TYPE (*fun)(TYPE, TYPE))
{
    if (first == NULL)
    {
        print_error("NULL pointer exception", "The pointer to the first matrix is null, calculation interrupted.");
        return NULL;
    }
    if (second == NULL)
    {
        print_error("NULL pointer exception", "The pointer to the second matrix is null, calculation interrupted.");
        return NULL;
    }
    if (first->row != second->row || first->col != second->col)
    {
        print_error("Illegal matrix shape",
                    "The shape of two matrices are different, calculation process interrupted.");
        return NULL;
    }
    Matrix *new = create_copy(first);

    for (size_t i = 0; i < size_of(new); i++)
    {
        new->data[i] = fun(new->data[i], second->data[i]);
    }
    return new;
}

Matrix *scalar_calc(Matrix *pmat, TYPE scalar, TYPE (*fun)(TYPE, TYPE))
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception", "The pointer to the source matrix is null, calculation interrupted.");
        return NULL;
    }
    Matrix *new = create_copy(pmat);
    for (size_t i = 0; i < size_of(new); i++)
    {
        new->data[i] = fun(new->data[i], scalar);
    }
    return new;
}

bool add_by(Matrix *augend, Matrix *addend)
{
    if (addend == NULL)
    {
        print_error("NULL pointer exception", "The pointer to addend matrix is null, add process interrupted.");
        return false;
    }
    if (augend == NULL)
    {
        print_warning("NULL pointer warning",
                      "The pointer to augend matrix is null, a copy of addend matrix will be assigned to augend matrix instead.");
        augend = create_copy(addend);
        return true;
    }
    if (augend->row != addend->row || augend->col != addend->col)
    {
        print_error("Illegal matrix shape",
                    "The shape of augend and addend matrices are different, add process interrupted.");
        return false;
    }
    for (size_t i = 0; i < size_of(augend); i++)
    {
        augend->data[i] += addend->data[i];
    }
    return true;
}

Matrix *matrix_add(Matrix *augend, Matrix *addend)
{
    if (addend == NULL)
    {
        print_error("NULL pointer exception", "The pointer to addend matrix is null, add process interrupted.");
        return NULL;
    }
    if (augend == NULL)
    {
        print_warning("NULL pointer warning",
                      "The pointer to augend matrix is null, a copy of addend matrix will be returned instead.");
        return create_copy(addend);
    }
    if (augend->row != addend->row || augend->col != addend->col)
    {
        print_error("Illegal matrix shape",
                    "The shape of augend and addend matrices are different, add process interrupted.");
        return NULL;
    }
    Matrix *new = create_copy(augend);
    for (size_t i = 0; i < size_of(new); i++)
    {
        new->data[i] += addend->data[i];
    }
    return new;
}

bool subtract_by(Matrix *minuend, Matrix *subtrahend)
{
    if (subtrahend == NULL)
    {
        print_error("NULL pointer warning", "The pointer to subtrahend matrix is null, subtract process interrupted.");
        return false;
    }
    if (minuend == NULL)
    {
        print_warning("NULL pointer warning",
                      "The pointer to minuend matrix is null, a negative copy of subtrahend matrix will be assigned to minuend matrix instead.");
        minuend = create_copy(subtrahend);
        for (size_t i = 0; i < size_of(minuend); i++)
        {
            minuend->data[i] = -minuend->data[i];
        }
        return true;
    }
    if (minuend->row != subtrahend->row || minuend->col != subtrahend->col)
    {
        print_error("Illegal matrix shape",
                    "The shape of minuend and subtrahend matrices are different, add process interrupted.");
        return false;
    }
    for (size_t i = 0; i < size_of(minuend); i++)
    {
        minuend->data[i] -= subtrahend->data[i];
    }
    return true;
}

Matrix *matrix_subtract(Matrix *minuend, Matrix *subtrahend)
{
    if (subtrahend == NULL)
    {
        print_error("NULL pointer warning", "The pointer to subtrahend matrix is null, subtract process interrupted.");
        return NULL;
    }
    if (minuend == NULL)
    {
        print_warning("NULL pointer warning",
                      "The pointer to minuend matrix is null, a negative copy of subtrahend matrix will be returned instead.");
        Matrix *new = create_copy(subtrahend);
        for (size_t i = 0; i < size_of(new); i++)
        {
            new->data[i] = -new->data[i];
        }
        return new;
    }
    if (minuend->row != subtrahend->row || minuend->col != subtrahend->col)
    {
        print_error("Illegal matrix shape",
                    "The shape of minuend and subtrahend matrices are different, add process interrupted.");
        return NULL;
    }
    Matrix *new = create_copy(minuend);
    for (size_t i = 0; i < size_of(new); i++)
    {
        new->data[i] -= subtrahend->data[i];
    }
    return new;
}

bool multiply_by(Matrix **multiplicand, Matrix *multiplier)
{
    if (multiplicand == NULL)
    {
        print_error("NULL pointer exception",
                    "The address of pointer to multiplicand matrix is null, multiplication process interrupted.");
        return false;
    }
    if ((*multiplicand) == NULL || multiplier == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointers to multiplicand and multiplier matrix are null, multiplication process interrupted.");
        return false;
    }
    if ((*multiplicand)->col != multiplier->row)
    {
        print_error("Illegal matrix shape",
                    "The col number of multiplicand matrix should equal to row number of multiplier matrix.");
        return false;
    }
    Matrix *new = matrix_multiply(*multiplicand, multiplier);
    if (new == NULL)
    {
        return false;
    }
    free((*multiplicand)->data);
    free(*multiplicand);
    *multiplicand = new;
    new = NULL;
    return true;
}

bool multiply_to(Matrix *multiplicand, Matrix **multiplier)
{
    if (multiplier == NULL)
    {
        print_error("NULL pointer exception",
                    "The address of pointer to multiplier matrix is null, multiplication process interrupted.");
        return false;
    }
    if ((*multiplier) == NULL || multiplicand == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointers to multiplier and multiplicand matrix are null, multiplication process interrupted.");
        return false;
    }
    if ((*multiplier)->col != multiplicand->row)
    {
        print_error("Illegal matrix shape",
                    "The col number of multiplier matrix should equal to row number of multiplicand matrix.");
        return false;
    }
    Matrix *new = matrix_multiply(multiplicand, *multiplier);
    if (new == NULL)
    {
        return false;
    }
    free((*multiplier)->data);
    free(*multiplier);
    *multiplier = new;
    new = NULL;
    return true;
}

Matrix *matrix_multiply(Matrix *multiplicand, Matrix *multiplier)
{
    if (multiplicand == NULL || multiplier == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointers to multiplicand and multiplier matrix are null, multiplication process interrupted.");
        return NULL;
    }
    if (multiplicand->col != multiplier->row)
    {
        print_error("Illegal matrix shape",
                    "The col number of multiplicand matrix should equal to row number of multiplier matrix.");
        return NULL;
    }
    Matrix *new = create_full(multiplicand->row, multiplier->col, 0);
    for (size_t i = 1; i <= multiplicand->row; i++)
    {
        for (size_t k = 1; k <= multiplicand->col; k++)
        {
            TYPE t = multiplicand->data[(i - 1) * multiplicand->col + k - 1];
            for (size_t j = 1; j <= multiplier->col; j++)
            {
                new->data[(i - 1) * new->col + j - 1] += t * multiplier->data[(k - 1) * multiplier->col + j - 1];
            }
        }
    }
    return new;
}

Matrix *matrix_pow(Matrix *base, size_t power)
{
    if (base == NULL)
    {
        print_error("NULL pointer exception", "The pointer to base matrix is null, power process interrupted.");
        return NULL;
    }
    if (power == 1)
    {
        return create_copy(base);
    }
    if (base->row != base->col)
    {
        print_error("Illegal matrix shape", "The base matrix should be square matrix.");
        return NULL;
    }
    if (power == 0)
    {
        return create_identity(base->row);
    }
    Matrix *new;
    if (power < 0)
    {
        new = create_copy(inverse(base));
        if (new == NULL)
        {
            print_error("NULL pointer exception",
                        "The source matrix has no inverse, negative power calculation interrupted.");
            return NULL;
        }
        power = -power;
    }
    else
    {
        new = create_copy(base);
    }
    Matrix *Base = create_copy(base);
    power--;
    while (power)
    {
        if (power & 1)
        {
            multiply_by(&new, Base);
        }
        multiply_by(&Base, Base);
        power >>= 1;
    }
    return new;
}

bool add_scalar(Matrix *pmat, TYPE scalar)
{
    Matrix *new = scalar_calc(pmat, scalar, plus);
    if (new == NULL)
    {
        return false;
    }
    delete_matrix(&pmat);
    pmat = new;
    return true;
}

bool subtract_scalar(Matrix *pmat, TYPE scalar)
{
    Matrix *new = scalar_calc(pmat, scalar, minus);
    if (new == NULL)
    {
        return false;
    }
    delete_matrix(&pmat);
    pmat = new;
    return true;
}

bool multiply_scalar(Matrix *pmat, TYPE scalar)
{
    Matrix *new = scalar_calc(pmat, scalar, mul);
    if (new == NULL)
    {
        return false;
    }
    delete_matrix(&pmat);
    pmat = new;
    return true;
}

bool divide_scalar(Matrix *pmat, TYPE scalar)
{
    Matrix *new = scalar_calc(pmat, scalar, divide);
    if (new == NULL)
    {
        return false;
    }
    delete_matrix(&pmat);
    pmat = new;
    return true;
}

//Functions For Matrix Transformations

TYPE determinant(Matrix *pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, determinant calculation interrupted.");
        return nanf("");
    }
    if (pmat->col != pmat->row)
    {
        print_error("Illegal matrix shape",
                    "Determinant exists only when the matrix is square, determinant calculation interrupted.");
        return nanf("");
    }
    TYPE result = 1.0f;
    Matrix *new = create_copy(pmat);
    if (new == NULL)
    {
        return nanf("");
    }
    size_t lim = new->row < new->col ? new->row : new->col;
    for (size_t i = 0; i < lim; i++)
    {
        if (float_equal(new->data[i * new->col + i], 0.0f))
        {
            for (size_t j = i + 1; j < new->row; j++)
            {
                if (!float_equal(new->data[j * new->col + i], 0.0f))
                {
                    for (size_t k = 0; k < new->col; k++)
                    {
                        result = -result;
                        TYPE t = new->data[i * new->col + k];
                        new->data[i * new->col + k] = new->data[j * new->col + k];
                        new->data[j * new->col + k] = t;
                    }
                    break;
                }
            }
        }
        if (float_equal(new->data[i * new->col + i], 0.0f))
        {
            return 0.0f;
        }
        for (size_t j = i + 1; j < new->row; j++)
        {
            TYPE t = new->data[j * new->col + i] / new->data[i * new->col + i];
            for (size_t k = 0; k < new->col; k++)
            {
                new->data[j * new->col + k] -= new->data[i * new->col + k] * t;
            }
        }
    }
    for (size_t i = 0; i < new->row; i++)
    {
        result *= new->data[i * new->col + i];
    }
    return result;
}

Matrix *inverse(Matrix *pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, inverse calculation interrupted.");
        return NULL;
    }
    if (pmat->row != pmat->col)
    {
        print_error("Illegal matrix shape",
                    "The matrix should be square to have inverse, inverse calculation interrupted.");
    }
    Matrix *new = row_concat(pmat, create_identity(pmat->row));
    size_t row = pmat->row;
    size_t col = row * 2;
    for (size_t i = 0; i < row; i++)
    {
        if (float_equal(new->data[i * col + i], 0.0f))
        {
            for (size_t j = i + 1; j < row; j++)
            {
                if (!float_equal(new->data[j * col + i], 0.0f))
                {
                    for (size_t k = 0; k < col; k++)
                    {
                        TYPE t = new->data[i * col + k];
                        new->data[i * col + k] = new->data[j * col + k];
                        new->data[j * col + k] = t;
                    }
                    break;
                }
            }
        }
        if (float_equal(new->data[i * col + i], 0.0f))
        {
            print_error("Inverse doesn't exist",
                        "The rank of source matrix is not full, inverse calculation interrupted.");
            return NULL;
        }
        for (size_t j = i + 1; j < row; j++)
        {
            TYPE t = new->data[j * col + i] / new->data[i * col + i];
            for (size_t k = 0; k < col; k++)
            {
                new->data[j * col + k] -= new->data[i * col + k] * t;
            }
        }
    }
    for (size_t i = 0; i < row; i++)
    {
        TYPE u = new->data[i * col + i];
        for (size_t j = 0; j < i; j++)
        {
            TYPE v = new->data[j * col + i] / u;
            for (size_t k = i; k < col; k++)
            {
                new->data[j * col + k] -= new->data[i * col + k] * v;
            }
        }
    }
    for (size_t i = 0; i < row; i++)
    {
        TYPE t = new->data[i * col + i];
        for (size_t j = row; j < col; j++)
        {
            new->data[i * new->col + j] /= t;
        }
    }
    return sub_matrix(new, 1, pmat->col + 1, new->row, new->col);
}

Matrix *transpose(Matrix *pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception", "The pointer to source matrix is null, transpose process interrupted.");
        return NULL;
    }
    Matrix *new = create_empty(pmat->col, pmat->row);
    for (size_t i = 0; i < pmat->row; i++)
    {
        for (size_t j = 0; j < pmat->col; j++)
        {
            *(new->data + j * new->col + i) = *(pmat->data + i * pmat->col + j);
        }
    }
    return new;
}

Matrix *Uptriangular(Matrix *pmat)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception",
                    "The pointer to source matrix is null, uptriangular process interrupted.");
        return NULL;
    }
    Matrix *new = create_copy(pmat);
    size_t lim = new->row < new->col ? new->row : new->col;
    for (size_t i = 0; i < lim; i++)
    {
        if (float_equal(new->data[i * new->col + i], 0.0f))
        {
            for (size_t j = i + 1; j < new->row; j++)
            {
                if (!float_equal(new->data[j * new->col + i], 0.0f))
                {
                    for (size_t k = 0; k < new->col; k++)
                    {
                        TYPE t = new->data[i * new->col + k];
                        new->data[i * new->col + k] = new->data[j * new->col + k];
                        new->data[j * new->col + k] = t;
                    }
                    break;
                }
            }
        }
        if (float_equal(new->data[i * new->col + i], 0.0f))
        {
            continue;
        }
        for (size_t j = i + 1; j < new->row; j++)
        {
            TYPE t = new->data[j * new->col + i] / new->data[i * new->col + i];
            for (size_t k = 0; k < new->col; k++)
            {
                new->data[j * new->col + k] -= new->data[i * new->col + k] * t;
            }
        }
    }
    Matrix *res = create_full(new->row, new->col, 0.0f);
    for (size_t i = 0, it = 0; i < new->row; i++)
    {
        bool emp = true;
        for (size_t j = 0; j < new->col; j++)
        {
            if (!(float_equal(new->data[i * new->col + j], 0.0f)))
            {
                res->data[it * res->col + j] = new->data[i * new->col + j];
                emp = false;
            }
        }
        it += emp ? 0 : 1;
    }
    delete_matrix(&new);
    return res;
}

//Functions For Debugging
void print_matrix(Matrix *pmat, int precision)
{
    if (pmat == NULL)
    {
        print_error("NULL pointer exception", "The pointer to source matrix is null, print process interrupted.");
        return;
    }
    if (precision < 0)
    {
        print_error("Illegal precision", "Precision should be non-negative, print process interrupted.");
        return;
    }
    if (precision > 6)
    {
        print_warning("Precision too large", "Float numbers are accurate to at most the 6th decimal place.");
        precision = 6;
    }
    for (size_t i = 0; i < pmat->row; i++)
    {
        for (size_t j = 0; j < pmat->col; j++)
        {
            if (float_equal(pmat->data[i * pmat->col + j], 0.0f))
            {
                pmat->data[i * pmat->col + j] = 0.0f;
            }
            printf("%.*f\t", precision, pmat->data[i * pmat->col + j]);
        }
        printf("\n");
    }
}

void print_error(char *err_type, char *err_info)
{
    printf("Error: %s\n", err_type);
    printf("Error log: %s\n", err_info);
    printf("Current operation interrupted, please check and try again.\n\n");
}

void print_warning(char *w_type, char *w_info)
{
    printf("Warning: %s\n", w_type);
    printf("Details: %s\n", w_info);
}

//File & String Operation

bool regex(char *str, size_t len)
{
    size_t it = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        it++;
    }
    else if (!isdigit(str[0]))
    {
        return false;
    }
    bool dot = false;
    while (it < len)
    {
        if (str[it] == '.')
        {
            if (dot)
            {
                return false;
            }
            dot = true;
        }
        else if (!isdigit(str[it]))
        {
            return false;
        }
        it++;
    }
    return true;
}

TYPE to_float(char *str, size_t len)
{
    float base = 1.0f;
    float f = 0.0f;
    size_t it = 0;
    if (str[0] == '-')
    {
        it++;
        base = -1.0f;
    }
    else if (str[0] == '+')
    {
        it++;
    }
    else if (!isdigit(str[0]))
    {
        return nanf("");
    }
    while (it < len && str[it] != '.')
    {

        f = f * 10.0f + (str[it] - '0');
        it++;
    }
    while (it < len - 1)
    {
        it++;
        if (!isdigit(str[it]))
        {
            return nanf("");
        }
        f = f * 10.0f + (str[it] - '0');
        base *= 10;
    }
    return f / base;
}