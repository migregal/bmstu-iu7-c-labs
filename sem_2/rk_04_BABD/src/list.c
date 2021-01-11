#include <string.h>
#include "defines.h"
#include "list.h"

struct node
{
    void *data;
    size_t size;
    node_t *next;
};

char push_back(node_t **head, void *value, size_t size)
{
    if (!head)
        return MEM_ACCESS_ERR;

    node_t *temp = malloc(sizeof(node_t));

    if (!temp)
        return MEM_ALLOC_ERR;

    if (!(temp->data = malloc(size)))
    {
        free(temp);
        return MEM_ALLOC_ERR;
    }

    memcpy(temp->data, value, size);
    temp->size = size;

    if (!*head)
    {
        *head = temp;
        return OK;
    }

    node_t *t = *head;

    while (t->next)
        t = t->next;

    t->next = temp;

    return OK;
}

void reverse(node_t **head)
{
    if (!head || !*head)
        return;

    node_t *cur = *head, *next = NULL, *prev = NULL;
    while (cur)
    {
        next = cur->next;
        cur->next = prev;

        prev = cur;
        cur = next;
    }
    *head = prev;
}

void print_list(node_t *head, FILE *fout, void (*print)(FILE *, void *), char endl)
{
    node_t *t = head;

    while (t)
    {
        if (t->data)
            print(fout, t->data);

        t = t->next;
    }

    fprintf(fout, "%c", endl);
}

void free_list(node_t **head, void(free_data)(void *))
{
    if (!head || !*head)
        return;

    while ((*head))
    {
        node_t *t = *head;
        *head = (*head)->next;

        free_data(t->data);
        free(t);
    }
}

#undef POP_NODE_END
