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

extern const char *commands[5];

extern int (*commands_fn[]) (char **args, global_state_t *state);

static int handle_in(cmd_opts_t *red, global_state_t *state)
{
    if (red->in->symbol == in1)
        return handle_redir_stdin(red->cmd, state);
    return handle_redir_stdin_word(red->cmd, state);
}

static int handle_out(cmd_opts_t *red, global_state_t *state)
{
    if (red->out->symbol == out1)
        return handle_redir_stdout(red->cmd, state);
    return handle_redir_stdout_append(red->cmd, state);
}

static int run_cmds(global_state_t *state)
{
    int status = 0;
    sep_t symbol;
    cmd_opts_t *red = state->red_inner;

    if (red->in) {
        return handle_in(red, state);
    } else if (red->out) {
        return handle_out(red, state);
    } else
        return run_prog(red->cmd, state);
}

static int handle_exec_inner(char *args, global_state_t *g_state)
{
    cmd_opts_t *red = get_cmd_opts(args);
    int status = 0;

    g_state->red_inner = red;
    status = run_cmds(g_state);
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
        status = handle_exec_inner(args, g_state);
        exit(status);
    } else {
        close(p_read);
        close(p_write);
    }
    return status;
}

static int handle_fork_without_pipe(char *args,
    global_state_t *g_state)
{
    pid_t child;
    int status = 0;

    child = fork();
    if (child == 0) {
        handle_exec_inner(args, g_state);
    } else
        waitpid(child, &status, 0);
    return handle_status(status);
}

static int handle_last(char *args, global_state_t *g_state)
{
    char **cmdargs = my_str_to_word_array(args);
    int status = 0;

    for (int i = 0; i < 5; i++) {
        if (commands[i] == 0) {
            status =
                handle_fork_without_pipe(args, g_state);
            break;
        }
        if (my_strcmp(cmdargs[0], commands[i]) == 0) {
            status = handle_exec_inner(args, g_state);
            break;
        }
    }
    free_ptr_arr(cmdargs);
    return status;
}

static int restore_copies(int copies[2])
{
    dup2(copies[0], 0);
    dup2(copies[1], 1);
}

static int pipe_inner(global_state_t *state)
{
    linked_list_t **env = state->env;
    cmds_arr_t *red = state->cmd;
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
    status = handle_last(red->arr[i], state);
    return status;
}

int it_pipes(global_state_t *state)
{
    int copies[2] = { dup(STDIN_FILENO), dup(STDOUT_FILENO) };
    int status = pipe_inner(state);

    restore_copies(copies);
    return status;
}
