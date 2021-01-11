#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef int (*compare)(void *, void *);

typedef int (*sum)(void *, void *, void **, size_t *);

typedef int (*diff)(void *, void *, void **, size_t *);

typedef int (*change)(void *);

//! List

typedef struct node node_t;

char list_init(node_t **);

char is_empty(node_t *);

char push(node_t *, void *, size_t);

char pop_back(node_t *, void **);

void free_list(node_t **);

char sort(node_t *, compare);

char each_elem(node_t *, change);

char merge_lists(node_t *, node_t *, node_t *, compare, sum);

char exclude_lists(node_t *, node_t *, node_t *, compare, diff);

//! Iterator

typedef struct iter iter_t;

char iter_init(iter_t **, node_t *);

char cur_data(iter_t *, void **);

char next(iter_t *);

char prev(iter_t *);

char begin(iter_t *);

char end(iter_t *);

void free_iter(iter_t **);

#endif
