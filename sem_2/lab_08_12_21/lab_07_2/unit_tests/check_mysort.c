#include <time.h>
#include <stdlib.h>

#include "../inc/macrologger.h"

#include "check_mysort.h"

#define NEW_VECTOR(vec, size)                       \
do                                                  \
{                                                   \
    if (new_vector(&vec, size))                     \
        ck_abort_msg("Memory allocation error");    \
} while (0)

#define COPY_VECTOR(dst, src)                                         \
    do                                                                \
    {                                                                 \
        memcpy(dst->arr, src->arr,                                    \
                src->len > dst->capacity ? dst->capacity : src->len); \
        dst->len = src->len;                                          \
    } while (0)

#define READ_EMPTY_FILE(filename, vec)      \
do                                          \
{                                           \
    if (!read_file(filename, vec))          \
    {                                       \
        delete_vector(&vec);                \
        ck_abort_msg("File reading err");   \
    }                                       \
} while (0)

#define READ_FILE(filename, vec)            \
do                                          \
{                                           \
    if (read_file(filename, vec))           \
    {                                       \
        delete_vector(&vec);                \
        ck_abort_msg("File reading err");   \
    }                                       \
} while (0)

#define CHECK_VEC_EQUALS(vec_1, vec_2)                                                           \
    do                                                                                           \
    {                                                                                            \
        if (len(vec_1) != len(vec_2))                                                            \
        {                                                                                        \
            ck_abort_msg("Vectors aren't equal\n");                                              \
            break;                                                                               \
        }                                                                                        \
                                                                                                 \
        if (sizeof(*(vec_1->begin(vec_1))) != sizeof(*(vec_2->begin(vec_2))))                    \
        {                                                                                        \
            ck_abort_msg("Vectors aren't equal\n");                                              \
            break;                                                                               \
        }                                                                                        \
                                                                                                 \
        ck_assert_mem_eq(vec_1->arr, vec_2->arr, vec_2->len * sizeof(*(vec_2->begin(vec_2))));   \
    } while (0)

START_TEST(test_empty_file_sort)
{
    vector *vec_a = NULL;

    NEW_VECTOR(vec_a, 0);
    size_t num = len(vec_a);

    READ_EMPTY_FILE("./func_tests/neg_04_in.txt", vec_a);

    sort(vec_a, false);
    delete_vector(&vec_a);

    ck_assert_int_eq(num, 0);
}
END_TEST

START_TEST(test_sort)
{
    vector *vec_a = NULL, *vec_b = NULL;
    NEW_VECTOR(vec_a, 0);

    READ_FILE("./func_tests/pos_02_in.txt", vec_a);

    NEW_VECTOR(vec_b, len(vec_a));
    COPY_VECTOR(vec_a, vec_b);

    sort(vec_a, false);
    qsort((void *)vec_b->begin(vec_b), len(vec_b), sizeof(int), compare_vec_elems);

    CHECK_VEC_EQUALS(vec_a, vec_b);

    delete_vector(&vec_a);
    delete_vector(&vec_b);
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_empty_file_sort);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort);
    tcase_set_timeout(tc_pos, 60);

    suite_add_tcase(s, tc_pos);

    return s;
}

#undef CHECK_VEC_EQUALS
#undef READ_FILE
#undef READ_EMPTY_FILE
#undef COPY_VECTOR
#undef NEW_VECTOR
