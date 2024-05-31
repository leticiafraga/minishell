#include "../include/shell.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

Test(getenv_list_test, basic_tests)
{
    linked_list_t *env = create_env();
    char **env2 = getenv_arr(env);
    linked_list_t *env3 = getenv_list(env2);
    env_item_t *item = env->data;
    env_item_t *item3 = env3->data;

    cr_assert_str_eq(item->key, item3->key);
    cr_assert_str_eq(item->value, item3->value);
    cr_assert_eq(env3->next, 0);
    cr_assert_eq(env2[1], 0);

    free_env(env);
    free_ptr_arr(env2);
    free_env(env3);
}

Test(put_arg_err_test, no_arg, .init=cr_redirect_stderr)
{
    put_arg_err(NULL, "testing");

    cr_assert_stderr_eq_str(": testing\n");
}

Test(parse_args_test, basic_tests)
{
    char *str = "echo '42 sh .c'";
    char **res = parse_args(str);

    cr_assert_str_eq(res[0], "echo");
    cr_assert_str_eq(res[1], "42 sh .c");
    cr_assert_eq(res[2], 0);
    free_ptr_arr(res);
}

Test(exec_line_test, command_exists)
{
    char *arg = "ls main.c";
    global_state_t *state = create_state();

    int res = exec_line(arg, state);

    cr_assert_eq(res, 0);
    free(state);
}

Test(exec_line_test, runs_builtin)
{
    char *arg = "cd ..";
    global_state_t *state = create_state();

    int res = run_prog(arg, state);

    cr_assert_eq(res, 0);
    free_state(state);
}

Test(exec_line_test, file_nonexistent, .init=cr_redirect_stderr)
{
    char *arg = "aaa";
    global_state_t *state = create_state();

    int res = exec_line(arg, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("aaa: Command not found.\n");
    free_state(state);
}

Test(exec_line_test, file_nopermission, .init=cr_redirect_stderr)
{
    char *arg = "chmod 444 ./tests/nopermission; ./tests/nopermission";
    global_state_t *state = create_state();

    int res = exec_line(arg, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("./tests/nopermission: Permission denied.\n");
    free_state(state);
}

Test(exec_line_test, segfault, .init=cr_redirect_stderr, .signal = SIGSEGV)
{
    char *arg = "./tests/segfault/my_segfault";
    global_state_t *state = create_state();

    int res = run_prog(arg, state);

    cr_assert_eq(res, 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}
