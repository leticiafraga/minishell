/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <unistd.h>
#include "../include/my.h"
#include "../include/shell.h"

static int handle_env_inner(char **args, linked_list_t *env)
{
    env_item_t *item;

    if (env == 0)
        return 0;
    item = (env_item_t *) env->data;
    handle_env_inner(args, env->next);
    my_putstr(item->key);
    my_putchar('=');
    my_putstr(item->value);
    my_putchar('\n');
    return 0;
}

int handle_env(char **args, global_state_t *state)
{
    return handle_env_inner(args, *(state->env));
}
