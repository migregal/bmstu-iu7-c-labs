#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>

typedef struct matrix_t
{
    int *data;
    size_t rows, cols;
} matrix_t;

int create_matrix(matrix_t *matrix, size_t rows, size_t cols);

void delete_matrix(matrix_t *matrix);

int read_matrix(matrix_t *matrix, char *filename);

int process_matrix(matrix_t *matrix);

int print_matrix(matrix_t *matrix, char *filename);

#endif
