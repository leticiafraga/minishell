/*
** EPITECH PROJECT, 2023
** Organized
** File description:
** LINKED_LIST_H
*/

#ifndef LINKED_LIST_H
    #define LINKED_LIST_H
    #include "env_item.h"

typedef struct linked_list_s {
    env_item_h *data;
    struct linked_list_s *next;
} linked_list_t;

#endif /* LINKED_LIST_H */
