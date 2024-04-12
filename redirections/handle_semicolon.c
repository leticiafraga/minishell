/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

int handle_semicolon(char **args, linked_list_t **env,
    int *index, redirection_list_t *red)
{
    return run_prog(args[*index], env);
}

int handle_semicolon2(
    char *args, linked_list_t **env, cmd_opts_t *red)
{
    return run_prog(args, env);
}
