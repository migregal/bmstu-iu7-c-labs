#include "check_algorythm.h"

#include "common.h"
#include "film.h"
#include "algorythm.h"

START_TEST(test_read_from_not_existing_file)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/neg_00_in.txt", 0);

    clear(&films);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(test_read_from_empty_file)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/neg_data_01.txt", 0);

    clear(&films);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(test_read_from_incorrect_file)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/neg_data_07.txt", 0);

    clear(&films);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(test_read_with_incorrect_flag)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/pos_data_01.txt", 0);

    clear(&films);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(test_read_from_correct_file_year)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/pos_data_01.txt", YEAR_SORT_FLAG);

    clear(&films);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_read_from_correct_file_title)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/pos_data_01.txt", TITLE_SORT_FLAG);

    clear(&films);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_read_from_correct_file_name)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = read_file(&films, "./func_tests/shared/pos_data_01.txt", NAME_SORT_FLAG);

    clear(&films);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_run_command_no_search_flag)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        YEAR_SORT_FLAG,
        NO_SEARCH_FLAG,
        NULL,
        NULL);

    clear(&films);

    ck_assert_int_eq(rc, ARRAY_SORTED);
}
END_TEST

START_TEST(test_run_command_title_search_flag)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};
    film *temp;

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        TITLE_SORT_FLAG,
        SEARCH_FLAG,
        "Whiplash",
        &(temp));

    clear(&films);

    ck_assert_int_eq(rc, FILM_FOUND);
}
END_TEST

START_TEST(test_run_command_title_not_found_search)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};
    film *temp;

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        TITLE_SORT_FLAG,
        SEARCH_FLAG,
        "Vas`ka",
        &(temp));

    clear(&films);

    ck_assert_int_eq(rc, FILM_NOT_FOUND);
}
END_TEST

START_TEST(test_run_command_name_search_flag)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};
    film *temp;

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        NAME_SORT_FLAG,
        SEARCH_FLAG,
        "Robert Zemeckis",
        &(temp));

    clear(&films);

    ck_assert_int_eq(rc, FILM_FOUND);
}
END_TEST

START_TEST(test_run_command_name_not_found_search)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};
    film *temp;

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        NAME_SORT_FLAG,
        SEARCH_FLAG,
        "Pupkin",
        &(temp));

    clear(&films);

    ck_assert_int_eq(rc, FILM_NOT_FOUND);
}
END_TEST

START_TEST(test_run_command_year_search_flag)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};
    film *temp;

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        YEAR_SORT_FLAG,
        SEARCH_FLAG,
        "2014",
        &(temp));

    clear(&films);

    ck_assert_int_eq(rc, FILM_FOUND);
}
END_TEST

START_TEST(test_run_command_year_not_found_search)
{
    films_vec films = {.arr = NULL, .len = 0, .cap = 0};
    film *temp;

    int rc = run_command(
        &films,
        "./func_tests/shared/pos_data_02.txt",
        YEAR_SORT_FLAG,
        SEARCH_FLAG,
        "2015",
        &(temp));

    clear(&films);

    ck_assert_int_eq(rc, FILM_NOT_FOUND);
}
END_TEST

Suite *algorythm_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("list");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_from_not_existing_file);
    tcase_add_test(tc_neg, test_read_from_empty_file);
    tcase_add_test(tc_neg, test_read_from_incorrect_file);
    tcase_add_test(tc_neg, test_read_with_incorrect_flag);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_read_from_correct_file_year);
    tcase_add_test(tc_pos, test_read_from_correct_file_title);
    tcase_add_test(tc_pos, test_read_from_correct_file_name);
    tcase_add_test(tc_pos, test_run_command_no_search_flag);
    tcase_add_test(tc_pos, test_run_command_title_search_flag);
    tcase_add_test(tc_pos, test_run_command_title_not_found_search);
    tcase_add_test(tc_pos, test_run_command_name_search_flag);
    tcase_add_test(tc_pos, test_run_command_name_not_found_search);
    tcase_add_test(tc_pos, test_run_command_year_search_flag);
    tcase_add_test(tc_pos, test_run_command_year_not_found_search);
    suite_add_tcase(s, tc_pos);

    return s;
}
