/*
** EPITECH PROJECT, 2024
** handle_dollar $
** File description:
** handle_dollar
*/

#include "../include/my.h"
#include "../include/shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int run_tree_with_var(
    tree_t *root, global_state_t *g_state, char *value)
{
    int len = 0;
    char *new_run;

    len = strlen(root->left->data) + strlen(value);
    new_run = malloc(sizeof(char) * len + 1);
    strcpy(new_run, root->left->data);
    strcat(new_run, value);
    free(root->left->data);
    root->left->data = new_run;
    return run_tree(root->left, g_state);
}

int handle_dollar(tree_t *root, global_state_t *state)
{
    char *value = my_getenv(*state->env, root->right->data);
    int status = 0;

    if (value) {
        status = run_tree_with_var(root, state, value);
        free(value);
        return status;
    }
    status = run_tree(root->left, state);
    return status;
}
