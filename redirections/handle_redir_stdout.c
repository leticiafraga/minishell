/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

int handle_redir_stdout(
    char *args, global_state_t *state)
{
    char *filename = clear_filename(state->red_inner->out->filename);
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    int dupout = dup(1);
    int status;

    close(1);
    dup(fd);
    close(fd);
    status = run_prog(args, state);
    dup2(dupout, 1);
    close(dupout);
    free(filename);
    return status;
}

int tree_redir_stdout(
    tree_t *root, global_state_t *state)
{
    char *filename = clear_filename(root->right->data);
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    int dupout = dup(1);
    int status;

    close(1);
    dup(fd);
    close(fd);
    status = run_tree(root->left, state);
    dup2(dupout, 1);
    close(dupout);
    free(filename);
    return status;
}
