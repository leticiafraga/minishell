#include "../include/shell.h"
#include "../include/my.h"
#include "../include/redirection.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_semicolon_test, basic_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    redirection_map_semic_t *s = sep_semicolon("ls run_prog.c;cat tests/cattest");

    int res = it_semicolons(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\nhola\n");
    free(env);
    free_semic(s);
}

Test(handle_semicolon_test, more_complex_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    redirection_map_semic_t *s = sep_semicolon("ls run_prog.c; cat tests/cattest | wc -w");

    int res = it_semicolons(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n1\n");
    free(env);
    free_semic(s);
}