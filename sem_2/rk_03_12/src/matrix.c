#include <stdio.h>

#include "common.h"
#include "matrix.h"

#define MATR(__ptr__, __a__, __b__) \
    (__ptr__->data)[(__a__)*__ptr__->cols + (__b__)]

#define FOREACH(__x__, __y__)                      \
    for (size_t __i__ = 0; __i__ < __x__; ++__i__) \
        for (size_t __j__ = 0; __j__ < __y__; ++__j__)

int create_matrix(matrix_t *matrix, size_t rows, size_t cols)
{
    matrix->data = calloc(rows * cols, sizeof(int));

    if (!(matrix->data))
        return MEM_ALLOC_ERR;

    matrix->cols = cols;
    matrix->rows = rows;

    return OK;
}

void delete_matrix(matrix_t *matrix)
{
    free(matrix->data);
    matrix->rows = 0;
    matrix->cols = 0;
}

int read_matrix(matrix_t *matrix, char *filename)
{
    LOG_DEBUG("Opening file");

    FILE *fin = fopen(filename, "r");

    if (!fin)
    {
        LOG_ERROR("Error while opening file");
        return FILE_OPEN_ERR;
    }

    LOG_DEBUG("Reading matrix fmt");
    long long rows, cols;

    if (2 != fscanf(fin, "%lld %lld", &rows, &cols))
    {
        LOG_ERROR("Error while matrix fmt reading");
        fclose(fin);
        return FILE_READ_ERR;
    }

    if (rows <= 0 || cols <= 0)
    {
        LOG_ERROR("Wrong matrix fmt");
        fclose(fin);
        return MATRIX_FMT_ERR;
    }

    LOG_DEBUG("Creating matrix [%lld, %lld]", rows, cols);

    if (create_matrix(matrix, rows, cols))
    {
        LOG_ERROR("Error while matrix creation");
        fclose(fin);
        return MEM_ALLOC_ERR;
    }

    LOG_DEBUG("Reading matrix");

    FOREACH(rows, cols)
    {
        if (1 == fscanf(fin, "%d", &(MATR(matrix, __i__, __j__))))
            continue;

        LOG_ERROR("Elem reading error on [%zu, %zu]", __i__, __j__);

        delete_matrix(matrix);
        fclose(fin);
        return MATRIX_DATA_ERR;
    }

    LOG_DEBUG("Matrix readed");

    return fclose(fin);
}

int get_elem_val(matrix_t const *const matrix, size_t row, size_t col)
{
    int res = 0;

    if (row > 0 && col > 0)
        res += -1 == (MATR(matrix, row - 1, col - 1));
    if (row > 0)
    {
        res += -1 == (MATR(matrix, row - 1, col));
    }

    if (row > 0 && col < matrix->cols - 1)
        res += -1 == (MATR(matrix, row - 1, col + 1));

    if (col > 0)
        res += -1 == (MATR(matrix, row, col - 1));

    if (col < matrix->cols - 1)
        res += -1 == (MATR(matrix, row, col + 1));

    if (row < matrix->rows - 1 && col > 0)
        res += -1 == (MATR(matrix, row + 1, col - 1));

    if (row < matrix->rows - 1)
        res += -1 == (MATR(matrix, row + 1, col));

    if (row < matrix->rows - 1 && col < matrix->cols - 1)
        res += -1 == (MATR(matrix, row + 1, col + 1));

    return res;
}

int process_matrix(matrix_t *matrix)
{
    FOREACH(matrix->rows, matrix->cols)
    {
        if (MATR(matrix, __i__, __j__))
            continue;

        MATR(matrix, __i__, __j__) =
            get_elem_val(matrix, __i__, __j__);
    }

    return OK;
}

int print_matrix(matrix_t *matrix, char *filename)
{
    FILE *fout = fopen(filename, "w");

    if (!fout)
        return FILE_OPEN_ERR;

    if (0 > fprintf(fout, "%zu %zu\n", matrix->rows, matrix->cols))
    {
        fclose(fout);
        return MATRIX_FMT_ERR;
    }

    FOREACH(matrix->rows, matrix->cols)
    {
        if (0 > fprintf(fout, "%d", MATR(matrix, __i__, __j__)))
        {
            fclose(fout);
            return FILE_WRITE_ERR;
        }

        if ((0 > fprintf(fout, (__j__ == matrix->cols - 1) ? "\n" : " ")))
        {
            fclose(fout);
            return FILE_WRITE_ERR;
        }
    }

    fclose(fout);
    return OK;
}

#undef MATR
#undef FOREACH
