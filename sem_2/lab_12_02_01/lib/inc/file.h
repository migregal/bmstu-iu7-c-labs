#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdbool.h>

#include "vector.h"

#define FILE_OK 0
#define FILE_ERR -1
#define EMPTY_FILE_ERR -2
#define FILE_DATA_ERR -3

int get_file_size(char *, size_t *);

int read_file(char *, vector *);

int write_file(char *, vector *);

#endif
