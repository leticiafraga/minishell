/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** TESTS_H
*/

#ifndef TESTS_H
    #define TESTS_H
#include "../include/linked_list.h"
#include "../include/shell.h"

linked_list_t *create_env();
global_state_t *create_state();
void free_state(global_state_t *state);

#endif /* TESTS_H */
