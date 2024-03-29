#include "../include/shell.h"
#include "../include/my.h"
#include "../include/redirection.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_redir_stdin_test, basic_test, .init=cr_redirect_stdout)
{
    linked_list_t *env = create_env();
    redirection_map_semic *s = sep_semicolon("cat < tests/cattest");

    int res = run_all(&env, s);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("hola\n");
    free(env);
    free_semic(s);
}
