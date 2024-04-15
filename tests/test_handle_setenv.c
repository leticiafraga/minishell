#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_setenv_test, many_args, .init=cr_redirect_stderr)
{
    char *args[5];
   global_state_t *state = create_state();

    args[0] = "setenv";
    args[1] = "leticia";
    args[2] = "aa";
    args[3] = "bb";
    args[4] = 0;

    int res = handle_setenv(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
    free_state(state);
}


Test(handle_setenv_test, inv_key, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    args[0] = "setenv";
    args[1] = "leticia_+";
    args[2] = 0;

    int res = handle_setenv(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str(
        "setenv: Variable name must contain alphanumeric characters.\n");
    free_state(state);
}

Test(handle_setenv_test, no_args, .init=cr_redirect_stdout)
{
    char *args[3];
    global_state_t *state = create_state();

    args[0] = "setenv";
    args[1] = 0;
    args[2] = 0;

    int res = handle_setenv(args, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin\n");
    free_state(state);
}

Test(handle_setenv_test, setenv, .init=cr_redirect_stdout)
{
    char *args[4];
    global_state_t *state = create_state();

    args[0] = "setenv";
    args[1] = "leticia";
    args[2] = "aa";
    args[3] = 0;

    int res = handle_setenv(args, state);
    args[1] = 0;
    handle_env(args, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin\nleticia=aa\n");
    free_state(state);
}

Test(handle_setenv_test, setenv_update, .init=cr_redirect_stdout)
{
    char *args[4];
    global_state_t *state = create_state();

    args[0] = "setenv";
    args[1] = "leticia";
    args[2] = "aa";
    args[3] = 0;

    int res = handle_setenv(args, state);
    args[2] = "bb";
    res = handle_setenv(args, state);
    args[1] = 0;
    handle_env(args, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin\nleticia=bb\n");
    free_state(state);
}