#include "check_list.h"
#include "list.h"
#include "process.h"

START_TEST(decompose_0)
{
    node_t *list = NULL;
    int rc = decompose_into_simple(&list, 0);
    if (!rc)
        free_list(&list);
    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(decompose_1)
{
    node_t *list = NULL;
    int rc = decompose_into_simple(&list, 1);
    free_list(&list);
    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(decompose_20)
{
    node_t *list = NULL;
    int rc = decompose_into_simple(&list, 20);
    free_list(&list);
    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(sqr_1)
{
    node_t *list_a = NULL;

    decompose_into_simple(&list_a, 1);

    int rc = each_elem(list_a, sqr_elem);

    free_list(&list_a);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(sqr_20)
{
    node_t *list_a = NULL;

    decompose_into_simple(&list_a, 1);

    int rc = each_elem(list_a, sqr_elem);

    free_list(&list_a);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(merging_1_1)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 1);
    decompose_into_simple(&list_b, 1);
    list_init(&list_r);

    int rc = merge_lists(list_a, list_b, list_r, cmp, summary);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(merging_24_24)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 24);
    decompose_into_simple(&list_b, 24);
    list_init(&list_r);

    int rc = merge_lists(list_a, list_b, list_r, cmp, summary);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(merging_14_49)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 14);
    decompose_into_simple(&list_b, 49);
    list_init(&list_r);

    int rc = merge_lists(list_a, list_b, list_r, cmp, summary);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(merging_49_14)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 49);
    decompose_into_simple(&list_b, 14);
    list_init(&list_r);

    int rc = merge_lists(list_a, list_b, list_r, cmp, summary);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(excluding_1_1)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 1);
    decompose_into_simple(&list_b, 1);
    list_init(&list_r);

    int rc = exclude_lists(list_a, list_b, list_r, cmp, difference);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(excluding_24_24)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 24);
    decompose_into_simple(&list_b, 24);
    list_init(&list_r);

    int rc = exclude_lists(list_a, list_b, list_r, cmp, difference);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(excluding_14_49)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 14);
    decompose_into_simple(&list_b, 49);
    list_init(&list_r);

    int rc = exclude_lists(list_a, list_b, list_r, cmp, difference);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(excluding_49_14)
{
    node_t *list_a = NULL, *list_b = NULL;
    node_t *list_r = NULL;

    decompose_into_simple(&list_a, 49);
    decompose_into_simple(&list_b, 14);
    list_init(&list_r);

    int rc = exclude_lists(list_a, list_b, list_r, cmp, difference);

    free_list(&list_b);
    free_list(&list_a);
    free_list(&list_r);

    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *list_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("list");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, decompose_0);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, decompose_1);
    tcase_add_test(tc_pos, decompose_20);
    tcase_add_test(tc_pos, sqr_1);
    tcase_add_test(tc_pos, sqr_20);
    tcase_add_test(tc_pos, merging_1_1);
    tcase_add_test(tc_pos, merging_24_24);
    tcase_add_test(tc_pos, merging_14_49);
    tcase_add_test(tc_pos, merging_49_14);
    tcase_add_test(tc_pos, excluding_1_1);
    tcase_add_test(tc_pos, excluding_24_24);
    tcase_add_test(tc_pos, excluding_14_49);
    tcase_add_test(tc_pos, excluding_49_14);

    suite_add_tcase(s, tc_pos);

    return s;
}
