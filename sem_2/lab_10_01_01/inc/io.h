#ifndef __IO_H__
#define __IO_H__

#include "common.h"
#include "list.h"

int read_file(node_t **head, char *file_n);

int write_file(node_t **head, char *file_name);

#endif
