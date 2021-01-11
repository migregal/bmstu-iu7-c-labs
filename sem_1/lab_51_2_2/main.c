#include <stdio.h>
#include "my_algorithm.h"

#define OK 0
#define ARG_ERROR -1
#define FILE_ERROR -2
#define DATA_ERROR -3

int main(int argc, char **argv)
{
    FILE *f;
    
    if (argc != 2)
        return ARG_ERROR;

    f = fopen(argv[1], "r");

    if (f == NULL)
        return FILE_ERROR;

    double avg, res;

    if (get_average_num(f, &avg) != 0)
        return DATA_ERROR;

    if (get_nums_disp(f, avg, &res))
        return DATA_ERROR;

    printf("%lf\n", res);
    
    if (fclose(f) == EOF)
        return FILE_ERROR;

    return OK;
}