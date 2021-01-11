#include <string.h>
#include <stdbool.h>

#include "../inc/file.h"
#include "../inc/vector.h"

#define OK 0
#define ARG_ERROR 100
#define MEM_ERR 101
#define FILE_SIZE_ERR 102
#define FILE_READ_ERR 103
#define SORT_ERR 104
#define FILE_WRITING_ERR 105

#define MAX_FILE_NAME_LEN 256

int parse_args(int argc, char **argv, char *fin_n, char *fout_n, bool *filter_flag)
{
    if (argc < 3 || argc > 4)
        return ARG_ERROR;

    strcpy(fin_n, argv[1]);
    strcpy(fout_n, argv[2]);

    if (argc == 3)
    {
        *filter_flag = false;
        return OK;
    }

    if (strcmp("f", argv[3]) == 0)
    {
        *filter_flag = true;
        return OK;
    }

    return ARG_ERROR;
}

int process(char *fin_n, char *fout_n, bool filter)
{
    vector *vec = NULL;

    size_t size = 0;

    if (get_file_size(fin_n, &size))
        return FILE_SIZE_ERR;

    if (new_vector(&vec, size))
        return MEM_ERR;

    if (read_file(fin_n, vec))
    {
        delete_vector(&vec);
        return FILE_READ_ERR;
    }

    if (sort(vec, filter))
    {
        delete_vector(&vec);
        return SORT_ERR;
    }

    if (write_file(fout_n, vec))
    {
        delete_vector(&vec);
        return FILE_WRITING_ERR;
    }

    delete_vector(&vec);

    return OK;
}

int main(int argc, char **argv)
{
    char fin_n[MAX_FILE_NAME_LEN], fout_n[MAX_FILE_NAME_LEN];

    bool filter = false;

    if (parse_args(argc, argv, fin_n, fout_n, &filter) != OK)
        return ARG_ERROR;

    return process(fin_n, fout_n, filter);
}
