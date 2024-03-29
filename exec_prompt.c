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
#include "include/redirections_fn.h"

static int free_vars(redirection_map *red, char **cmds)
{
    free_seps(red);
    free_ptr_arr_content(cmds);
}

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

static int run_cmds(linked_list_t **env,
    redirection_map *red, char **cmds)
{
    int status = 0;
    sep symbol;

    for (int i = 0; i < red->cnt; i++) {
        symbol = red->arr[i]->symbol;
        status = (redirections_fn[symbol])(cmds, env, &i, red);
    }
    return status;
}

int run_all(linked_list_t **env, redirection_map_semic *s)
{
    redirection_map **r;
    redirection_map *red;
    char **cmds;
    int status;

    r = get_cmds(s);
    for (int i = 0; i < s->cnt; i++) {
        red = r[i];
        cmds = malloc(sizeof(char *) * (red->cnt + 1));
        for (int i = 0; i < red->cnt; i++) {
            cmds[i] = my_strdup(red->arr[i]->cmd);
        }
        cmds[red->cnt] = 0;
        status = run_cmds(env, red, cmds);
        free_vars(red, cmds);
    }
    free(r);
    free(cmds);
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
        status = run_all(env, s);
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
