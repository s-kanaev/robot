#include "containers.h"
#include <check.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int nfailed = 0;

    Suite *s;
    SRunner *runner;

    s = containers_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    nfailed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return nfailed ? EXIT_FAILURE : EXIT_SUCCESS;
}