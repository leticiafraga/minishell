#include "../include/shell.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_dollar, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "echo $PATH";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("/usr/bin\n");
}

Test(handle_dollar, no_variable, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "echo $aa";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("\n");
}
