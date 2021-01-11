#include <stdlib.h>
#include <string.h>

#include "../inc/file.h"

#define MAX_STR_LEN 12

int get_file_size(char *file_name, size_t *size)
{
    FILE *f = fopen(file_name, "r");

    if (f == NULL)
        return FILE_ERR;

    for (int temp; fscanf(f, "%d", &temp) == 1; (*size)++)
        if (ferror(f))
        {
            fclose(f);
            return FILE_ERR;
        }

    if (!feof(f))
    {
        fclose(f);
        return FILE_ERR;
    }

    fclose(f);

    if (!(*size))
        return FILE_DATA_ERR;

    return FILE_OK;
}

int read_file(char *file_name, vector *dest)
{
    dest->clear(dest);

    FILE *f = fopen(file_name, "r");

    if (f == NULL)
        return FILE_ERR;

    for (int temp; fscanf(f, "%d", &temp) == 1;)
        if (dest->append(dest, temp))
        {
            fclose(f);
            return FILE_ERR;
        }


    if (!feof(f))
    {
        fclose(f);
        return FILE_ERR;
    }

    fclose(f);

    if (len(dest) == 0)
        return EMPTY_FILE_ERR;

    return FILE_OK;
}

int write_file(char *file_name, vector *vec)
{
    FILE *fout = fopen(file_name, "w");

    if (fout == NULL)
        return FILE_DATA_ERR;

    for (size_t i = 0; i < len(vec); i++)
    {
        int x;
        if (vec->get(vec, i, &x))
        {
            fclose(fout);
            return FILE_ERR;
        }

        fprintf(fout, " %d", x);
    }

    fprintf(fout, "\n");
    fclose(fout);

    return FILE_OK;
}
