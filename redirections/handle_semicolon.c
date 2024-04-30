/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include "../include/my.h"
#include "../include/shell.h"

int handle_semicolon(
    tree_t *root, global_state_t *state)
{
    run_tree(root->left, state);
    return run_tree(root->right, state);
}
