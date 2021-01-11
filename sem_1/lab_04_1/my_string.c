#include <stdlib.h>
#include <string.h>

#include "my_string.h"

char *my_strchr(const char *str, int ch)
{
    while (*str != (char) ch)
        if (!*str++)
            return 0;
    return (char *) str;
}

size_t my_strcspn(const char *str, const char *sym)
{
    size_t res = 0;
    while (*str && !my_strchr(sym, *str++))
        res++;
    return res;
}
