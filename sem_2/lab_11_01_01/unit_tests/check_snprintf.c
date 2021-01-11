#include <stdio.h>
#include <limits.h>

#include "check_snprintf.h"

#define OK 0
#define FAIL 1

int snprintf_cmp(const int lib_out, const int my_out, char *lib_str, char *my_str)
{
    if (lib_out != my_out || strcmp(lib_str, my_str))
        return FAIL;

    return OK;
}

START_TEST(s_spec)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 5, "%s", "room");
    int my_res = my_snprintf(my_buf, 5, "%s", "room");

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(c_spec)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%c", 'c');
    int my_res = my_snprintf(my_buf, 100, "%c", 'c');

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(x_spec)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%x", 256);
    int my_res = my_snprintf(my_buf, 100, "%x", 256);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(lx_spec)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%lx", ULONG_MAX);
    int my_res = my_snprintf(my_buf, 100, "%lx", ULONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(llx_spec)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 100, "%llx", ULLONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(null_buf)
{
    int lib_res = snprintf(NULL, 0, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(NULL, 0, "%llx", ULLONG_MAX);

    ck_assert_int_eq(my_res, lib_res);
}
END_TEST

START_TEST(zero_size)
{
    char lib_buf[BUFSIZE] = {0};
    char my_buf[BUFSIZE] = {0};
    int lib_res = snprintf(lib_buf, 0, "flex %llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 0, "flex %llx", ULLONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(size_only)
{
    char lib_buf[BUFSIZE] = {0};
    char my_buf[BUFSIZE] = {0};
    int lib_res = snprintf(lib_buf, 1, "flex %llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 1, "flex %llx", ULLONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(empty_fmt)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 10, "", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 10, "", ULLONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(buf_overflow)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 5, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 5, "%llx", ULLONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

START_TEST(usual_way)
{
    char lib_buf[BUFSIZE];
    char my_buf[BUFSIZE];
    int lib_res = snprintf(lib_buf, 100, "%llx", ULLONG_MAX);
    int my_res = my_snprintf(my_buf, 100, "%llx", ULLONG_MAX);

    ck_assert_int_eq(snprintf_cmp(lib_res, my_res, lib_buf, my_buf), 0);
}
END_TEST

Suite *snprintf_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("my_snprintf");

    tc = tcase_create("workcases");
    tcase_add_test(tc, s_spec);
    tcase_add_test(tc, c_spec);
    tcase_add_test(tc, x_spec);
    tcase_add_test(tc, lx_spec);
    tcase_add_test(tc, llx_spec);
    tcase_add_test(tc, null_buf);
    tcase_add_test(tc, zero_size);
    tcase_add_test(tc, size_only);
    tcase_add_test(tc, empty_fmt);
    tcase_add_test(tc, buf_overflow);
    tcase_add_test(tc, usual_way);
    suite_add_tcase(s, tc);

    return s;
}
