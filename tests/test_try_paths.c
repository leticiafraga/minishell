#include "../include/shell.h"
#include "../include/my.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(try_paths_test, command_exists)
{
    char **arg = malloc(sizeof(char*) * 2);
    char **env = malloc(sizeof(char*) * 2);
    char **paths = malloc(sizeof(char*) * 2);

    arg[0] = "ls";
    arg[1] = 0;
    env[0] = "PATH=/usr/bin";
    env[1] = 0;
    paths[0] = "/usr/bin";
    paths[1] = 0;

    int res = try_paths(arg, env, paths);

    cr_assert_eq(res, 0);
    free(arg);
    free(env);
}

Test(try_paths_test, no_command)
{
    char **arg = malloc(sizeof(char*) * 2);
    char **env = malloc(sizeof(char*) * 2);
    char **paths = malloc(sizeof(char*) * 2);

    arg[0] = "nonexistent";
    arg[1] = 0;
    env[0] = "PATH=/usr/bin";
    env[1] = 0;
    paths[0] = "/usr/bin";
    paths[1] = 0;

    int res = try_paths(arg, env, paths);

    cr_assert_eq(res, -1);
    free(arg);
    free(env);
}

Test(try_paths_test, no_path)
{
    char **arg = malloc(sizeof(char*) * 2);
    char **env = malloc(sizeof(char*) * 2);
    char **paths = 0;

    arg[0] = "ls";
    arg[1] = 0;
    env[0] = 0;
    env[1] = 0;

    int res = try_paths(arg, env, paths);

    cr_assert_eq(res, -1);
    free(arg);
    free(env);
}

