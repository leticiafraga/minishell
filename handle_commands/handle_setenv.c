/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/shell.h"

int handle_setenv(char **args, linked_list_t **env)
{
    char *key = args[1];
    char *value;

    if (key == 0)
        return handle_env(args, env);
    value = args[2];
    if (value != 0 && args[3] != 0) {
        my_put_err("setenv: Too many arguments.\n");
        return 1;
    }
    if (!(my_str_isalphanum(key))) {
        my_put_err(
            "setenv: Variable name must contain alphanumeric characters.\n"
        );
        return 1;
    }
    add_item(key, value, env);
    return 0;
}
