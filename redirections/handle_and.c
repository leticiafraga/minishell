/*
** EPITECH PROJECT, 2024
** handle_and &&
** File description:
** handle_and
*/

#include "../include/my.h"
#include "../include/shell.h"

int handle_and(tree_t *root, global_state_t *state)
{
    int status = run_tree(root->left, state);

    if (status == 0)
        return run_tree(root->right, state);
    else
        return status;
}
