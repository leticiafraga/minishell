/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "include/shell.h"

int main(int argc, char **argv, char **env)
{
    if (argv == 0)
        return 84;
    return exec_prompt(argc, env);
}
