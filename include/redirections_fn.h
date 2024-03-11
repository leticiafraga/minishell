/*
** EPITECH PROJECT, 2023
** redirection specifiers
** File description:
** Header file for redirection specifiers in minishell
*/

#ifndef REDIRECTION_FN_H
    #define REDIRECTION_FN_H
    #include "redirection.h"

int (*redirections_fn[]) (char *args, linked_list_t **env) = {
    &handle_semicolon,
    &handle_semicolon,
    &handle_semicolon,
    &handle_semicolon,
    &handle_semicolon,
    &handle_semicolon,
    &handle_semicolon,
    0
};

#endif
