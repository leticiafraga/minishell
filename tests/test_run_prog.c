#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(run_prog_test, command_exists)
{
    char *arg = "ls";
    linked_list_t *env = create_env();

    int res = run_prog(arg, &env);

    cr_assert_eq(res, 0);
    free(env);
}

Test(run_prog_test, no_path)
{
    char *arg = "ls";
    linked_list_t *env = 0;

    int res = run_prog(arg, &env);

    cr_assert_eq(res, 1);
}

Test(run_prog_test, segfault, .init=cr_redirect_stderr)
{
    char *arg = "./tests/my_segfault";
    linked_list_t *env = create_env();

    int res = run_prog(arg, &env);

    cr_assert_eq(res, 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
    free(env);
}

Test(run_prog_test, runs_builtin)
{
    char *arg = "cd ..";
    linked_list_t *env = 0;

    int res = run_prog(arg, &env);

    cr_assert_eq(res, 0);
    free(env);
}

Test(run_prog_test, file_nonexistent, .init=cr_redirect_stderr)
{
    char *arg = "aaa";
    linked_list_t *env = 0;

    int res = run_prog(arg, &env);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("aaa: Command not found.\n");
    free(env);
}

Test(run_prog_test, file_nopermission, .init=cr_redirect_stderr)
{
    char *arg = "./tests/nopermission";
    linked_list_t *env = 0;

    int res = run_prog(arg, &env);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("./tests/nopermission: Permission denied.\n");
    free(env);
}
