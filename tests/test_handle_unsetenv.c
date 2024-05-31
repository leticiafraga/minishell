#include "../include/shell.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_unsetenv_test, few_args, .init=cr_redirect_stderr)
{
    char *args[2];
    global_state_t *state = create_state();

    args[0] = "unsetenv";
    args[1] = 0;

    int res = handle_unsetenv(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
    free_state(state);
}

Test(handle_unsetenv_test, unsetenv, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    add_item("leticia", "aa", state->env);

    args[0] = "unsetenv";
    args[1] = "leticia";
    args[2] = 0;

    int res = handle_unsetenv(args, state);
    cr_assert_eq(res, 0);
    res = handle_unsetenv(args, state);
    cr_assert_eq(res, 0);
    free_state(state);
}