/*
** EPITECH PROJECT, 2024
** delete_in_list
** File description:
** delete_in_list
*/

#include "../include/linked_list.h"
#include <stdlib.h>

static void del_item(linked_list_t **begin, linked_list_t **prev,
    linked_list_t *cur)
{
    if (*prev == 0)
        (*begin) = cur->next;
    else
        (*prev)->next = cur->next;
}

void *delete_in_list(linked_list_t **begin,
    void const *ref, int (*cmp_fct) ())
{
    linked_list_t *cur = *begin;
    linked_list_t *prev = 0;
    linked_list_t *tmp = 0;
    void *data;

    while (cur != 0) {
        tmp = cur->next;
        if (cmp_fct(ref, cur->data) == 0) {
            del_item(begin, &prev, cur);
            data = cur->data;
            free(cur);
            return data;
        } else {
            prev = cur;
        }
        cur = tmp;
    }
    return 0;
}
