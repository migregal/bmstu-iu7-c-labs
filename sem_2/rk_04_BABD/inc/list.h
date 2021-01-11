#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct node node_t;

char push_back(node_t **, void *, size_t);

void reverse(node_t **);

void print_list(node_t *, FILE *, void (*)(FILE *, void *), char);

void free_list(node_t **, void (*)(void *));

#endif
