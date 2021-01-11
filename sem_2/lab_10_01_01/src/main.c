#include <stdio.h>
#include <string.h>

#include "common.h"
#include "list.h"
#include "film.h"
#include "io.h"

int cmp(const void *a, const void *b)
{
    if (*(int *)a > *(int *)b)
        return 1;

    if (*(int *)a < *(int *)b)
        return -1;

    return 0;
}

int parse_args(int argc, char **argv, char **fin_n, char **fout_n)
{
    if (argc != 3)
        return ARG_ERR;

    if (!(*fin_n = realloc(*fin_n, sizeof(char) * strlen(argv[1]))))
        return MEM_ALLOC_ERR;

    strcpy(*fin_n, argv[1]);

    if (!(*fout_n = realloc(*fout_n, sizeof(char) * strlen(argv[2]))))
    {
        free(*fin_n);
        return MEM_ALLOC_ERR;
    }

    strcpy(*fout_n, argv[2]);

    return OK;
}

int process(int argc, char **argv)
{
    char *fin_n = NULL, *fout_n = NULL;

    if (parse_args(argc, argv, &fin_n, &fout_n))
        return ARG_ERR;

    node_t *list = NULL;

    int rc = read_file(&list, fin_n);

    if (rc)
        return rc;

    remove_duplicates(&list, compare_films);

    write_file(&list, fout_n);

    return OK;
}

int main(int argc, char **argv)
{
    return process(argc, argv);
}
