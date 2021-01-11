#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/film.h"

#define OK 0
#define ERR 1

#define VECTOR_SIZE_COEF 2

size_t len(films_vec *ptr)
{
    return ptr->len;
}

void free_film(film *temp)
{
    free(temp->name);
    free(temp->title);
}

int clear(films_vec *ptr)
{
    for (size_t i = 0; i < ptr->len; ++i)
        free_film(ptr->arr + i);

    free(ptr->arr);
    ptr->len = 0;

    return OK;
}

int init_film(film *temp, const char *title, const char *name)
{
    if (temp->title || temp->name)
        return NON_EMPTY_PTR_ERR;

    if (!title || !(temp->title = strdup(title)))
        return MEM_ALLOC_ERR;

    if (!name || !(temp->name = strdup(name)))
    {
        free(temp->title);
        return MEM_ALLOC_ERR;
    }

    return OK;
}

int get(films_vec *ptr, size_t idx, film *res)
{
    if (idx >= ptr->len)
        return ERR;

    memcpy(res, ptr->arr + idx, sizeof(film));

    return OK;
}

int set(films_vec *ptr, size_t idx, film *src)
{
    if (idx >= ptr->len)
        return ERR;

    LOG_DEBUG("Setting [%s][%s][%d]", src->name, src->title, src->year);
    ptr->arr[idx].name = strdup(src->name);

    if (!(ptr->arr[idx].name))
        return MEM_ALLOC_ERR;

    ptr->arr[idx].title = strdup(src->title);
    if (!(ptr->arr[idx].title))
    {
        free(ptr->arr[idx].name);
        return MEM_ALLOC_ERR;
    }

    ptr->arr[idx].year = src->year;

    return OK;
}

int append(films_vec *ptr, film *src)
{
    if (ptr->len == ptr->cap)
    {
        ptr->cap = ptr->cap == 0 ? 1 : ptr->cap * VECTOR_SIZE_COEF;
        film *temp = realloc(ptr->arr, ptr->cap * sizeof(film));

        if (temp == NULL)
            return MEM_ALLOC_ERR;

        ptr->arr = temp;
    }

    if (set(ptr, (ptr->len)++, src) != OK)
    {
        (ptr->len)--;
        return ERR;
    }

    return OK;
}

int pop(films_vec *ptr, film *res)
{
    if (ptr->len == 0)
        return ERR;

    if (get(ptr, --(ptr->len), res))
        return ERR;

    if (VECTOR_SIZE_COEF * ptr->len <= ptr->cap)
    {
        ptr->cap /= VECTOR_SIZE_COEF;
        film *temp = realloc(ptr->arr, ptr->cap * sizeof(film));

        if (temp == NULL)
            return MEM_ALLOC_ERR;

        ptr->arr = temp;
    }

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
    if (((film *)first)->year > ((film *)second)->year)
        return 1;

    if (((film *)first)->year < ((film *)second)->year)
        return -1;

    return 0;
}
