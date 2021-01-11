/*
    Выбранный целочисленный тип - int
    Алгоритм сортировки - Comb sort (Сортировка расчёской)
    Направление упорядочивания - Прямое
*/

#include <stdlib.h>
#include <string.h>
#include "my_file.h"

#define CREATE_FILE "c"
#define PRINT_NUMBERS "p"
#define SORT_FILE "s"

#define OK 0
#define COMMAND_FORMAT_ERROR 1
#define FILE_SIZE_FOR_CREATION_ERROR 2

int parse_args(int argc, char **argv)
{
    if (argc < 3)
        return COMMAND_FORMAT_ERROR;

    if (strcmp(argv[1], CREATE_FILE) == 0)
    {
        if (argc != 4) 
            return COMMAND_FORMAT_ERROR;

        int file_size;

        if ((file_size = atoi(argv[2])) <= 0)
            return FILE_SIZE_FOR_CREATION_ERROR;

        return create_random_nums_file(argv[3], file_size);
    }

    if (argc != 3)
        return COMMAND_FORMAT_ERROR;

    if (strcmp(argv[1], PRINT_NUMBERS) == 0)
        return print_file(argv[2]);

    if (strcmp(argv[1], SORT_FILE) == 0)
        return sort_file(argv[2]);

    return COMMAND_FORMAT_ERROR;
}

int main(int argc, char **argv)
{
    if (parse_args(argc, argv) != 0)
        return COMMAND_FORMAT_ERROR;

    return OK;
}