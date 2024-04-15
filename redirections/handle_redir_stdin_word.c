/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

static int cmp_line(char *line, char *word)
{
    char *cleared_line = clear_filename(line);
    int res = strcmp(line, word) != 0
        && strcmp(cleared_line, word) != 0;

    free(cleared_line);
    return res;
}

static char *get_whole_str(global_state_t *state, char *word)
{
    size_t characters;
    size_t bufsize = 500;
    char *line = malloc(sizeof(char) * 500);
    char *str = malloc(sizeof(char) * 1000);

    str[0] = '\0';
    characters = getline(&line, &bufsize, stdin);
    while (cmp_line(line, word)) {
        my_strcat(str, line);
        characters = getline(&line, &bufsize, stdin);
    }
    free(line);
    return str;
}

static char *get_newargs(char *str, char *args)
{
    int len = strlen(str) + strlen(args) + 3;
    char *newargs = malloc(sizeof(char) * len);

    strcpy(newargs, args);
    strcat(newargs, " '");
    strcat(newargs, str);
    strcat(newargs, "'");
    return newargs;
}

int handle_redir_stdin_word(
    char *args, global_state_t *state)
{
    char *word = clear_filename(state->red_inner->in->filename);
    int status;
    char *str = get_whole_str(state, word);
    char *newargs = get_newargs(str, args);

    status = run_prog(newargs, state);
    free(word);
    free(str);
    free(newargs);
    return status;
}
