#include <stdio.h>

#include "../inc/common.h"
#include "../inc/matrix.h"

void delete_matrix(matrix_t *const matrix)
{
    if (!matrix)
        return;

    for (int clean = 0; clean < matrix->rows; ++clean)
        if (*(matrix->data + clean))
            free(*(matrix->data + clean));

    free(matrix->data);

    matrix->cols = 0;
    matrix->rows = 0;
}

int create_matrix(matrix_t *const matrix, m_size_t rows, m_size_t cols)
{
    if (!matrix)
        return EMPTY_PTR_ERROR;

    LOG_DEBUG("Checking matrix size");

    if (matrix->data)
    {
        LOG_ERROR("Matrix variable isn\'t empty");
        return NON_EMPTY_MATRIX_ERROR;
    }

    if (0 == rows || 0 == cols)
    {
        LOG_ERROR("Wrong matrix size" SIZE_TYPE_FMT " " SIZE_TYPE_FMT, rows, cols);
        return DATA_ERROR;
    }

    LOG_DEBUG("Memory allocation");

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = (type_t **)calloc(matrix->rows, sizeof(type_t *));

    LOG_DEBUG("Checking memory allocation");

    if (!matrix->data)
    {
        LOG_ERROR("Matrix memory allocaton error");
        return MEMORY_ALLOC_ERROR;
    }

    LOG_DEBUG("Rows allocation [" SIZE_TYPE_FMT "]", matrix->rows);
    for (m_size_t row = 0; row < matrix->rows; ++row)
    {
        matrix->data[row] = (type_t *)calloc(matrix->cols, sizeof(type_t));

        LOG_DEBUG("Checking row [" SIZE_TYPE_FMT "] allocation", row);

        if (!(matrix->data[row]))
        {
            LOG_ERROR("Row memory allocaton error [" SIZE_TYPE_FMT " / " SIZE_TYPE_FMT "]", row, matrix->rows);
            delete_matrix(matrix);
            return MEMORY_ALLOC_ERROR;
        }
    }

    return OK;
}

int read_from_file(matrix_t *matrix, const char *const file_name)
{
    if (!matrix)
        return EMPTY_PTR_ERROR;

    LOG_DEBUG("Opening file for reading [%s]", file_name);

    FILE *fin = NULL;

    fin = fopen(file_name, "r");

    LOG_DEBUG("Checking file correctness");

    if (!fin)
    {
        LOG_ERROR("Error while opening file for reading [%s]", file_name);
        return FILE_OPEN_ERROR;
    }

    m_size_t rows = 0, cols = 0, num = 0;

    LOG_DEBUG("Reading matrix size from file");

    if (3 != fscanf(fin, MATRIX_MARKET_FORMAT, &rows, &cols, &num))
    {
        LOG_ERROR("Matrix size reading error");
        fclose(fin);
        return FILE_READ_ERROR;
    }

    LOG_DEBUG("Checking matrix size correctness");

    if (0 >= rows || 0 >= cols)
    {
        LOG_ERROR("Wrong matrix size [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "]", rows, cols);
        fclose(fin);
        return MEMORY_ALLOC_ERROR;
    }

    if (num < 0 || num > rows * cols)
    {
        LOG_ERROR("Wrong matrix elems count [" SIZE_TYPE_FMT "]", num);
        fclose(fin);
        return MEMORY_ALLOC_ERROR;
    }

    LOG_DEBUG("Matrix creation");

    if (create_matrix(matrix, rows, cols))
    {
        LOG_ERROR("Matrix creation error");
        fclose(fin);
        return MEMORY_ALLOC_ERROR;
    }

    m_size_t row = 0, col = 0;
    type_t val = 0;

    LOG_DEBUG("Reading non-zero matrix elems [" SIZE_TYPE_FMT "]", num);

    m_size_t i = 0;
    for (; i < num && !feof(fin); ++i)
    {
        if (3 != fscanf(fin, POINT_FORMAT, &row, &col, &val))
        {
            LOG_ERROR("Matrix elem reading error");
            delete_matrix(matrix);
            fclose(fin);
            return FILE_READ_ERROR;
        }

        LOG_DEBUG("Checking matrix elem correctness [" SIZE_TYPE_FMT " / " SIZE_TYPE_FMT "]", i, num);

        if (0 >= col || 0 >= row || (--row) >= matrix->rows || (--col) >= matrix->cols)
        {
            LOG_ERROR("Wrong matrix elem coords [" SIZE_TYPE_FMT ", " SIZE_TYPE_FMT "]", row, col);
            delete_matrix(matrix);
            fclose(fin);
            return FILE_READ_ERROR;
        }

        matrix->data[row][col] = val;
    }

    if (i != num)
    {
        LOG_ERROR("Wrong matrix elems count");
        delete_matrix(matrix);
        fclose(fin);
        return FILE_READ_ERROR;
    }

    return (EOF == fclose(fin));
}

int write_elem_to_file(type_t num, const char *const file_name)
{
    LOG_DEBUG("Opening file for writing [%s]", file_name);

    FILE *fout = NULL;

    fout = fopen(file_name, "w");

    LOG_DEBUG("Checking file correctness");

    if (!fout)
    {
        LOG_ERROR("Error while opening file for writing [%s]", file_name);
        return FILE_OPEN_ERROR;
    }

    LOG_DEBUG("Writing elem to file " ELEM_FORMAT, num);

    if (!fprintf(fout, ELEM_FORMAT "\n", num))
    {
        LOG_ERROR("Writing to file error");
        fclose(fout);
        return FILE_WRITE_ERROR;
    }

    return (EOF == fclose(fout));
}

int write_to_file(matrix_t *matrix, const char *const file_name)
{
    if (!matrix)
        return EMPTY_PTR_ERROR;

    LOG_DEBUG("Opening file for writing [%s]", file_name);

    FILE *fout = NULL;

    fout = fopen(file_name, "w");

    LOG_DEBUG("Checking file correctness");

    if (!fout)
    {
        LOG_ERROR("Error while opening file for writing [%s]", file_name);
        return FILE_OPEN_ERROR;
    }

    LOG_DEBUG("Writing matrix size to file");

    if (!fprintf(fout, MATRIX_FORMAT, matrix->rows, matrix->cols))
    {
        LOG_ERROR("Matrix size writing to file error");
        fclose(fout);
        return FILE_WRITE_ERROR;
    }

    LOG_DEBUG("Writing matrix elems to file");

    for (m_size_t i = 0; i < matrix->rows; ++i)
    {
        LOG_DEBUG("Writing row [" SIZE_TYPE_FMT " / " SIZE_TYPE_FMT "]", i + 1, matrix->rows);

        for (m_size_t j = 0; j < matrix->cols; ++j)
        {
            if (fprintf(fout, ELEM_FORMAT, matrix->data[i][j]) && (matrix->cols - 1 == j || fprintf(fout, " ")))
                continue;

            LOG_ERROR("Matrix elem writing to file error");

            fclose(fout);
            return FILE_WRITE_ERROR;
        }

        LOG_DEBUG("Row ended");
        if (!fprintf(fout, "\n"))
        {
            LOG_ERROR("Matrix elem writing to file error");

            fclose(fout);
            return FILE_WRITE_ERROR;
        }
    }

    return (EOF == fclose(fout));
}

int sum(const matrix_t *const m_a, const matrix_t *m_b, matrix_t *const res)
{
    if (!m_a || !m_b || !res)
        return EMPTY_PTR_ERROR;

    LOG_DEBUG("Checking matrix size correctness");

    if (m_a->rows != m_b->rows || m_a->cols != m_b->cols)
    {
        LOG_ERROR("Wrong matrix size [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "] and [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "]",
                  m_a->rows, m_a->cols,
                  m_b->rows, m_b->cols);

        return MATRIX_SIZE_ERROR;
    }

    LOG_DEBUG("Result matrix creation (if it doesn\'t exist)");

    if (!(res->data) && create_matrix(res, m_a->rows, m_a->cols))
    {
        LOG_ERROR("Matrix creation error");
        return MEMORY_ALLOC_ERROR;
    }

    LOG_DEBUG("Calculating sum");

    for (m_size_t r = 0; r < m_a->rows; ++r)
        for (m_size_t c = 0; c < m_a->cols; ++c)
            res->data[r][c] = m_a->data[r][c] + m_b->data[r][c];

    return OK;
}

int multiplication(const matrix_t *const m_a, const matrix_t *m_b, matrix_t *const res)
{
    if (!m_a || !m_b || !res)
        return EMPTY_PTR_ERROR;

    LOG_DEBUG("Checking matrix size correctness");

    if (m_a->cols != m_b->rows)
    {
        LOG_ERROR("Wrong matrix size [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "] and [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "]",
                  m_a->rows, m_a->cols,
                  m_b->rows, m_b->cols);

        return MATRIX_SIZE_ERROR;
    }

    LOG_DEBUG("Result matrix creation (if it doesn\'t exist)");

    if (!(res->data) && create_matrix(res, m_a->rows, m_b->cols))
    {
        LOG_ERROR("Matrix creation error");
        return MEMORY_ALLOC_ERROR;
    }

    LOG_DEBUG("Calculating product");
    for (m_size_t r = 0; r < m_a->rows; ++r)
        for (m_size_t c = 0; c < m_b->cols; ++c)
        {
            type_t sum = 0;
            for (m_size_t k = 0; k < m_a->cols; k++)
                sum += m_a->data[r][k] * m_b->data[k][c];

            res->data[r][c] = sum;
        }

    return OK;
}

void get_matrix_without_row_and_col(const matrix_t *const matrix, const m_size_t row, const m_size_t col, matrix_t *new_matrix)
{
    if (!matrix || !new_matrix)
        return;

    m_size_t offset_row = 0;
    m_size_t offset_col = 0;

    for (m_size_t i = 0; i < matrix->rows - 1; i++)
    {
        if (row == i)
            offset_row = 1;

        offset_col = 0;
        for (m_size_t j = 0; j < matrix->cols - 1; j++)
        {
            if (col == j)
                offset_col = 1;

            new_matrix->data[i][j] = matrix->data[i + offset_row][j + offset_col];
        }
    }
}

int determinant(const matrix_t *const matrix, type_t *det)
{
    if (!matrix)
        return EMPTY_PTR_ERROR;

    if (matrix->cols != matrix->rows)
        return MATRIX_SIZE_ERROR;

    if (1 == matrix->rows)
    {
        *det = matrix->data[0][0];
        return OK;
    }

    if (2 == matrix->rows)
    {
        *det = matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
        return OK;
    }

    matrix_t new_matrix;
    new_matrix.data = NULL;

    int err = 0;

    if ((err = create_matrix(&new_matrix, matrix->rows - 1, matrix->cols - 1)))
    {
        LOG_ERROR("Matrix creation error");
        return err;
    }

    type_t res = 0;
    int sign = 1;

    for (m_size_t j = 0; j < matrix->cols; ++j)
    {
        LOG_DEBUG("Creating matrix without row [0] and col [" SIZE_TYPE_FMT "]", j);

        get_matrix_without_row_and_col(matrix, 0, j, &new_matrix);

        type_t rec_det = 0;

        LOG_DEBUG("Calculating smaller matrix determinant");

        if ((err = determinant(&new_matrix, &rec_det)))
        {
            LOG_ERROR("Determinant calculating error");

            delete_matrix(&new_matrix);
            return err;
        }

        LOG_DEBUG("Result is " ELEM_FORMAT, rec_det);

        res += sign * matrix->data[0][j] * rec_det;
        sign = -sign;
    }

    LOG_DEBUG("Result is " ELEM_FORMAT, res);

    LOG_DEBUG("Memory freeing");

    delete_matrix(&new_matrix);

    *det = res;

    return OK;
}
