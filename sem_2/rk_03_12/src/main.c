#include "common.h"
#include "matrix.h"

int main(void)
{
    matrix_t matrix;

    int err = OK;

    LOG_DEBUG("Reading matrix");

    if ((err = read_matrix(&matrix, "in.txt")))
    {
        LOG_ERROR("File reading error [%d]", err);
        delete_matrix(&matrix);
        return err;
    }

    LOG_DEBUG("Processing matrix");
    if ((err = process_matrix(&matrix)))
    {
        LOG_ERROR("Processing error [%d]", err);
        return err;
    }

    if ((err = print_matrix(&matrix, "out.txt")))
    {
        LOG_ERROR("File writing error [%d]", err);
        return err;
    }

    delete_matrix(&matrix);
    return err;
}
