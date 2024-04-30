/*
** EPITECH PROJECT, 2024
** my_getenv
** File description:
** my_getenv
*/

#include "../include/my.h"
#include "../include/linked_list.h"

char *my_getenv(linked_list_t *env, char *var)
{
    char *value;
    env_item_t *item;

    while (env != 0) {
        item = env->data;
        if (my_strcmp(item->key, var) == 0) {
            value = item->value;
            return value;
        }
        env = env->next;
    }
    return 0;
}
