#include "../include/shell.h"
#include "../include/my.h"
#include "../include/redirection.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_pipe_test, basic_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    redirection_map_semic *s = sep_semicolon("ls | grep run_prog.c");

    int res = run_all(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n");
    free(env);
}

Test(handle_pipe_test, multiple_pipe, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    redirection_map_semic *s = sep_semicolon("ls | grep run_prog.c | wc -l");

    int res = run_all(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("1\n");
    free(env);
}