#include "defines.h"
#include "list.h"
#include "process.h"

void print(FILE *fout, void *el)
{
    char c = *((char *)el);

    fprintf(fout, "%c", '\n' == c ? ' ' : c);
}

int process(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
        return ARG_ERR;

    node_t *list = NULL;

    FILE *fin = fopen(argv[1], "r");

    if (!fin)
    {
        free_list(&list, free);
        return FILE_READ_ERR;
    }

    char a;

    while (1 == fscanf(fin, "%c", &a))
    {
        push_back(&list, &a, sizeof(char));
    }

    fclose(fin);

    reverse(&list);

    FILE *fout = fopen(argv[2], "w");

    if (!fout)
    {
        free_list(&list, free);
        return FILE_WRITE_ERR;
    }

    print_list(list, fout, print, '\n');

    fclose(fout);
    free_list(&list, free);

    return OK;
}
