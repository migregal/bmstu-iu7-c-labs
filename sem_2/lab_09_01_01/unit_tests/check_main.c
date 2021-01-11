#include "check_algorythm.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_list;
    SRunner *runner;

    s_list = algorythm_suite();

    runner = srunner_create(s_list);
    // srunner_add_suite(runner, s_mysort);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
