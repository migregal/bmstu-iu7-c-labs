#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include <stdlib.h>

typedef long long type_t;

#define ELEM_FMT "%lld"

typedef struct multiplier multiplier_t;

struct multiplier
{
    type_t num;
    long long count;
};

#endif
