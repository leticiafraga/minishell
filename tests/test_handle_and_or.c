#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

Test(handle_and_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat tests/cattest && cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("hola\nhola\n");
    free_state(state);
}

Test(handle_and_test, basic_test_builtin, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat tests/cattest && cd ..";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("hola\n");
    free_state(state);
}

Test(handle_and_test, runs_only_first_cmd, .init=cr_redirect_stderr)
{
    global_state_t *state = create_state();
    char *s = "cat nofile && cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 1);
    cr_assert_stderr_eq_str("cat: nofile: No such file or directory\n");
    free_state(state);
}

Test(handle_and_test, multiple_ands, .init=redirect_all_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat tests/cattest && cat nofile && cat tests/cattest && cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 1);
    cr_assert_stdout_eq_str("hola\n");
    cr_assert_stderr_eq_str("cat: nofile: No such file or directory\n");
    free_state(state);
}

Test(handle_or_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat tests/cattest || cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("hola\n");
    free_state(state);
}

Test(handle_or_test, runs_both_cmds, .init=redirect_all_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat nofile || cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stderr_eq_str("cat: nofile: No such file or directory\n");
    cr_assert_stdout_eq_str("hola\n");
    free_state(state);
}

Test(handle_or_test, multiple_or, .init=redirect_all_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat nofile || cat tests/cattest || cat tests/cattest || cat tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stderr_eq_str("cat: nofile: No such file or directory\n");
    cr_assert_stdout_eq_str("hola\n");
    free_state(state);
}