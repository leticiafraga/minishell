#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(getenv_list_test, basic_tests)
{
    linked_list_t *env = create_env();
    char **env2 = getenv_arr(env);
    linked_list_t *env3 = getenv_list(env2);

    cr_assert_str_eq(env->data->key, env3->data->key);
    cr_assert_str_eq(env->data->value, env3->data->value);
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

