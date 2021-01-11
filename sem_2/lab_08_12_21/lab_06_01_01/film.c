#include <string.h>

#include "film.h"

#define OK 0
#define ERR 1

size_t len(films_arr *ptr)
{
    return ptr->len;
}

int clear(films_arr *ptr)
{
    ptr->len = 0;

    return OK;
}

int get(films_arr *ptr, size_t idx, film *res)
{
    if (idx >= ptr->len)
        return ERR;

    memcpy(res, ptr->arr + idx, sizeof(film));

    return OK;
}

int set(films_arr *ptr, size_t idx, film *src)
{
    if (idx >= ptr->len)
        return ERR;

    memcpy(ptr->arr + idx, src, sizeof(film));

    return OK;
}

int append(films_arr *ptr, film *src)
{
    if (ptr->len == MAX_FILM_ARRAY_LENGTH)
        return ERR;

    if (set(ptr, (ptr->len)++, src) != OK)
    {
        (ptr->len)--;
        return ERR;
    }

    return OK;
}

int pop(films_arr *ptr, film *res)
{
    if (ptr->len == 0)
        return ERR;

    get(ptr, --(ptr->len), res);

    return OK;
}

int compare_title(const void *first, const void *second)
{
    return strcmp(((film *)first)->title, ((film *)second)->title);
}

int compare_name(const void *first, const void *second)
{
    return strcmp(((film *)first)->name, ((film *)second)->name);
}

int compare_year(const void *first, const void *second)
{
    return ((film *)first)->year - ((film *)second)->year;
}
