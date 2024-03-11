/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/shell.h"

static int cmp_key(char *key, env_item *item)
{
    return my_strcmp(key, item->key);
}

int handle_unsetenv(char **args, linked_list_t **env)
{
    char *key = args[1];
    env_item *deleted;

    if (key == 0) {
        my_put_err("unsetenv: Too few arguments.\n");
        return 1;
    }
    deleted = delete_in_list(env, key, &cmp_key);
    if (deleted) {
        free(deleted->key);
        free(deleted->value);
        free(deleted);
    }
    return 0;
}
