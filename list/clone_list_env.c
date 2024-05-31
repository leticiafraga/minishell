/*
** EPITECH PROJECT, 2024
** clone_list
** File description:
** clone_list
*/

#include "../include/linked_list.h"
#include "../include/my.h"
#include <stdlib.h>

static void add_new_data(linked_list_t *new, linked_list_t *cur)
{
    env_item_t *new_item = malloc(sizeof(env_item_t));
    env_item_t *cur_item = (env_item_t *) cur->data;

    new_item->key = my_strdup(cur_item->key);
    new_item->value = my_strdup(cur_item->value);
    new->data = new_item;
    new->next = 0;
}

linked_list_t *clone_list_env(linked_list_t **begin)
{
    linked_list_t *new = 0;
    linked_list_t *beg = 0;
    linked_list_t *prev = 0;
    linked_list_t *cur = *begin;

    if (cur != 0) {
        beg = malloc(sizeof(linked_list_t));
        add_new_data(beg, cur);
        cur = cur->next;
        prev = beg;
    }
    while (cur != 0) {
        new = malloc(sizeof(linked_list_t));
        add_new_data(new, cur);
        cur = cur->next;
        prev->next = new;
        prev = new;
    }
    return beg;
}
