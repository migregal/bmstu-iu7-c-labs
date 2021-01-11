#include <dlfcn.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"
#include "vector.h"

#define OK 0000
#define ARG_ERROR 0001
#define MEM_ERR 0002
#define FILE_SIZE_ERR 0003
#define FILE_READ_ERR 0004
#define SORT_ERR 0005
#define FILE_WRITING_ERR 0006

#define LIB_LOADING_ERROR 0010

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

    // Lib and funcs loading
    void *library = dlopen("libsoutils.so", RTLD_LAZY);

    if (!library)
        return LIB_LOADING_ERROR;

    int (*get_file_size_dl)(char *, size_t *);
    *(int **)(&get_file_size_dl) = dlsym(library, "get_file_size");
    if (!get_file_size_dl)
        return dlclose(library) || LIB_LOADING_ERROR;

    int (*read_file_dl)(char *, vector *);
    *(int **)(&read_file_dl) = dlsym(library, "read_file");
    if (!read_file_dl)
        return dlclose(library) || LIB_LOADING_ERROR;

    int (*write_file_dl)(char *, vector *);
    *(int **)(&write_file_dl) = dlsym(library, "write_file");
    if (!write_file_dl)
        return dlclose(library) || LIB_LOADING_ERROR;

    int (*new_vector_dl)(vector **, size_t);
    *(int **)(&new_vector_dl) = dlsym(library, "new_vector");
    if (!new_vector_dl)
        return dlclose(library) || LIB_LOADING_ERROR;

    int (*sort_dl)(vector *, bool);
    *(int **)(&sort_dl) = dlsym(library, "sort");
    if (!sort_dl)
        return dlclose(library) || LIB_LOADING_ERROR;

    int (*delete_vector_dl)(vector **);
    *(int **)(&delete_vector_dl) = dlsym(library, "delete_vector");
    if (!delete_vector_dl)
        return dlclose(library) || LIB_LOADING_ERROR;

    // Process

    if (get_file_size_dl(fin_n, &size))
        return dlclose(library) || LIB_LOADING_ERROR;

    if (new_vector_dl(&vec, size))
        return dlclose(library) || MEM_ERR;

    if (read_file_dl(fin_n, vec))
    {
        delete_vector_dl(&vec);
        return dlclose(library) || FILE_READ_ERR;
    }

    if (sort_dl(vec, filter))
    {
        delete_vector_dl(&vec);
        return dlclose(library) || SORT_ERR;
    }

    if (write_file_dl(fout_n, vec))
    {
        delete_vector_dl(&vec);
        return dlclose(library) || FILE_WRITING_ERR;
    }

    delete_vector_dl(&vec);

    return dlclose(library) || OK;
}

int main(int argc, char **argv)
{
    char fin_n[MAX_FILE_NAME_LEN], fout_n[MAX_FILE_NAME_LEN];

    bool filter = false;

    if (parse_args(argc, argv, fin_n, fout_n, &filter) != OK)
        return ARG_ERROR;

    return process(fin_n, fout_n, filter);
}
