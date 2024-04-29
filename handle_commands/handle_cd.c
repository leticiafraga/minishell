/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/shell.h"

static int handle_old(char *path, linked_list_t **env)
{
    int status = 0;
    char *old;

    old = my_getenv(*env, "OLDPWD");
    status = old ? chdir(old) : chdir("");
    path[0] = '\0';
    return status;
}

static int handle_home(linked_list_t **env)
{
    int status = 0;
    char *home = my_getenv(*env, "HOME");

    if (home == 0) {
        errno = -3;
        return -1;
    }
    status = chdir(home);
    if (status != 0)
        errno = -4;
    return status;
}

static int exec_cd(char *path, linked_list_t **env)
{
    int status = 0;

    if (path == 0 || my_strcmp(path, "~") == 0)
        status = handle_home(env);
    else if (my_strcmp(path, "-") == 0) {
        status = handle_old(path, env);
    } else
        status = chdir(path);
    return status;
}

static void handle_error(char *arg)
{
    switch (errno) {
        case -3:
            my_put_err("cd: No home directory.\n");
            break;
        case -4:
            my_put_err("cd: Can't change to home directory.\n");
            break;
        case 13:
            put_arg_err(arg, "Permission denied.");
            break;
        case 2:
            put_arg_err(arg, "No such file or directory.");
            break;
        case 20:
            put_arg_err(arg, "Not a directory.");
            break;
        default:
            break;
    }
}

static void update_state_pwd(global_state_t *state, char *cur)
{
    free(state->pwd);
    state->pwd = my_strdup(cur);
}

int handle_cd(char **args, global_state_t *state)
{
    char *path = args[1];
    char cur[200];
    int status = 0;

    if (path != 0 && args[2] != 0) {
        my_put_err("cd: Too many arguments.\n");
        return 1;
    }
    getcwd(cur, 200);
    status = exec_cd(path, state->env);
    if (status != 0) {
        handle_error(path);
        return 1;
    }
    add_item("OLDPWD", cur, state->env);
    getcwd(cur, 200);
    add_item("PWD", cur, state->env);
    update_state_pwd(state, cur);
    return status;
}
