/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"
#include "../include/redirections_fn.h"

static void free_vars(char **args, char **arr, char **paths)
{
    free_ptr_arr(args);
    free_ptr_arr(arr);
    free_ptr_arr(paths);
}

static void free_cmd_state(cmd_state *state)
{
    free_ptr_arr(state->arrenv);
    free_ptr_arr(state->cmdargs);
    free_ptr_arr(state->paths);
    free(state);
}

cmd_state *getcmd_state(char *args, linked_list_t **env)
{
    cmd_state *state = malloc(sizeof(cmd_state));

    state->cmdargs = my_str_to_word_array(args);
    state->arrenv = getenv_arr(*env);
    state->paths = get_paths(state->cmdargs[0], *env);
    state->env = env;
    return state;
}

static int run_cmds(linked_list_t **env,
    redirection_map *red, char **cmds)
{
    int status = 0;
    sep symbol;

    for (int i = 0; i < red->cnt; i++) {
        symbol = red->arr[i]->symbol;
        status = (redirections_fn[symbol])(cmds, env, &i, red);
    }
    return status;
}

static int handle_exec_inner(char *args, linked_list_t **env)
{
    cmd_state *state = getcmd_state(args, env);
    redirection_map *red = get_cmds(args);
    char **cmds = malloc(sizeof(char *) * (red->cnt + 1));
    int status = 0;

    for (int i = 0; i < red->cnt; i++) {
        cmds[i] = my_strdup(red->arr[i]->cmd);
    }
    cmds[red->cnt] = 0;
    status = run_cmds(env, red, cmds);
    free_seps(red);
    free_ptr_arr(cmds);
    free_cmd_state(state);
    return status;
}

static int handle_fork(int p_read, int p_write,
    char *args, linked_list_t **env)
{
    pid_t child = fork();
    int status = 0;

    if (child == 0) {
        if (p_read != 0) {
            dup2(p_read, 0);
            close(p_read);
        }
        dup2(p_write, 1);
        close(p_write);
        handle_exec_inner(args, env);
    } else {
        close(p_read);
        close(p_write);
    }
    return status;
}

static int handle_second(char *args, linked_list_t **env, int *status)
{
    pid_t child = fork();
    cmd_state *state = getcmd_state(args, env);

    if (child == 0) {
        handle_exec_inner(args, env);
    } else {
        waitpid(child, status, 0);
    }
    return *status;
}

static int restore_copies(int copies[2])
{
    dup2(copies[0], 0);
    dup2(copies[1], 1);
}

static int pipe_inner(linked_list_t **env,
    redirection_map *red)
{
    int mypipe[2];
    int p_read = 0;
    int status;
    int i = 0;

    for (i = 0; i < red->cnt - 1; i++) {
        if (pipe(mypipe))
            return 84;
        handle_fork(p_read, mypipe[1], red->arr[i]->cmd, env);
        p_read = mypipe[0];
        if (p_read != 0) {
            dup2(p_read, 0);
        }
    }
    handle_second(red->arr[i]->cmd, env, &status);
    return handle_status(status);
}

int handle_pipe(linked_list_t **env, redirection_map *red)
{
    int copies[2] = { dup(STDIN_FILENO), dup(STDOUT_FILENO) };
    int status = pipe_inner(env, red);

    restore_copies(copies);
    return status;
}
