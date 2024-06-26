#include "../include/shell.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_redir_stdout_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls run_prog.c > lsresult; cat lsresult";

    int res = exec_line(s, state);
    exec_line("rm lsresult", state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n");
    free_state(state);
}

Test(handle_redir_stdout_append_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "ls run_prog.c >> lsresultappend; ls run_prog.c >> lsresultappend; cat lsresultappend";

    int res = exec_line(s, state);
    exec_line("rm lsresultappend", state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\nrun_prog.c\n");
    free_state(state);
}

Test(handle_redir_stdin_test, basic_test, .init=cr_redirect_stdout)
{
    global_state_t *state = create_state();
    char *s = "cat < tests/cattest";

    int res = exec_line(s, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("hola\n");
    free_state(state);
}
