#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_cd_test, command_exists)
{
    char *args[3];
    global_state_t *state = create_state();

    args[0] = "cd";
    args[1] = "..";
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 0);
    free_state(state);
}

Test(handle_cd_test, no_home, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    args[0] = "cd";
    args[1] = 0;
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
    free_state(state);
}

Test(handle_cd_test, home_inv, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    add_item("HOME", "aa", state->env);

    args[0] = "cd";
    args[1] = 0;
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("cd: Can't change to home directory.\n");
    free_state(state);
}

Test(handle_cd_test, home_inv_2, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    add_item("HOME", NULL, state->env);

    args[0] = "cd";
    args[1] = "~";
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("cd: Can't change to home directory.\n");
    free_state(state);
}

Test(handle_cd_test, home_v, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    add_item("HOME", "..", state->env);

    args[0] = "cd";
    args[1] = 0;
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 0);
    free_state(state);
}

Test(handle_cd_test, home_v_tilde, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    add_item("HOME", "..", state->env);

    args[0] = "cd";
    args[1] = "~";
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 0);
    free_state(state);
}

Test(handle_cd_test, many_args, .init=cr_redirect_stderr)
{
    char *args[4];
    global_state_t *state = create_state();


    args[0] = "cd";
    args[1] = "aa";
    args[2] = "bb";
    args[3] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
    free_state(state);
}

Test(handle_cd_test, no_dir, .init=cr_redirect_stderr)
{
    char *args[3];
    global_state_t *state = create_state();

    args[0] = "cd";
    args[1] = "aa";
    args[2] = 0;

    int res = handle_cd(args, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("aa: No such file or directory.\n");
    free_state(state);
}