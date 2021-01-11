#include <string.h>
#include "arr.h"

#define swap(_a_, _b_, _t_, _size_) \
    do                              \
    {                               \
        memcpy(_t_, _a_, _size_);   \
        memcpy(_a_, _b_, _size_);   \
        memcpy(_b_, _t_, _size_);   \
    } while (0)

int lrotate(void *arr, size_t len, size_t elem_size, size_t dist)
{
    LOG_DEBUG("Rotating array of size %zu for %zu steps", len, dist);
    if (!arr)
    {
        LOG_ERROR("Empty data ptr");
        return EMPTY_PTR;
    }

    if (!len || !(dist %= len))
    {
        LOG_DEBUG("Empty list or zero rotation");
        return OK;
    }

    void *first = arr;
    void *middle = (char *)arr + elem_size * dist;
    void *last = (char *)arr + elem_size * (len - 1);

    void *t = malloc(elem_size * sizeof(char));

    if (!t)
    {
        LOG_ERROR("Temp mem allocation err");
        return MEM_ALLOC_ERR;
    }

    LOG_DEBUG("Rotating");
    void *next = middle;
    while (first != next)
    {
        swap(first, next, t, elem_size);

        first = (char *)first + elem_size;
        next = (char *)next + elem_size;

        if ((char *)next == (char *)last + elem_size)
            next = middle;
        else if (first == middle)
            middle = next;
    }
    free(t);
    LOG_DEBUG("Rotated");
    return OK;
}

int cpybycond(void *a, size_t la, void *b, size_t lb, size_t elem_size, bool (*cond)(void *data))
{
    LOG_DEBUG("Copying by cond check");
    if (!a || !b || !lb)
    {
        LOG_ERROR("Empty data ptr");
        return EMPTY_PTR;
    }

    LOG_DEBUG("Copying values");
    for (size_t i = 0, j = 0; i < la && j < lb; i++)
        if (cond((void *)((char *)a + i * elem_size)))
            memcpy((char *)b + j++ * elem_size, (char *)a + i * elem_size, elem_size);
    LOG_DEBUG("Copied");
    return OK;
}
