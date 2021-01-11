#include <stdio.h>
#include <string.h>
#include "my_file.h"

#define SORT_FILE_BIN "sb"

#define FIND_IN_BIN "fb"

#define REMOVE_BAD_BIN "db"

#define OK 0
#define COMMAND_FORMAT_ERROR 53

int parse_args(int argc, char **argv)
{
    if (argc < 3)
        return COMMAND_FORMAT_ERROR;

    if (strcmp(argv[1], SORT_FILE_BIN) == 0)
    {
        if (argc > 3) 
            return COMMAND_FORMAT_ERROR;

        return sort_file_bin(argv[2]);
    }

    if (strcmp(argv[1], REMOVE_BAD_BIN) == 0)
    {
        if (argc > 3) 
            return COMMAND_FORMAT_ERROR;

        return delete_bad_bin(argv[2]);
    }

    if (argc != 5) 
            return COMMAND_FORMAT_ERROR;

    if (strcmp(argv[1], FIND_IN_BIN) == 0)
        return find_in_file_bin(argv[2], argv[3], argv[4]);

    return COMMAND_FORMAT_ERROR;
}

int main(int argc, char **argv)
{
    int res = parse_args(argc, argv);
    
    if (res)
        return res;

    return OK;
}