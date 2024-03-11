/*
** EPITECH PROJECT, 2023
** push_to_list
** File description:
** push_to_list
*/

#include "../include/linked_list.h"
#include <stdlib.h>

void push_to_list(linked_list_t **begin, void *data)
{
    linked_list_t *cur = *begin;
    linked_list_t *new = malloc(sizeof(linked_list_t));

    new->data = data;
    new->next = cur;
    *begin = new;
    begin = &new;
}
