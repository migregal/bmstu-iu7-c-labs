#include "check_list.h"
#include "list.h"
#include "film.h"

int cmp(const void *a, const void *b)
{
    if (*(size_t *)a > *(size_t *)b)
        return 1;

    if (*(size_t *)a < *(size_t *)b)
        return -1;

    return 0;
}

START_TEST(insertion)
{
    node_t *list = NULL;

    node_t *node = NULL;
    size_t temp = 0;
    create_node(&node, &temp, sizeof(size_t));
    insert(&list, node, NULL);
    void *r = pop_front(&list);

    int rc = *(size_t *)r != temp;
    free_list(&list);

    free(r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(sorted_insertion)
{
    node_t *list = NULL;

    node_t *node = NULL;
    size_t temp = 0;
    create_node(&node, &temp, sizeof(size_t));
    sorted_insert(&list, node, cmp);
    void *r = pop_front(&list);

    int rc = *(size_t *)r != temp;
    free_list(&list);

    free(r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(searching)
{
    node_t *list = NULL;

    node_t *node = NULL;
    size_t temp = 0;
    create_node(&node, &temp, sizeof(size_t));
    sorted_insert(&list, node, cmp);

    node_t *r = find(list, &temp, cmp);

    int rc = memcmp(r, node, sizeof(node_t));
    free_list(&list);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(duplication)
{
    node_t *list = NULL;

    node_t *node = NULL;
    size_t temp = 0;
    create_node(&node, &temp, sizeof(size_t));
    sorted_insert(&list, node, cmp);

    node_t *node2 = NULL;
    create_node(&node2, &temp, sizeof(size_t));
    sorted_insert(&list, node2, cmp);

    remove_duplicates(&list, cmp);
    void *r = pop_front(&list);
    free(r);

    r = pop_front(&list);

    int rc = r != NULL;
    free_list(&list);

    free(r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(sorting)
{
    node_t *list = NULL;

    node_t *node = NULL;
    size_t temp = 10;
    create_node(&node, &temp, sizeof(size_t));
    insert(&list, node, NULL);

    node_t *node2 = NULL;
    temp = 0;
    create_node(&node2, &temp, sizeof(size_t));
    insert(&list, node2, NULL);

    list = sort(list, cmp);
    void *r = pop_front(&list);

    int rc = *(size_t *)r != temp;
    free_list(&list);

    free(r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(neg_insertion)
{
    node_t *list = NULL;

    insert(&list, NULL, NULL);
    void *r = pop_front(&list);

    int rc = r != NULL;
    free_list(&list);

    free(r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(neg_sorted_insertion)
{
    node_t *list = NULL;

    sorted_insert(&list, NULL, cmp);
    void *r = pop_front(&list);

    int rc = r != NULL;
    free_list(&list);

    free(r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *list_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("list");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, insertion);
    tcase_add_test(tc_pos, sorted_insertion);
    tcase_add_test(tc_pos, searching);
    tcase_add_test(tc_pos, duplication);
    tcase_add_test(tc_pos, sorting);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, neg_insertion);
    tcase_add_test(tc_neg, neg_sorted_insertion);

    suite_add_tcase(s, tc_neg);

    return s;
}
