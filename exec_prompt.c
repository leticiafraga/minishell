/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/my.h"
#include "include/shell.h"
#include "include/linked_list.h"

static int free_seps(redirection_map *r)
{
    for (int i = 0; i < r->cnt; i++) {
        free(r->arr[i]);
    }
    free(r->arr);
    free(r);
}

int is_exit(char *line)
{
    return my_strcmp(line, "exit\n") == 0
        || my_strcmp(line, "exit") == 0;
}

int prompt(size_t bufsize, char *line, linked_list_t **env)
{
    int status = 0;
    size_t characters;
    int tty = isatty(0);

    while (1) {
        if (tty)
            my_putstr("$> ");
        characters = getline(&line, &bufsize, stdin);
        if (characters == -1)
            break;
        if (line[0] == '\n')
            continue;
        if (is_exit(line)) {
            status = 0;
            break;
        }
        status = run_prog(line, env);
    }
    return status;
}

int exec_prompt(int argc, char **argv, char **env)
{
    size_t bufsize = 500;
    size_t characters;
    int status = 84;
    char line[500];
    linked_list_t *listenv = getenv_list(env);

    if (argc == 1) {
        status = prompt(bufsize, line, &listenv);
    }
    free_env(listenv);
    return status;
}
