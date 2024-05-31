#include "../include/shell.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_env_test, command_exists, .init=cr_redirect_stdout)
{
    char *args[3];
    global_state_t *state = create_state();

    args[0] = "env";
    args[1] = 0;
    args[2] = 0;

    int res = handle_env(args, state);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin\n");
    free_state(state);
}