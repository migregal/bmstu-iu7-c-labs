#ifndef __COMMON_H__
#define __COMMON_H__

#define OK 0000
#define ARG_ERR 0001
#define MEM_ALLOC_ERR 0002
#define MEM_ACCESS_ERR 0003

#define FILE_ENDED 0010
#define DATA_ERROR 0011
#define FILE_NAME_ERROR 0012

#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>

#define LOG_LEVEL NO_LOG
#include "macrologger.h"

#endif
