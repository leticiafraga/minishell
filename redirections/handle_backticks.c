/*
** EPITECH PROJECT, 2024
** handle_backticks ()
** File description:
** handle_backticks
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/helpers.h"

static int print_res(int p_read,
    tree_t *root, global_state_t *g_state)
{
    char res[400] = "";
    int nbytes = 0;
    int len = 0;
    char *new_run;

    nbytes = read(p_read, res, sizeof(res));
    len = strlen(root->left->data) + nbytes;
    new_run = malloc(sizeof(char) * len + 1);
    strcpy(new_run, root->left->data);
    strcat(new_run, res);
    free(root->left->data);
    root->left->data = new_run;
    return run_tree(root->left, g_state);
}

static int handle_fork(int p_read, int p_write,
    char *cmd, global_state_t *g_state)
{
    pid_t child = fork();
    int status = 0;

    if (child == 0) {
        close(p_read);
        dup2(p_write, 1);
        status = exec_line(cmd, g_state);
        close(p_write);
        exit(status);
    } else {
        close(p_write);
        waitpid(child, &status, 0);
    }
    return status;
}

static int inner_pipe(tree_t *root, global_state_t *state)
{
    int mypipe[2];
    int status = 0;

    if (pipe(mypipe) == -1)
        return 84;
    handle_fork(mypipe[0], mypipe[1], root->right->data, state);
    status = print_res(mypipe[0], root, state);
    close(mypipe[0]);
    return status;
}

static void restore_copies(int copies[2])
{
    dup2(copies[0], STDIN_FILENO);
    dup2(copies[1], STDOUT_FILENO);
}

int handle_backticks(tree_t *root, global_state_t *state)
{
    global_state_t new_state;
    linked_list_t *env = 0;
    int status;
    int copies[2] = { dup(STDIN_FILENO), dup(STDOUT_FILENO) };

    env = clone_list_env(state->env);
    new_state.env = &env;
    new_state.pwd = strdup(state->pwd);
    status = inner_pipe(root, &new_state);
    free_env(env);
    free(new_state.pwd);
    restore_copies(copies);
    return status;
}
