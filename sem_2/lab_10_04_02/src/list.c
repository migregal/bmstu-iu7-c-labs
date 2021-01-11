#include <string.h>
#include "../inc/common.h"
#include "../inc/list.h"

#define POP_NODE_END(list)         \
    do                             \
    {                              \
        node_t *temp = list->prev; \
        temp->prev->next = list;   \
        list->prev = temp->prev;   \
                                   \
        free(temp->data);          \
        free(temp);                \
    } while (0)

void cur(iter_t *iterator, node_t **value);

//! List

struct node
{
    void *data;
    size_t size;
    node_t *next, *prev;
};

char list_init(node_t **list)
{
    if (*list)
        return MEM_ALLOC_ERR;

    if (!(*list = malloc(sizeof(node_t))))
        return MEM_ALLOC_ERR;

    (*list)->data = NULL;
    (*list)->size = 0;
    (*list)->next = *list;
    (*list)->prev = *list;

    return OK;
}

char is_empty(node_t *list)
{
    return list->next == list;
}

char push(node_t *list, void *value, size_t size)
{
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

    list->next->prev = temp;
    temp->next = list->next;
    temp->prev = list;
    list->next = temp;

    return OK;
}

char pop_back(node_t *list, void **value)
{
    if (!list)
        return UNINITIALIZED_PTR_ERR;

    if (list == list->prev)
        return MEM_ACCESS_ERR;

    *value = list->prev->data;

    POP_NODE_END(list);

    return OK;
}

void free_list(node_t **list)
{
    while ((*list)->prev != (*list))
        POP_NODE_END((*list));

    free((*list)->data);
    free((*list));
}

char each_elem(node_t *list, change change)
{
    if (!(list->next))
        return OK;

    iter_t *i = NULL;

    if (iter_init(&i, list))
        return MEM_ALLOC_ERR;

    prev(i);

    node_t *t = NULL;
    while (!(begin(i)))
    {
        cur(i, &t);
        change(t->data);
        prev(i);
    }
    t = NULL;

    free_iter(&i);

    return OK;
}

char merge_lists(node_t *a, node_t *b, node_t *r, compare cmp, sum sum)
{
    iter_t *i_a = NULL, *i_b = NULL;

    if (iter_init(&i_a, a) || iter_init(&i_b, b))
        return MEM_ALLOC_ERR;

    prev(i_a), prev(i_b);

    node_t *x = NULL,
           *y = NULL;

    while (!(begin(i_a)) && !(begin(i_b)))
    {
        cur(i_a, &x), cur(i_b, &y);

        if (0 == cmp(x->data, y->data))
        {
            size_t size = 0;
            void *t = NULL;

            sum(x->data, y->data, &t, &size);
            push(r, t, size);

            prev(i_a), cur(i_a, &x);
            prev(i_b), cur(i_b, &y);

            free(t);

            continue;
        }

        if (0 > cmp(x->data, y->data))
        {
            push(r, x->data, x->size);
            prev(i_a);
            cur(i_a, &x);
            continue;
        }

        if (0 < cmp(x->data, y->data))
        {
            push(r, y->data, y->size);
            prev(i_b);
            cur(i_b, &y);
            continue;
        }
    }

    while (!(begin(i_a)))
    {
        cur(i_a, &x);
        push(r, x->data, x->size);
        prev(i_a);
    }

    while (!(begin(i_b)))
    {
        cur(i_b, &y);
        push(r, y->data, y->size);
        prev(i_b);
    }

    x = (y = NULL);
    free_iter(&i_b);
    free_iter(&i_a);

    return OK;
}

char exclude_lists(node_t *a, node_t *b, node_t *r, compare cmp, diff diff)
{
    LOG_DEBUG("%s", "Excluding lists");

    iter_t *i_a = NULL, *i_b = NULL;

    if (iter_init(&i_a, a) || iter_init(&i_b, b))
        return MEM_ALLOC_ERR;

    prev(i_a), prev(i_b);

    node_t *x = NULL,
           *y = NULL;

    while (!(begin(i_a)) && !(begin(i_b)))
    {
        cur(i_a, &x), cur(i_b, &y);

        if (0 == cmp(x->data, y->data))
        {
            LOG_DEBUG("%s", "Found same elems");
            size_t size = 0;
            void *t = NULL;
            if (!diff(x->data, y->data, &t, &size))
            {
                LOG_DEBUG("%s", "Their difference isn't empty");
                push(r, t, size);
            }

            prev(i_a), cur(i_a, &x);
            prev(i_b), cur(i_b, &y);

            free(t);

            continue;
        }

        if (0 > cmp(x->data, y->data))
        {
            LOG_DEBUG("%s", "Passing first list elem to result");
            push(r, x->data, x->size);
            prev(i_a);
            cur(i_a, &x);
            continue;
        }

        if (0 < cmp(x->data, y->data))
        {
            LOG_DEBUG("%s", "Passing second list elem to result");
            size_t size = 0;
            void *t;

            diff(NULL, y->data, &t, &size);
            push(r, t, size);

            prev(i_b), cur(i_b, &y);

            free(t);

            continue;
        }
    }

    while (!(begin(i_a)))
    {
        cur(i_a, &x);
        push(r, x->data, x->size);
        prev(i_a);
    }

    while (!(begin(i_b)))
    {
        cur(i_b, &y);

        size_t size = 0;
        void *t;

        diff(NULL, y->data, &t, &size);
        push(r, t, size);

        prev(i_b);

        free(t);
    }

    x = (y = NULL);
    free_iter(&i_b);
    free_iter(&i_a);

    return OK;
}

//! Iterator

struct iter
{
    node_t *list;
    node_t *cur;
};

char iter_init(iter_t **iterator, node_t *list)
{
    if (*iterator)
        return MEM_ALLOC_ERR;

    if (!list)
        return MEM_ACCESS_ERR;

    if (!((*iterator) = malloc(sizeof(iter_t))))
        return MEM_ALLOC_ERR;

    (*iterator)->list = list;
    (*iterator)->cur = list;

    return OK;
}

void cur(iter_t *iterator, node_t **value)
{
    *value = (void *)(iterator->cur);
}

char cur_data(iter_t *iterator, void **value)
{
    *value = iterator->cur->data;
    return OK;
}

char next(iter_t *iterator)
{
    iterator->cur = iterator->cur->next;

    return OK;
}

char prev(iter_t *iterator)
{
    iterator->cur = iterator->cur->prev;

    return OK;
}

char begin(iter_t *iterator)
{
    return iterator->cur == iterator->list;
}

char end(iter_t *iterator)
{
    return iterator->cur == iterator->list;
}

void free_iter(iter_t **iterator)
{
    (*iterator)->cur = NULL;
    (*iterator)->list = NULL;

    free((*iterator));
    (*iterator) = NULL;
}

#undef POP_NODE_END
