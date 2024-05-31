#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_parentheses_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls main.c | ( cat | wc )";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("      1       1       7\n");
    free_state(state);
}