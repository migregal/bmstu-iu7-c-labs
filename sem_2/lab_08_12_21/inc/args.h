#ifndef __ARGS_H__
#define __ARGS_H__

typedef struct
{
    char cmd;
    const char *fin_2_name;
    const char *fin_1_name;
    const char *fout_name;
} parsed_args;

void clean_args(parsed_args *args);

int parse_args(parsed_args *args, int argc, char **argv);

#endif
