/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** COMMANDS_H
*/

#ifndef COMMANDS_H
    #define COMMANDS_H
    #include "shell.h"

char *commands[] = {
    "cd",
    "env",
    "setenv",
    "unsetenv",
    0
};

int (*commands_fn[]) (char **args, global_state_t *state) = {
    &handle_cd,
    &handle_env,
    &handle_setenv,
    &handle_unsetenv,
    0
};


#endif
