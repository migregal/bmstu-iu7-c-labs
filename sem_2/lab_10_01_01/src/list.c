#include <string.h>
#include <stdio.h>
#include "list.h"

int create_node(node_t **node, const void *data, size_t size)
{
    if (*node)
        return MEM_ACCESS_ERR;

    if (!(*node = malloc(sizeof(node_t))))
        return MEM_ALLOC_ERR;

    if (!((*node)->data = malloc(size)))
    {
        free(*node);
        return MEM_ALLOC_ERR;
    }

    if (data)
        memcpy((*node)->data, data, size);

    (*node)->next = NULL;

    return OK;
}

void free_node(node_t **node)
{
    if (!node || !*node)
        return;

    if ((*node)->data)
        free((*node)->data);

    free(*node);
    *node = NULL;
}

void free_list(node_t **head)
{
    node_t *temp = NULL;

    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free_node(&temp);
    }

    *head = NULL;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    node_t *res = head;

    while (res && comparator(res->data, data))
        res = res->next;

    return res;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (!head || !elem)
        return;

    if (!(*head))
    {
        *head = elem;
        return;
    }

    if (before == *head)
    {
        elem->next = *head;
        *head = elem;
        return;
    }

    node_t *ptr = *head;
    while (ptr && ptr->next != before)
        ptr = ptr->next;

    if (!ptr)
        return;

    elem->next = ptr->next;
    ptr->next = elem;
}

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *))
{
    if (!head || !(*head))
        return;

    for (node_t *ptr = (*head); ptr->next;)
    {
        if (find(*head, ptr->next->data, comparator) == ptr->next)
        {
            ptr = ptr->next;
            continue;
        }

        node_t *temp = ptr->next;
        ptr->next = ptr->next->next;
        free_node(&temp);
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *res = NULL;

    node_t *ptr = head;
    while (ptr != NULL)
    {
        node_t *next = ptr->next;

        sorted_insert(&res, ptr, comparator);

        ptr = next;
    }

    return res;
}

void sorted_insert(node_t **head, node_t *elem, int (*comparator)(const void *, const void *))
{
    if (!head || !elem)
        return;

    if (!(*head) || comparator((*head)->data, elem->data) >= 0)
    {
        elem->next = *head;
        *head = elem;
        return;
    }

    node_t *ptr = *head;
    while (ptr->next && comparator(ptr->next->data, elem->data) < 0)
        ptr = ptr->next;

    elem->next = ptr->next;
    ptr->next = elem;
}

void *pop_front(node_t **head)
{
    if (!head || !*head)
        return NULL;

    void *data = (*head)->data;
    node_t *next = (*head)->next;

    free(*head);
    *head = next;

    return data;
}
