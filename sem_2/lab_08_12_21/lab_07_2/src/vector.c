#include <string.h>

#include "../inc/vector.h"

#define SWAP(a, b, size)                      \
    do                                        \
    {                                         \
        register size_t __size = (size);      \
        register char *__a = (a), *__b = (b); \
        do                                    \
        {                                     \
            char __tmp = *__a;                \
            *__a++ = *__b;                    \
            *__b++ = __tmp;                   \
        } while (--__size > 0);               \
    } while (0)

static int *begin(vector *ptr)
{
    return ptr->arr;
}

static int set(vector *ptr, size_t idx, int src)
{
    if (idx >= ptr->len)
        return VECTOR_ERR;

    ptr->arr[idx] = src;

    return VECTOR_OK;
}

static int get(vector *ptr, size_t idx, int *res)
{
    if (idx >= ptr->len)
        return VECTOR_ERR;

    *res = *(ptr->arr + idx);

    return VECTOR_OK;
}

static int append(vector *ptr, int src)
{
    if (ptr->len == ptr->capacity)
    {
        ptr->capacity = ptr->capacity == 0 ? 1 : ptr->capacity * VECTOR_SIZE_COEF;
        int *temp = (int *)realloc(ptr->arr, ptr->capacity * sizeof(int));

        if (temp == NULL)
            return VECTOR_MEMORY_ERR;

        ptr->arr = temp;
    }

    if (set(ptr, (ptr->len)++, src))
    {
        (ptr->len)--;
        return VECTOR_ERR;
    }

    return VECTOR_OK;
}

static int pop(vector *ptr, int *res)
{
    if (ptr->len == 0)
        return VECTOR_ERR;

    if (get(ptr, --(ptr->len), res))
        return VECTOR_ERR;

    if (VECTOR_SIZE_COEF * ptr->len <= ptr->capacity)
    {
        ptr->capacity /= VECTOR_SIZE_COEF;
        int *temp = (int *)realloc(ptr->arr, ptr->capacity * sizeof(int));

        if (temp == NULL)
            return VECTOR_MEMORY_ERR;

        ptr->arr = temp;
    }

    return VECTOR_OK;
}

static void clear(vector *ptr)
{
    free(ptr->arr);
    ptr->arr = NULL;

    ptr->len = 0;
    ptr->capacity = 0;
}

void delete_vector(vector **ptr)
{
    if (ptr == NULL || *ptr == NULL)
        return;

    (*ptr)->clear(*ptr);
    free(*ptr);
}

int new_vector(vector **ptr, size_t size)
{
    if (ptr == NULL || *ptr != NULL)
        return VECTOR_ERR;

    *ptr = (vector *)malloc(sizeof(vector));

    if (*ptr == NULL)
        return VECTOR_MEMORY_ERR;

    (*ptr)->len = 0;
    (*ptr)->capacity = size == 0 ? 1 : size;

    (*ptr)->arr = (int *)malloc((*ptr)->capacity * sizeof(int));

    if ((*ptr)->arr == NULL)
    {
        free(*ptr);
        return VECTOR_MEMORY_ERR;
    }

    (*ptr)->begin = &begin;

    (*ptr)->get = &get;
    (*ptr)->set = &set;

    (*ptr)->append = &append;
    (*ptr)->pop = &pop;

    (*ptr)->clear = &clear;

    return VECTOR_OK;
}

size_t len(vector *ptr)
{
    return ptr->len;
}

void mysort(void *base, size_t n, size_t size, cmp_fun compare_vec_elems)
{
    if (n == 0 || base == NULL || compare_vec_elems == NULL || size == 0)
        return;

    register char *b_ptr = (char *)base;

    char *last, *j_next;

    for (char *i = b_ptr + (n - 1) * size; i > b_ptr; i = last)
        for (char *j = last = b_ptr; j < i; j += size)
        {
            if (compare_vec_elems(j, j_next = j + size) < 0)
                continue;

            SWAP(last = j, j_next, size);
        }
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
        return VECTOR_FILTER_ERROR;

    *pb_dst = *pe_dst = NULL;

    size_t size = 0;

    for (int *i = (int *)pb_src; i < pe_src && (*i) >= 0; i++, size++);

    if (!size)
        return VECTOR_FILTER_ERROR;

    *pb_dst = (int *)malloc(size * sizeof(int));

    if (!*pb_dst)
        return VECTOR_MEMORY_ERR;

    *pe_dst = *pb_dst + size;

    for (size_t i = 0; i < size; i++)
        *(*pb_dst + i) = *(pb_src + i);

    return VECTOR_OK;
}

int compare_vec_elems(const void *a, const void *b)
{
    int a1 = *((int *)a);
    int b1 = *((int *)b);

    return a1 > b1 ? 1 : (a1 == b1) ? 0 : -1;
}

int sort(vector *src, bool filter)
{
    if (filter)
    {
        int *b_ptr = NULL, *e_ptr = NULL;

        if (key(src->begin(src), src->begin(src) + len(src), &b_ptr, &e_ptr))
            return VECTOR_ERR;

        free(src->arr);
        src->arr = b_ptr;
        src->len = (size_t)(e_ptr - b_ptr);
        src->capacity = src->len;
    }

    mysort((void *)src->begin(src), len(src), sizeof(*(src->begin(src))), compare_vec_elems);

    return VECTOR_OK;
}

#undef SWAP
