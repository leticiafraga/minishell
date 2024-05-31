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
#include "include/helpers.h"
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

int exec_line(char *line, global_state_t *state)
{
    linked_list_t *list = parse_line(line);
    tree_t *tree;
    int status;

    if (list == 0){
        return 1;
    }
    tree = create_tree(list);
    status = run_tree(tree, state);
    free_list(list);
    free_tree(tree);
    return status;
}

int prompt(size_t bufsize, char *line, global_state_t *state)
{
    int status = 0;
    int characters;

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
        status = exec_line(line, state);
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
    char *init_pwd = my_getenv(listenv, "PWD");

    state.env = &listenv;
    if (init_pwd)
        state.pwd = strdup(init_pwd);
    else
        state.pwd = 0;
    if (argc == 1) {
        status = prompt(bufsize, line, &state);
    }
    if (state.pwd)
        free(state.pwd);
    free_env(listenv);
    return status;
}
