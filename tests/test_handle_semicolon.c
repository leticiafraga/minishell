#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_semicolon_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls run_prog.c;cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\nhola\n");
    free_state(state);
}

Test(handle_semicolon_test, more_complex_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls run_prog.c; cat tests/cattest | wc -w";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n1\n");
    free_state(state);
}