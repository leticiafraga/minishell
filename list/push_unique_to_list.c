/*
** EPITECH PROJECT, 2023
** push_unique_to_list
** File description:
** push_unique_to_list
*/

#include "../include/linked_list.h"
#include "../include/my.h"
#include "../include/shell.h"
#include <stdlib.h>

void push_unique_to_list(linked_list_t **begin, env_item_h *data)
{
    linked_list_t *cur = *begin;

    while (cur != 0) {
        if (my_strcmp(cur->data->key, data->key) == 0) {
            free(cur->data->value);
            cur->data->value = data->value;
            free(data->key);
            free(data);
            return;
        }
        cur = cur->next;
    }
    push_to_list(begin, data);
}
