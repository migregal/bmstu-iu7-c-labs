#include <stdio.h>

#include "../inc/common.h"
#include "../inc/args.h"
#include "../inc/matrix.h"

int process(const parsed_args *const args)
{
    LOG_DEBUG("Args processing");

    if (args->cmd != 'a' && args->cmd != 'm' && args->cmd != 'o')
    {
        LOG_ERROR("Wrong command flag");
        return ARG_ERR;
    }

    matrix_t matrix_a = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int err = OK;

    LOG_DEBUG("First file reading");

    if ((err = read_from_file(&matrix_a, args->fin_1_name)))
    {
        LOG_ERROR("First file reading error");
        return err;
    }

    if (args->cmd == 'o')
    {
        LOG_DEBUG("Matrix determinant calculating");

        type_t det = 0;

        if ((err = determinant(&matrix_a, &det)))
        {
            LOG_ERROR("Determinant calcilating error");
            delete_matrix(&matrix_a);
            return err;
        }

        LOG_DEBUG("Wrintg result to file");

        if ((err = write_elem_to_file(det, args->fout_name)))
            LOG_ERROR("File writing error");

        LOG_DEBUG("Memory freeing");

        delete_matrix(&matrix_a);

        return err;
    }

    matrix_t matrix_b = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    LOG_DEBUG("Reading second file");

    if ((err = read_from_file(&matrix_b, args->fin_2_name)))
    {
        LOG_ERROR("Second file reading error");
        delete_matrix(&matrix_a);
        return err;
    }

    matrix_t matrix_res = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    if (args->cmd == 'a')
    {
        LOG_DEBUG("Creating result matrix [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "]", matrix_a.rows, matrix_a.cols);

        if ((err = create_matrix(&matrix_res, matrix_a.rows, matrix_a.cols)))
        {
            LOG_ERROR("Matrix creation error");
            delete_matrix(&matrix_a);
            delete_matrix(&matrix_b);
            return err;
        }

        LOG_DEBUG("Calculating sum");

        if ((err = sum(&matrix_a, &matrix_b, &matrix_res)))
            LOG_ERROR("Sum calculating error");

        LOG_DEBUG("Wrinting result to file");

        if (!err && (err = write_to_file(&matrix_res, args->fout_name)))
            LOG_ERROR("File writing error");

        LOG_DEBUG("Memory freeing");

        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        delete_matrix(&matrix_res);

        return err;
    }

    LOG_DEBUG("Creating result matrix [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "]", matrix_a.rows, matrix_b.cols);
    if ((err = create_matrix(&matrix_res, matrix_a.rows, matrix_b.cols)))
    {
        LOG_ERROR("Memory allocation for result matrix failed");

        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);

        return err;
    }

    LOG_DEBUG("Product calculating");

    err = multiplication(&matrix_a, &matrix_b, &matrix_res);

    if (err)
        LOG_ERROR("Multiplication error");
    else
    {
        LOG_DEBUG("Creating result matrix [" SIZE_TYPE_FMT " x " SIZE_TYPE_FMT "]", matrix_a.rows, matrix_a.cols);
        if ((err = write_to_file(&matrix_res, args->fout_name)))
            LOG_ERROR("File writing error");
    }

    LOG_DEBUG("Memory freeing");

    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);
    delete_matrix(&matrix_res);

    return err;
}

int main(int argc, char **argv)
{
    parsed_args args;

    clean_args(&args);

    if (parse_args(&args, argc, argv))
    {
        LOG_ERROR("Wrong arguments");
        return ARG_ERR;
    }

    LOG_DEBUG("args parsed");

    return process(&args);
}
