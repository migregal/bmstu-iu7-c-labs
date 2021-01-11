#include "check_vector.h"

#define NEW_VECTOR(vec, size)                        \
    do                                               \
    {                                                \
        if (new_vector(&vec, size))                  \
            ck_abort_msg("Memory allocation error"); \
    } while (0)

START_TEST(test_read_array_from_not_existing_file)
{
    vector *vect = NULL;

    NEW_VECTOR(vect, 0);

    int rc = read_file("./func_tests/neg_04_1_in.txt", vect);

    delete_vector(&vect);

    ck_assert_int_ne(rc, FILE_OK);
}
END_TEST

START_TEST(test_read_array_from_empty_file)
{
    vector *vect = NULL;

    NEW_VECTOR(vect, 0);

    int rc = read_file("./func_tests/neg_04_in.txt", vect);

    delete_vector(&vect);

    ck_assert_int_ne(rc, FILE_OK);
}
END_TEST

START_TEST(test_read_array_from_incorrect_file)
{
    vector *vect = NULL;

    NEW_VECTOR(vect, 0);

    int rc = read_file("./func_tests/neg_06_in.txt", vect);

    delete_vector(&vect);

    ck_assert_int_ne(rc, FILE_OK);
}
END_TEST

START_TEST(test_read_array_from_float_num_file)
{
    vector *vect = NULL;

    NEW_VECTOR(vect, 0);

    int rc = read_file("./func_tests/neg_07_in.txt", vect);

    delete_vector(&vect);

    ck_assert_int_ne(rc, FILE_OK);
}
END_TEST

START_TEST(test_read_array_from_damaged_file)
{
    vector *vect = NULL;

    NEW_VECTOR(vect, 0);

    int rc = read_file("./func_tests/neg_08_in.txt", vect);

    delete_vector(&vect);

    ck_assert_int_ne(rc, FILE_OK);
}
END_TEST

START_TEST(test_read_array_from_file)
{
    vector *vect = NULL;

    NEW_VECTOR(vect, 0);

    int rc = read_file("./func_tests/pos_02_in.txt", vect);

    delete_vector(&vect);

    ck_assert_int_eq(rc, FILE_OK);
}
END_TEST

Suite *vector_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("array");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_array_from_not_existing_file);
    tcase_add_test(tc_neg, test_read_array_from_empty_file);
    tcase_add_test(tc_neg, test_read_array_from_incorrect_file);
    tcase_add_test(tc_neg, test_read_array_from_float_num_file);
    tcase_add_test(tc_neg, test_read_array_from_damaged_file);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_read_array_from_file);

    suite_add_tcase(s, tc_pos);

    return s;
}
