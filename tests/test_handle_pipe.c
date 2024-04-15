#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(it_pipes_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls | grep run_prog.c";

    int res = it_semicolons(state, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n");
    free_state(state);
}

Test(it_pipes_test, multiple_pipe, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls | grep run_prog.c | wc -l";

    int res = it_semicolons(state, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("1\n");
    free_state(state);
}