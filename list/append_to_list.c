/*
** EPITECH PROJECT, 2024
** append_to_list
** File description:
** append_to_list
*/

#include "../include/linked_list.h"
#include <stdlib.h>

static void add_last_item(linked_list_t **begin, linked_list_t *new)
{
    linked_list_t *cur = *begin;

    while (cur->next != 0) {
        cur = cur->next;
    }
    cur->next = new;
}

void append_to_list(linked_list_t **begin, void *data)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));

    new->data = data;
    new->next = 0;
    if (*begin != 0) {
        add_last_item(begin, new);
    } else {
        *begin = new;
        begin = &new;
    }
}
