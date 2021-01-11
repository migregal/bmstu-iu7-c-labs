#ifndef __COMMON_H__
#define __COMMON_H__

#define OK 00
#define WRONG_CMD 0001

#define INPUT_ERR 0010
#define UNINITIALIZED_PTR_ERR 0011
#define INITIALIZED_PTR_ERR 0012
#define MEM_ALLOC_ERR 0013
#define MEM_ACCESS_ERR 0014
#define ELEM_VAL_ERR 0015
#define DIVISION_BY_ZERO_ERR 0016

#define _GNU_SOURCE

#define LOG_LEVEL NO_LOG
#include "macrologger.h"

#endif
