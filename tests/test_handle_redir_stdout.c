#include "../include/shell.h"
#include "../include/my.h"
#include "../include/redirection.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_redir_stdout_test, basic_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    cmds_arr_t *s = sep_semicolon("ls run_prog.c > lsresult; cat lsresult");

    int res = it_semicolons(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\n");
    free(env);
    free_semic(s);
}

Test(handle_redir_stdout_append_test, basic_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    cmds_arr_t *s = sep_semicolon(
        "rm lsresultappend; ls run_prog.c >> lsresultappend; ls run_prog.c >> lsresultappend; cat lsresultappend");

    int res = it_semicolons(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("run_prog.c\nrun_prog.c\n");
    free(env);
    free_semic(s);
}
