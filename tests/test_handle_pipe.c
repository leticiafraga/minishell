#include "../include/shell.h"
#include "../include/my.h"
#include "../include/redirection.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(it_pipes_test, basic_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    cmds_arr_t *s = sep_semicolon("ls | grep run_prog.c");

    int res = it_semicolons(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n");
    free(env);
    free_cmds_arr(s);
}

Test(it_pipes_test, multiple_pipe, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    cmds_arr_t *s = sep_semicolon("ls | grep run_prog.c | wc -l");

    int res = it_semicolons(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("1\n");
    free(env);
    free_cmds_arr(s);
}