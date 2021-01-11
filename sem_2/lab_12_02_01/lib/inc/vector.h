#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

#define VECTOR_SIZE_COEF 2

#define VECTOR_OK 0
#define VECTOR_ERR 1
#define VECTOR_MEMORY_ERR 2
#define VECTOR_FILTER_ERROR 3

typedef int (*cmp_fun)(const void *, const void *);

typedef struct vector
{
    int *arr;

    size_t len;
    size_t capacity;

    int *(*begin)(struct vector *ptr);

    int (*set)(struct vector *ptr, size_t idx, int src);
    int (*get)(struct vector *ptr, size_t idx, int *res);

    int (*append)(struct vector *ptr, int src);
    int (*pop)(struct vector *ptr, int *res);

    void (*clear)(struct vector *ptr);
} vector;

int new_vector(vector **ptr, size_t size);

void delete_vector(vector **ptr);

size_t len(vector *ptr);

int sort(vector *, bool);

int compare_vec_elems(const void *, const void *);

#endif
