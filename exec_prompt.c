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

int is_exit(char *line)
{
    return my_strcmp(line, "exit\n") == 0
        || my_strcmp(line, "exit") == 0;
}

static void handle_tty(void)
{
    if (isatty(0))
        my_putstr("$> ");
}

int it_semicolons(linked_list_t **env, redirection_map_semic *s)
{
    redirection_map **r;
    redirection_map *red;
    int status = 0;

    r = get_pipes(s);
    for (int i = 0; i < s->cnt; i++) {
        red = r[i];
        status = handle_pipe(env, red);
        free_seps(red);
    }
    free(r);
    return status;
}

int prompt(size_t bufsize, char *line, linked_list_t **env)
{
    int status = 0;
    size_t characters;
    redirection_map_semic *s;

    while (1) {
        handle_tty();
        characters = getline(&line, &bufsize, stdin);
        if (characters == -1)
            break;
        if (line[0] == '\n')
            continue;
        if (is_exit(line)) {
            status = 0;
            break;
        }
        s = sep_semicolon(line);
        status = it_semicolons(env, s);
        free_semic(s);
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
