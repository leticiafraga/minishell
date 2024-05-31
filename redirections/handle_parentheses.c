/*
** EPITECH PROJECT, 2024
** handle_parentheses ()
** File description:
** handle_parentheses
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/shell.h"
#include <string.h>

int handle_parentheses(tree_t *root, global_state_t *state)
{
    global_state_t new_state;
    linked_list_t *env = 0;
    int status = 0;

    env = clone_list_env(state->env);
    new_state.env = &env;
    new_state.pwd = strdup(state->pwd);
    status = exec_line(root->right->data, &new_state);
    free_env(env);
    free(new_state.pwd);
    return status;
}
