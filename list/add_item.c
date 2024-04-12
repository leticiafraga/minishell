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

int add_item(char *key, char *value, linked_list_t **env)
{
    env_item_h *item = malloc(sizeof(env_item_h));

    item->key = my_strdup(key);
    if (value == 0) {
        item->value = malloc(sizeof(char));
        item->value[0] = '\0';
    } else
        item->value = my_strdup(value);
    push_unique_to_list(env, item);
}
