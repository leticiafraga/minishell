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

static const char *commands[5] = {
    "cd",
    "env",
    "setenv",
    "unsetenv",
    0
};

static int (*commands_fn[5]) (char **args, linked_list_t **env) = {
    &handle_cd,
    &handle_env,
    &handle_setenv,
    &handle_unsetenv,
    0
};

cmd_state_t *getcmd_state(char *args, linked_list_t **env)
{
    cmd_state_t *state = malloc(sizeof(cmd_state_t));

    state->cmdargs = my_str_to_word_array(args);
    state->arrenv = getenv_arr(*env);
    state->paths = get_paths(state->cmdargs[0], *env);
    state->env = env;
    return state;
}

static int run_cmds(global_state_t *state)
{
    int status = 0;
    sep_t symbol;
    redirection_list2_t *red = state->red_inner;

    if (red->in) {
        handle_redir_stdin(red->cmd, state->env, state->red_inner);
    } else if (red->out) {
        handle_redir_stdout(red->cmd, state->env, state->red_inner);
    } else
        handle_semicolon2(red->cmd, state->env, state->red_inner);
    return status;
}

static int handle_exec_inner(char *args, global_state_t *g_state)
{
    cmd_state_t *state = getcmd_state(args, g_state->env);
    redirection_list2_t *red = get_cmds(args);
    int status = 0;

    g_state->red_inner = red;
    status = run_cmds(g_state);
    free_cmd_state(state);
    return status;
}

static int handle_fork(int p_read, int p_write,
    char *args, global_state_t *g_state)
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
        handle_exec_inner(args, g_state);
    } else {
        close(p_read);
        close(p_write);
    }
    return status;
}

static int handle_fork_2(char *args,
    global_state_t *g_state)
{
    pid_t child;
    int status = 0;

    child = fork();
    if (child == 0) {
        handle_exec_inner(args, g_state);
    } else
        waitpid(child, &status, 0);
    return status;
}

static int handle_last(char *args, global_state_t *g_state, int *status)
{
    cmd_state_t *state = getcmd_state(args, g_state->env);

    for (int i = 0; i < 5; i++) {
        if (commands[i] == 0) {
            *status = handle_status(
                handle_fork_2(args, g_state));
            break;
        }
        if (my_strcmp(state->cmdargs[0], commands[i]) == 0) {
            *status = (commands_fn[i])(state->cmdargs, g_state->env);
            break;
        }
    }
    free_cmd_state(state);
    return *status;
}

static int restore_copies(int copies[2])
{
    dup2(copies[0], 0);
    dup2(copies[1], 1);
}

static int pipe_inner(global_state_t *state)
{
    linked_list_t **env = state->env;
    cmds_arr_t *red = state->red;
    int p_read = 0;
    int status;
    int i = 0;

    for (i = 0; i < red->cnt - 1; i++) {
        if (pipe(state->global_pipe))
            return 84;
        handle_fork(p_read, state->global_pipe[1], red->arr[i], state);
        p_read = state->global_pipe[0];
        if (p_read != 0) {
            dup2(p_read, 0);
        }
    }
    handle_last(red->arr[i], state, &status);
    return handle_status(status);
}

int it_pipes(global_state_t *state)
{
    int copies[2] = { dup(STDIN_FILENO), dup(STDOUT_FILENO) };
    int status = pipe_inner(state);

    restore_copies(copies);
    return status;
}
