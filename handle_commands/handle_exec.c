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

int try_paths(char **args, char **env, char **paths)
{
    int res_exec = -1;
    char dest[200];
    int i = 0;

    dest[0] = '\0';
    if (paths != 0) {
        while (res_exec == -1 && paths[i] != 0) {
            my_strcpy(dest, paths[i]);
            my_strcat(dest, "/");
            my_strcat(dest, args[0]);
            res_exec = execve(dest, args, env);
            i++;
        }
    }
    if (res_exec == -1)
        res_exec = execve(args[0], args, env);
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

static void free_vars(char **args, char **arr, char **paths)
{
    free_ptr_arr(args);
    free_ptr_arr(arr);
    free_ptr_arr(paths);
}

void handle_exec(char **args, char **env, char **paths,
    linked_list_t *listenv)
{
    int res_exec = 0;

    if (args[0][0] == '.' || args[0][0] == '/')
        res_exec = execve(args[0], args, env);
    else {
        res_exec = try_paths(args, env, paths);
    }
    if (res_exec == -1) {
        res_exec = handle_error(args[0]);
    }
    free_vars(args, env, paths);
    free_env(listenv);
    exit(res_exec);
}
