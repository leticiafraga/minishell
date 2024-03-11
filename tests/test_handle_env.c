#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(handle_env_test, command_exists, .init=cr_redirect_stdout)
{
    char *args[3];
    linked_list_t *env = create_env();

    args[0] = "env";
    args[1] = 0;
    args[2] = 0;

    int res = handle_env(args, &env);

    cr_assert_eq(res, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin\n");
    free(env);
}
