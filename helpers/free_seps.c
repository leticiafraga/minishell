/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "../include/redirection.h"
#include <stdlib.h>

int free_seps(redirection_map *r)
{
    for (int i = 0; i < r->cnt; i++) {
        free(r->arr[i]);
    }
    free(r->arr);
    free(r);
}
