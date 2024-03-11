/*
** EPITECH PROJECT, 2023
** Organized
** File description:
** COMMANDS_H
*/

#ifndef COMMANDS_H
    #define COMMANDS_H
    #include "shell.h"

const char *commands[] = {
    "cd",
    "env",
    "setenv",
    "unsetenv",
    0
};

int (*commands_fn[]) (char **args, linked_list_t **env) = {
    &handle_cd,
    &handle_env,
    &handle_setenv,
    &handle_unsetenv,
    0
};


#endif
