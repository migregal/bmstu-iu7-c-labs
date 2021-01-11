#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <inttypes.h>

#define ELEM_FORMAT             "%lf"
#define SIZE_TYPE_FMT           "%" SCNd64
#define MATRIX_FORMAT           SIZE_TYPE_FMT " " SIZE_TYPE_FMT "\n"
#define MATRIX_MARKET_FORMAT    SIZE_TYPE_FMT " " SIZE_TYPE_FMT " " SIZE_TYPE_FMT "\n"
#define POINT_FORMAT            SIZE_TYPE_FMT " " SIZE_TYPE_FMT " " ELEM_FORMAT "\n"

typedef double type_t;
typedef int64_t m_size_t;

typedef struct
{
    type_t **data;
    m_size_t rows, cols;
} matrix_t;

int create_matrix(matrix_t *const, m_size_t, m_size_t);

void delete_matrix(matrix_t *const);

int read_from_file(matrix_t *, const char *const);

int write_elem_to_file(type_t, const char *const);

int write_to_file(matrix_t *, const char *const);

int sum(const matrix_t *const, const matrix_t *, matrix_t *const);

int multiplication(const matrix_t *const, const matrix_t *, matrix_t *const);

int determinant(const matrix_t *const, type_t *);

#endif
