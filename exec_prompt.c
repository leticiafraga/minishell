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

int it_semicolons(linked_list_t **env, char *line)
{
    cmds_arr_t **r;
    int status = 0;
    global_state_t state;
    cmds_arr_t *s = sep_semicolon(line);

    state.env = env;
    r = sep_pipes(s);
    for (int i = 0; i < s->cnt; i++) {
        state.cmd = r[i];
        status = it_pipes(&state);
        free_cmds_arr(r[i]);
    }
    free(r);
    free_cmds_arr(s);
    return status;
}

int prompt(size_t bufsize, char *line, linked_list_t **env)
{
    int status = 0;
    size_t characters;

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
        status = it_semicolons(env, line);
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
