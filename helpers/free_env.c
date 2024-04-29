/*
** EPITECH PROJECT, 2024
** getenv_list
** File description:
** getenv_list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

void free_env(linked_list_t *list)
{
    linked_list_t *next;
    env_item_t *item;

    while (list != 0) {
        next = list->next;
        item = list->data;
        free(item->key);
        free(item->value);
        free(list->data);
        free(list);
        list = next;
    }
}

void free_ptr_arr(char **args)
{
    int i = 0;

    if (args == 0)
        return;
    while (args[i] != 0) {
        free(args[i]);
        i++;
    }
    free(args);
}

void free_ptr_arr_content(char **args)
{
    int i = 0;

    if (args == 0)
        return;
    while (args[i] != 0) {
        free(args[i]);
        i++;
    }
}
