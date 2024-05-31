/*
** EPITECH PROJECT, 2024
** push_unique_to_list
** File description:
** push_unique_to_list
*/

#include "../include/linked_list.h"
#include "../include/my.h"
#include "../include/shell.h"
#include <stdlib.h>

void push_unique_to_list(linked_list_t **begin, env_item_t *data)
{
    linked_list_t *cur = *begin;
    env_item_t *item;

    while (cur != 0) {
        item = cur->data;
        if (my_strcmp(item->key, data->key) == 0) {
            free(item->value);
            item->value = data->value;
            free(data->key);
            free(data);
            return;
        }
        cur = cur->next;
    }
    push_to_list(begin, data);
}
