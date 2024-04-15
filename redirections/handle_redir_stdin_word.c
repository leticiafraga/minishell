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

static void handle_tty(void)
{
    if (isatty(0)) {
        printf("? ");
    }
}

static char *get_whole_str(global_state_t *state, char *word)
{
    size_t characters;
    size_t bufsize = 500;
    char *line = malloc(sizeof(char) * 500);
    char *str = malloc(sizeof(char) * 1000);

    str[0] = '\0';
    handle_tty();
    characters = getline(&line, &bufsize, stdin);
    while (cmp_line(line, word)) {
        my_strcat(str, line);
        handle_tty();
        characters = getline(&line, &bufsize, stdin);
    }
    free(line);
    return str;
}

int handle_redir_stdin_word(
    char *args, global_state_t *state)
{
    char *word = clear_filename(state->red_inner->in->filename);
    int status;
    char *str = get_whole_str(state, word);
    int mypipe[2];
    int dupin = dup(STDIN_FILENO);

    if (pipe(mypipe) < 0)
        return 84;
    close(STDIN_FILENO);
    dup(mypipe[0]);
    dprintf(mypipe[1], str);
    close(mypipe[1]);
    status = run_prog(args, state);
    dup2(dupin, STDIN_FILENO);
    close(dupin);
    close(mypipe[0]);
    free(word);
    free(str);
    return status;
}
