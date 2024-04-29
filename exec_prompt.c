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

static void handle_tty(global_state_t *state)
{
    if (isatty(0)) {
        printf("\033[33m$");
        if (state->pwd) {
            printf("%s", state->pwd);
        }
        printf("> ");
        printf("\033[0;0m");
    }
}

int it_semicolons(global_state_t *state, char *line)
{
    cmds_arr_t **r;
    int status = 0;
    cmds_arr_t *s = sep_semicolon(line);

    r = sep_pipes(s);
    for (int i = 0; i < s->cnt; i++) {
        state->cmd = r[i];
        status = it_pipes(state);
        free_cmds_arr(r[i]);
    }
    free(r);
    free_cmds_arr(s);
    return status;
}

int prompt(size_t bufsize, char *line, global_state_t *state)
{
    int status = 0;
    size_t characters;

    while (1) {
        handle_tty(state);
        characters = getline(&line, &bufsize, stdin);
        if (characters == -1)
            break;
        if (line[0] == '\n')
            continue;
        if (is_exit(line)) {
            status = 0;
            break;
        }
        status = it_semicolons(state, line);
    }
    return status;
}

int exec_prompt(int argc, char **env)
{
    size_t bufsize = 500;
    int status = 84;
    char line[500];
    linked_list_t *listenv = getenv_list(env);
    global_state_t state;

    state.env = &listenv;
    state.pwd = my_strdup(my_getenv(listenv, "PWD"));
    if (argc == 1) {
        status = prompt(bufsize, line, &state);
    }
    free(state.pwd);
    free_env(listenv);
    return status;
}
