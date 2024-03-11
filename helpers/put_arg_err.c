/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "../include/my.h"

void put_arg_err(char *arg, char *err)
{
    if (arg)
        my_put_err(arg);
    my_put_err(": ");
    my_put_err(err);
    my_put_err("\n");
}
