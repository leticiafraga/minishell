/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "../include/redirection.h"
#include "../include/shell.h"
#include <stdlib.h>


void free_cmd_state(cmd_state_t *state)
{
    free_ptr_arr(state->arrenv);
    free_ptr_arr(state->cmdargs);
    free_ptr_arr(state->paths);
    free(state);
}

void free_tree(tree_t *tree)
{
    if (tree == 0)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    if (tree->data)
        free(tree->data);
    free(tree);
}

void free_list(linked_list_t *list)
{
    linked_list_t *next;

    while (list != 0) {
        next = list->next;
        free(list->data);
        free(list);
        list = next;
    }
}
