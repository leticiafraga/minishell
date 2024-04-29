/*
** EPITECH PROJECT, 2024
** tree_pipe
** File description:
** tree_pipe
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

static int handle_fork(int p_read, int p_write,
    tree_t *left, global_state_t *g_state)
{
    pid_t child = fork();
    int status = 0;

    if (child == 0) {
        close(p_read);
        dup2(p_write, 1);
        status = run_tree(left, g_state);
        close(p_write);
        exit(status);
    } else {
        close(p_write);
    }
    return status;
}

static int inner_pipe(tree_t *root, global_state_t *state)
{
    int mypipe[2];
    int status = 0;

    if (pipe(mypipe) == -1)
        return 84;
    handle_fork(mypipe[0], mypipe[1], root->left, state);
    close(mypipe[1]);
    dup2(mypipe[0], STDIN_FILENO);
    status = run_tree(root->right, state);
    close(mypipe[0]);
    return status;
}

static void restore_copies(int copies[2])
{
    dup2(copies[0], STDIN_FILENO);
    dup2(copies[1], STDOUT_FILENO);
}

int tree_pipe(tree_t *root, global_state_t *state)
{
    int copies[2] = { dup(STDIN_FILENO), dup(STDOUT_FILENO) };
    int status = inner_pipe(root, state);

    restore_copies(copies);
    return status;
}
