/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "../include/helpers.h"
#include "../include/my.h"
#include "../include/shell.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

/**
 * @brief checks if file exists and is executable
 * f_path is being concatnated with fname with "/" as a separator
 * @param fname
 * @param f_path
 * @return
 */
int file_exists_and_ex(const char *fname, const char *f_path)
{
    char *a = concat_strings(3, f_path, "/", fname);

    if ((access(a, F_OK) == 0) && access(a, X_OK) == 0) {
        free(a);
        return 1;
    }
    free(a);
    return 0;
}

int try_paths(cmd_state_t *state)
{
    char **args = state->cmdargs;
    char **paths = state->paths;
    int res_exec = -1;
    int i = 0;
    char *path_buffer;

    for (size_t i = 0; paths && paths[i]; ++i) {
        if (file_exists_and_ex(state->cmdargs[0], paths[i])) {
            path_buffer = concat_strings(3, paths[i], "/", state->cmdargs[0]);
            res_exec = execve(path_buffer, args, state->arrenv);
            free(path_buffer);
            return res_exec;
        }
    }
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
        put_arg_err(arg, "Exec format error. Wrong Architecture.");
        break;
    default:
        put_arg_err(arg, "Command not found.");
        break;
    }
    return 1;
}

int needs_search_in_path(char **arg)
{
    if (arg[0][0] && arg[0][0] == '/')
        return 0;
    if (arg[0][1] && arg[0][0] == '.' && arg[0][1] == '/')
        return 0;
    return 1;
}

void handle_exec(cmd_state_t *state)
{
    char **args = state->cmdargs;
    char **env = state->arrenv;
    linked_list_t *listenv = *(state->env);
    int res_exec = 0;

    if (!needs_search_in_path(args))
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
