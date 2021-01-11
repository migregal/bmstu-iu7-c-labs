#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "../inc/common.h"

#include "../inc/list.h"
#include "../inc/data_structures.h"

int process(FILE *fin);

char decompose_into_simple(node_t **list, type_t num);

char list_to_num(node_t *list, type_t *res);

char print_list(node_t *list);

char out(type_t num);

char sqr(type_t num);

char division(type_t a, type_t b);

char mul(type_t a, type_t b);

int cmp(void *x, void *y);

int summary(void *x, void *y, void **r, size_t *new_size);

int difference(void *x, void *y, void **r, size_t *new_size);

int sqr_elem(void *x);

#endif
