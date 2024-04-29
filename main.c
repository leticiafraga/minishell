/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include "include/shell.h"

int main(int argc, char **argv, char **env)
{
    return exec_prompt(argc, env);
}
