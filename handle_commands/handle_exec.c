/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/signal.h>
#include "../include/my.h"
#include "../include/shell.h"

static void create_path_str(
    cmd_state_t *state, char dest[200], int i)
{
    char **args = state->cmdargs;
    char **paths = state->paths;

    my_strcpy(dest, paths[i]);
    my_strcat(dest, "/");
    my_strcat(dest, args[0]);
}

int try_paths(cmd_state_t *state)
{
    char **args = state->cmdargs;
    char **paths = state->paths;
    int res_exec = -1;
    char dest[200];
    int i = 0;

    dest[0] = '\0';
    if (paths != 0) {
        while (res_exec == -1 && paths[i] != 0) {
            create_path_str(state, dest, i);
            res_exec = execve(dest, args, state->arrenv);
            i++;
        }
    }
    if (res_exec == -1)
        res_exec = execve(args[0], args, state->arrenv);
    return res_exec;
}

static int handle_error(char *arg)
{
    switch (errno) {
        case 13:
            put_arg_err(arg, "Permission denied.");
            break;
        case 8:
            put_arg_err(arg,
                "Exec format error. Wrong Architecture.");
            break;
        default:
            put_arg_err(arg, "Command not found.");
            break;
    }
    return 1;
}

void handle_exec(cmd_state_t *state)
{
    char **args = state->cmdargs;
    char **env = state->arrenv;
    linked_list_t *listenv = *(state->env);
    int res_exec = 0;

    if (args[0][0] == '.' || args[0][0] == '/')
        res_exec = execve(args[0], args, env);
    else {
        res_exec = try_paths(state);
    }
    if (res_exec == -1) {
        res_exec = handle_error(args[0]);
    }
    free_cmd_state(state);
    exit(res_exec);
}
