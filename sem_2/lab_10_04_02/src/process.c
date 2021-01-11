#include <math.h>

#include "../inc/process.h"

#define on_decompose_err(__list__, __num__, __rc__) \
    if ((__rc__ = decompose_into_simple(__list__, __num__)))

int process(FILE *fin)
{
    char rc = WRONG_CMD;

    LOG_DEBUG("%s", "Reading command");

    char cmd[4];
    char c = '\n';

    if (2 != scanf("%3s%c", cmd, &c) || '\n' != c)
    {
        LOG_ERROR("Wrong command");
        return WRONG_CMD;
    }

    if (!strcmp(cmd, "out"))
    {
        type_t a = 0;

        if (2 != scanf(ELEM_FMT "%c", &a, &c) || '\n' != c)
        {
            LOG_ERROR("Input error");
            return INPUT_ERR;
        }

        if (0 >= a)
        {
            LOG_ERROR("Value error [" ELEM_FMT "]", a);
            return ELEM_VAL_ERR;
        }

        rc = out(a);
    }

    if (!strcmp(cmd, "mul"))
    {
        type_t a = 0, b = 0;

        if (3 != scanf(ELEM_FMT " " ELEM_FMT "%c", &a, &b, &c) || '\n' != c)
        {
            LOG_ERROR("Input error");
            return INPUT_ERR;
        }

        if (0 >= a || 0 >= b)
        {
            LOG_ERROR("Values error [" ELEM_FMT ";" ELEM_FMT "]", a, b);
            return ELEM_VAL_ERR;
        }

        rc = mul(a, b);
    }

    if (!strcmp(cmd, "div"))
    {
        type_t a = 0, b = 0;

        if (3 != scanf(ELEM_FMT " " ELEM_FMT "%c", &a, &b, &c) || '\n' != c)
        {
            LOG_ERROR("Input error");
            return INPUT_ERR;
        }

        if (0 >= a || 0 >= b)
        {
            LOG_ERROR("Values error [" ELEM_FMT ";" ELEM_FMT "]", a, b);
            return ELEM_VAL_ERR;
        }

        rc = division(a, b);
    }

    if (!strcmp(cmd, "sqr"))
    {
        type_t a = 0;

        if (2 != scanf(ELEM_FMT "%c", &a, &c) || '\n' != c)
        {
            LOG_ERROR("Input error");
            return INPUT_ERR;
        }

        if (0 >= a)
        {
            LOG_ERROR("Value error [" ELEM_FMT "]", a);
            return ELEM_VAL_ERR;
        }

        rc = sqr(a);
    }

    return rc;
}

//! Functions

char decompose_into_simple(node_t **list, type_t num)
{
    LOG_DEBUG("%s", "Decomposing number to miltipliers");

    if (0 == num)
        return ELEM_VAL_ERR;

    char rc = OK;
    if ((rc = list_init(list)))
    {
        LOG_ERROR("%s", "List initialization error");
        return rc;
    }

    type_t div = 2;

    while (num > 1)
    {
        long long count = 0;

        while (num % div == 0)
            num /= div, ++count;

        div++;

        if (!count)
            continue;

        multiplier_t temp = {.num = div - 1, .count = count};

        if (!(rc = push(*list, (void *)&temp, sizeof(multiplier_t))))
        {
            LOG_DEBUG("New multiplier " ELEM_FMT " (%lld)", div - 1, count);
            continue;
        }

        LOG_ERROR("%s", "Error occured on push");
        free_list(list);
        return rc;
    }
    LOG_DEBUG("%s", "Decomposing finished");

    return rc;
}

char list_to_num(node_t *list, type_t *res)
{
    LOG_DEBUG("%s", "Converting list to num");

    iter_t *it = NULL;

    if (iter_init(&it, list))
    {
        LOG_ERROR("%s", "Iter initialization err");
        return MEM_ALLOC_ERR;
    }
    prev(it);

    double r = 1;
    while (!begin(it))
    {
        multiplier_t *temp;
        cur_data(it, (void **)&temp);

        long long n = temp->count;
        while (0 != n)
        {
            if (0 > n)
            {
                r /= temp->num;
                n += 1;
            }
            if (0 < n)
            {
                r *= temp->num;
                n -= 1;
            }
        }
        prev(it);
    }

    free_iter(&it);

    *res = (type_t)floor(r);
    LOG_DEBUG("%s", "List converted");

    return OK;
}

char print_list(node_t *list)
{
    char rc = OK;

    iter_t *i = NULL;
    if ((rc = iter_init(&i, list)))
        return rc;

    next(i);

    multiplier_t *m = NULL;
    while (!(end(i)))
    {
        cur_data(i, (void **)&m);
        printf(ELEM_FMT " %lld ",
               m->num,
               m->count);
        next(i);
    }
    m = NULL;
    printf("1\n");
    free_iter(&i);

    return rc;
}

char out(type_t num)
{
    char rc = OK;

    node_t *list = NULL;

    on_decompose_err(&list, num, rc)
    {
        LOG_ERROR("Decomposing error");
        return rc;
    }

    print_list(list);

    free_list(&list);

    return rc;
}

char sqr(type_t num)
{
    char rc = OK;

    node_t *list = NULL;

    on_decompose_err(&list, num, rc)
    {
        LOG_ERROR("Decomposing error");
        return rc;
    }

    LOG_DEBUG("%s", "Powering num");
    each_elem(list, sqr_elem);
    LOG_DEBUG("%s", "Powered");

    print_list(list);

    free_list(&list);

    return rc;
}

char division(type_t a, type_t b)
{
    if (0 == b)
        return DIVISION_BY_ZERO_ERR;

    char rc = OK;

    node_t *list_a = NULL,
           *list_b = NULL,
           *list_r = NULL;

    on_decompose_err(&list_a, a, rc)
    {
        LOG_ERROR("Decomposing error");
        return rc;
    }

    on_decompose_err(&list_b, b, rc)
    {
        LOG_ERROR("Decomposing error");
        free_list(&list_a);
        return rc;
    }

    LOG_DEBUG("%s", "Result list init");
    if ((rc = list_init(&list_r)))
    {
        LOG_ERROR("%s", "Result list allocation error");
        free_list(&list_b);
        free_list(&list_a);
        return rc;
    }

    LOG_DEBUG("%s", "Excluding lists");
    rc = exclude_lists(list_a, list_b, list_r, cmp, difference);

    free_list(&list_b);
    free_list(&list_a);

    if (rc)
    {
        LOG_ERROR("%s", "Excluding lists error");
        free_list(&list_r);
        return rc;
    }

    type_t res = 0;
    list_to_num(list_r, &res);
    free_list(&list_r), list_r = NULL;

    if (!res)
    {
        LOG_ERROR("%s", "Incorrect division result");
        return ELEM_VAL_ERR;
    }

    on_decompose_err(&list_r, res, rc)
    {
        LOG_ERROR("Decomposing error");
        return rc;
    }

    print_list(list_r);

    free_list(&list_r);

    return rc;
}

char mul(type_t a, type_t b)
{
    char rc = OK;

    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    on_decompose_err(&list_a, a, rc)
    {
        LOG_ERROR("Decomposing error");
        return rc;
    }

    on_decompose_err(&list_b, b, rc)
    {
        LOG_ERROR("Decomposing error");
        free_list(&list_a);
        return rc;
    }

    list_init(&list_r);

    LOG_DEBUG("%s", "Merging lists");
    rc = merge_lists(list_a, list_b, list_r, cmp, summary);

    free_list(&list_b);
    free_list(&list_a);

    if (rc)
        LOG_ERROR("%s", "Merging error");
    else
        print_list(list_r);

    free_list(&list_r);

    return rc;
}

int cmp(void *x, void *y)
{
    multiplier_t *x1 = (multiplier_t *)x;
    multiplier_t *y1 = (multiplier_t *)y;

    if (x1->num > y1->num)
        return 1;

    if (x1->num < y1->num)
        return -1;

    return 0;
}

int summary(void *x, void *y, void **r, size_t *new_size)
{
    if (!(*r = malloc(sizeof(multiplier_t))))
        return MEM_ALLOC_ERR;

    *new_size = sizeof(multiplier_t);

    ((multiplier_t *)(*r))->count = ((multiplier_t *)x)->count + ((multiplier_t *)y)->count;
    ((multiplier_t *)(*r))->num = ((multiplier_t *)x)->num;

    return OK;
}

int difference(void *x, void *y, void **r, size_t *new_size)
{
    if (!(*r = malloc(sizeof(multiplier_t))))
        return MEM_ALLOC_ERR;

    *new_size = sizeof(multiplier_t);

    ((multiplier_t *)(*r))->count = 0;

    if (x)
        ((multiplier_t *)(*r))->count = ((multiplier_t *)x)->count;

    ((multiplier_t *)(*r))->count -= ((multiplier_t *)y)->count;

    ((multiplier_t *)(*r))->num = ((multiplier_t *)y)->num;

    return ((multiplier_t *)(*r))->count != 0 ? OK : 1;
}

int sqr_elem(void *x)
{
    ((multiplier_t *)x)->count *= 2;
    return OK;
}

#undef print_list
#undef on_decompose_err
