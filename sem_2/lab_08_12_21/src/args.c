#include <string.h>

#include "../inc/common.h"
#include "../inc/args.h"

int is_empty(const parsed_args *args)
{
    return (!args->cmd && !args->fin_1_name && !args->fin_2_name && !args->fout_name);
}

void clean_args(parsed_args *args)
{
    LOG_DEBUG("Cleaning args variable");

    args->cmd = 0;
    args->fin_1_name = NULL;
    args->fin_2_name = NULL;
    args->fout_name = NULL;
}

int parse_args(parsed_args *args, int argc, char **argv)
{
    LOG_DEBUG("Checking if args are empty");

    if (!is_empty(args))
    {
        LOG_ERROR("Args variable isn\'t empty");
        return ARG_ERR;
    }

    LOG_DEBUG("Checking args count");

    if (argc < 4 || argc > 5)
    {
        LOG_ERROR("Incorrect args count");
        return ARG_ERR;
    }

    LOG_DEBUG("Checking args format");

    if (!strcmp(argv[1], "a"))
        args->cmd = 'a';
    else if (!strcmp(argv[1], "m"))
        args->cmd = 'm';
    else if (!strcmp(argv[1], "o"))
        args->cmd = 'o';
    else
    {
        LOG_ERROR("Wrong command arg");
        return CMD_ERR;
    }

    LOG_DEBUG("First file\'s name saving");

    args->fin_1_name = argv[2];

    LOG_DEBUG("Checking if cmd is \'o\'");

    if (args->cmd == 'o')
    {
        LOG_DEBUG("Checking args count for \'o\' option");
        if (argc != 4)
        {
            LOG_ERROR("Incorrect args count");
            clean_args(args);
            return ARG_ERR;
        }

        args->fout_name = argv[3];

        return OK;
    }

    LOG_DEBUG("Checking args count for \'a\' or \'m\' option");

    if (argc != 5)
    {
        LOG_ERROR("Incorrect args count");
        clean_args(args);
        return ARG_ERR;
    }

    LOG_DEBUG("File names saving");

    args->fin_2_name = argv[3];
    args->fout_name = argv[4];

    return OK;
}
