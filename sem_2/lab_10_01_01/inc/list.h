#ifndef __LIST_H__
#define __LIST_H__

#include "common.h"

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

int create_node(node_t **node, const void *data, size_t size);

void free_node(node_t **node);

void free_list(node_t **head);

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));

void insert(node_t **head, node_t *elem, node_t *before);

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

void sorted_insert(node_t **head, node_t *elem, int (*comparator)(const void *, const void *));

void *pop_front(node_t **head);

#endif
