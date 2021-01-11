#include "../inc/check_matrix.h"

#define NEW_MATRIX(__matrix__, __rows__, __cols__)          \
    do                                                      \
    {                                                       \
        free(__matrix__.data);                              \
        __matrix__.data = NULL;                             \
        __matrix__.rows = 0;                                \
        __matrix__.cols = 0;                                \
                                                            \
        if (create_matrix(&__matrix__, __rows__, __cols__)) \
            ck_abort_msg("Memory allocation error");        \
    } while (0)

#define DETERMINANT_1x1 1

#define MATRIX_A_1x1(__matrix__)                 \
    do                                           \
    {                                            \
        NEW_MATRIX(__matrix__, 1, 1);            \
        __matrix__.data[0][0] = DETERMINANT_1x1; \
    } while (0)

#define DETERMINANT_2x2 1

#define MATRIX_A_2x2(__matrix__)                 \
    do                                           \
    {                                            \
        NEW_MATRIX(__matrix__, 2, 2);            \
        __matrix__.data[0][0] = DETERMINANT_2x2; \
        __matrix__.data[1][1] = DETERMINANT_2x2; \
    } while (0)

#define DETERMINANT_3x3 0

#define MATRIX_A_3x3(__matrix__)      \
    do                                \
    {                                 \
        NEW_MATRIX(__matrix__, 3, 3); \
        __matrix__.data[0][0] = 1;    \
        __matrix__.data[0][2] = 1;    \
        __matrix__.data[2][0] = 1;    \
        __matrix__.data[2][2] = 1;    \
    } while (0)

#define MATRIX_B_3x3(__matrix__)      \
    do                                \
    {                                 \
        NEW_MATRIX(__matrix__, 3, 3); \
        __matrix__.data[0][1] = 1;    \
        __matrix__.data[1][0] = 1;    \
        __matrix__.data[1][2] = 1;    \
        __matrix__.data[2][1] = 1;    \
    } while (0)

#define MATRIX_A_B_MULTIPLICATION_3x3(__matrix__) \
    do                                            \
    {                                             \
        NEW_MATRIX(__matrix__, 3, 3);             \
        __matrix__.data[0][1] = 2;                \
        __matrix__.data[2][1] = 2;                \
    } while (0)

#define MATRIX_A_B_SUM_3x3(__matrix__) \
    do                                 \
    {                                  \
        NEW_MATRIX(__matrix__, 3, 3);  \
        __matrix__.data[0][0] = 1;     \
        __matrix__.data[0][1] = 1;     \
        __matrix__.data[0][2] = 1;     \
        __matrix__.data[1][0] = 1;     \
        __matrix__.data[1][2] = 1;     \
        __matrix__.data[2][0] = 1;     \
        __matrix__.data[2][1] = 1;     \
        __matrix__.data[2][2] = 1;     \
    } while (0)

#define CHECK_MATRIX_EQUALS(__matrix_1__, __matrix_2__)              \
    do                                                               \
    {                                                                \
        if (__matrix_1__.rows != __matrix_2__.rows)                  \
        {                                                            \
            ck_abort_msg("Different row's count\n");                 \
            break;                                                   \
        }                                                            \
                                                                     \
        if (__matrix_1__.cols != __matrix_2__.cols)                  \
        {                                                            \
            ck_abort_msg("Different row's count\n");                 \
            break;                                                   \
        }                                                            \
                                                                     \
        for (m_size_t __r__ = 0; __r__ < __matrix_1__.rows; ++__r__) \
            ck_assert_mem_eq(                                        \
                __matrix_1__.data[__r__],                            \
                __matrix_2__.data[__r__],                            \
                (__matrix_1__.cols) * sizeof(type_t));               \
    } while (0)

START_TEST(not_existing_file_reading)
{
    matrix_t matrix = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int rc = read_from_file(&matrix, "./func_tests/shared/data_00.txt");

    if (rc == OK)
        delete_matrix(&matrix);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(empty_file_reading)
{
    matrix_t matrix = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int rc = read_from_file(&matrix, "./func_tests/shared/data_01.txt");

    if (rc == OK)
        delete_matrix(&matrix);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(incorrect_matrix_reading)
{
    matrix_t matrix = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int rc = read_from_file(&matrix, "./func_tests/shared/data_02.txt");

    if (rc == OK)
        delete_matrix(&matrix);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(incorrect_elem_reading)
{
    matrix_t matrix = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int rc = read_from_file(&matrix, "./func_tests/shared/data_03.txt");

    if (rc == OK)
        delete_matrix(&matrix);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(incorrect_size_multiplication)
{
    matrix_t matrix_a = {.data = NULL}, matrix_b = {.data = NULL}, matrix_res = {.data = NULL};

    NEW_MATRIX(matrix_a, 3, 3);

    NEW_MATRIX(matrix_b, 2, 2);

    int rc = multiplication(&matrix_a, &matrix_b, &matrix_res);

    delete_matrix(&matrix_b);
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_res);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(incorrect_size_sum)
{
    matrix_t matrix_a = {.data = NULL}, matrix_b = {.data = NULL}, matrix_res = {.data = NULL};

    NEW_MATRIX(matrix_a, 3, 3);

    NEW_MATRIX(matrix_b, 2, 2);

    int rc = sum(&matrix_a, &matrix_b, &matrix_res);

    delete_matrix(&matrix_b);
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_res);

    ck_assert_int_ne(rc, OK);
}
END_TEST

START_TEST(matrix_reading_1_x_1)
{
    matrix_t matrix = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int rc = read_from_file(&matrix, "./func_tests/shared/data_05.txt");

    delete_matrix(&matrix);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(matrix_reading_3_x_3)
{
    matrix_t matrix = {
        .data = NULL,
        .rows = 0,
        .cols = 0};

    int rc = read_from_file(&matrix, "./func_tests/shared/data_10.txt");

    delete_matrix(&matrix);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(correct_multiplication)
{
    matrix_t matrix_a = {.data = NULL};
    matrix_t matrix_b = {.data = NULL};
    matrix_t matrix_res = {.data = NULL};
    matrix_t matrix_res_correct = {.data = NULL};

    MATRIX_A_3x3(matrix_a);

    MATRIX_B_3x3(matrix_b);

    MATRIX_A_B_MULTIPLICATION_3x3(matrix_res_correct);

    int rc = multiplication(&matrix_a, &matrix_b, &matrix_res);

    CHECK_MATRIX_EQUALS(matrix_res_correct, matrix_res);

    delete_matrix(&matrix_b);
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_res);
    delete_matrix(&matrix_res_correct);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(correct_sum)
{
    matrix_t matrix_a = {.data = NULL};
    matrix_t matrix_b = {.data = NULL};
    matrix_t matrix_res = {.data = NULL};
    matrix_t matrix_res_correct = {.data = NULL};

    MATRIX_A_3x3(matrix_a);

    MATRIX_B_3x3(matrix_b);

    MATRIX_A_B_SUM_3x3(matrix_res_correct);

    int rc = sum(&matrix_a, &matrix_b, &matrix_res);

    CHECK_MATRIX_EQUALS(matrix_res_correct, matrix_res);

    delete_matrix(&matrix_b);
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_res);
    delete_matrix(&matrix_res_correct);

    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(correct_determinant_1x1)
{
    matrix_t matrix_a = {.data = NULL};

    MATRIX_A_1x1(matrix_a);

    type_t res = -1;
    int rc = determinant(&matrix_a, &res);

    delete_matrix(&matrix_a);

    ck_assert_int_eq(rc, OK);
    ck_assert_ldouble_eq(res, DETERMINANT_1x1);
}
END_TEST

START_TEST(correct_determinant_2x2)
{
    matrix_t matrix_a = {.data = NULL};

    MATRIX_A_2x2(matrix_a);

    type_t res = -1;
    int rc = determinant(&matrix_a, &res);

    delete_matrix(&matrix_a);

    ck_assert_int_eq(rc, OK);
    ck_assert_ldouble_eq(res, DETERMINANT_2x2);
}
END_TEST

START_TEST(correct_determinant_3x3)
{
    matrix_t matrix_a = {.data = NULL};

    MATRIX_A_3x3(matrix_a);

    type_t res = -1;
    int rc = determinant(&matrix_a, &res);

    delete_matrix(&matrix_a);

    ck_assert_int_eq(rc, OK);
    ck_assert_ldouble_eq(res, DETERMINANT_3x3);
}
END_TEST

Suite *matrix_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, not_existing_file_reading);
    tcase_add_test(tc_neg, empty_file_reading);
    tcase_add_test(tc_neg, incorrect_matrix_reading);
    tcase_add_test(tc_neg, incorrect_elem_reading);
    tcase_add_test(tc_neg, incorrect_size_multiplication);
    tcase_add_test(tc_neg, incorrect_size_sum);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, matrix_reading_1_x_1);
    tcase_add_test(tc_pos, matrix_reading_3_x_3);
    tcase_add_test(tc_pos, correct_multiplication);
    tcase_add_test(tc_pos, correct_sum);
    tcase_add_test(tc_pos, correct_determinant_1x1);
    tcase_add_test(tc_pos, correct_determinant_2x2);
    tcase_add_test(tc_pos, correct_determinant_3x3);

    suite_add_tcase(s, tc_pos);

    return s;
}

#undef CHECK_MATRIX_EQUALS
#undef MATRIX_A_B_SUM_3x3
#undef MATRIX_A_B_MULTIPLICATION_3x3
#undef MATRIX_B_3x3
#undef MATRIX_A_3x3
#undef DETERMINANT_3x3
#undef MATRIX_A_2x2
#undef DETERMINANT_2x2
#undef MATRIX_A_1x1
#undef DETERMINANT_1x1
#undef NEW_MATRIX
