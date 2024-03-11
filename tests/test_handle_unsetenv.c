#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_unsetenv_test, few_args, .init=cr_redirect_stderr)
{
    char *args[2];
    linked_list_t *env = create_env();

    args[0] = "unsetenv";
    args[1] = 0;

    int res = handle_unsetenv(args, &env);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
    free(env);
}

Test(handle_unsetenv_test, unsetenv, .init=cr_redirect_stderr)
{
    char *args[3];
    linked_list_t *env = create_env();

    add_item("leticia", "aa", &env);

    args[0] = "unsetenv";
    args[1] = "leticia";
    args[2] = 0;

    int res = handle_unsetenv(args, &env);
    cr_assert_eq(res, 0);
    res = handle_unsetenv(args, &env);
    cr_assert_eq(res, 0);
    free(env);
}

