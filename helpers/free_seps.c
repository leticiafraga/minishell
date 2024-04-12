/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "../include/redirection.h"
#include "../include/shell.h"
#include <stdlib.h>

int free_seps(redirection_list_t *r)
{
    for (int i = 0; i < r->cnt; i++) {
        free(r->arr[i]->cmd);
        free(r->arr[i]);
    }
    free(r->arr);
    free(r);
}

int free_semic(redirection_map_semic_t *r)
{
    for (int i = 0; i < r->cnt; i++) {
        free(r->arr[i]);
    }
    free(r->arr);
    free(r);
}

void free_vars(char **args, char **arr, char **paths)
{
    free_ptr_arr(args);
    free_ptr_arr(arr);
    free_ptr_arr(paths);
}

void free_cmd_state(cmd_state *state)
{
    free_ptr_arr(state->arrenv);
    free_ptr_arr(state->cmdargs);
    free_ptr_arr(state->paths);
    free(state);
}
