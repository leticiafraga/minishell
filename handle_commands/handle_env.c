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
    if (env == 0)
        return 0;
    handle_env_inner(args, env->next);
    my_putstr(env->data->key);
    my_putchar('=');
    my_putstr(env->data->value);
    my_putchar('\n');
    return 0;
}

int handle_env(char **args, global_state_t *state)
{
    return handle_env_inner(args, *(state->env));
}
