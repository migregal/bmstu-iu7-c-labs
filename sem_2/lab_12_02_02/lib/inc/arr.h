#ifndef __ARR_H__
#define __ARR_H__

#include <stdlib.h>
#include <stdbool.h>

#define LOG_LEVEL NO_LOG
#include "macrologger.h"

#define OK 0000
#define EMPTY_PTR 0001
#define MEM_ALLOC_ERR 0002

int lrotate(void *arr, size_t len, size_t elem_size, size_t dist);

int cpybycond(void *a, size_t la, void *b, size_t lb, size_t elem_size, bool (*cond)(void *data));

#endif
