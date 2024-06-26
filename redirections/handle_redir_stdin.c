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

int handle_redir_stdin(
    tree_t *root, global_state_t *state)
{
    char *filename = clear_filename(root->right->data);
    int fd = open(filename, O_RDONLY);
    int dupin = dup(STDIN_FILENO);
    int status;

    if (fd < 0) {
        free(filename);
        return 1;
    }
    close(STDIN_FILENO);
    dup(fd);
    close(fd);
    status = run_tree(root->left, state);
    dup2(dupin, STDIN_FILENO);
    close(dupin);
    free(filename);
    return status;
}
