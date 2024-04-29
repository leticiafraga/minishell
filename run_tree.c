/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "include/my.h"
#include "include/shell.h"
#include "include/linked_list.h"

int handle_fork(tree_t *node, global_state_t *state)
{
    pid_t child = fork();
    int status = 0;

    if (child == 0) {
        status = run_prog(node->data, state);
        exit(status);
    } else {
        waitpid(child, &status, 0);
    }
    return status;
}

int run_tree(tree_t *root, global_state_t *state)
{
    int status = 0;

    if (root == NULL)
        return 0;
    switch (root->type) {
    case STRING:
        return handle_fork(root, state);
    case OP_SEMICOLON:
        run_tree(root->left, state);
        return run_tree(root->right, state);
    default:
        break;
    }
    return status;
}
