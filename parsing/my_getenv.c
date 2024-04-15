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

    while (env != 0) {
        if (my_strcmp(env->data->key, var) == 0) {
            value = env->data->value;
            return value;
        }
        env = env->next;
    }
    return 0;
}
