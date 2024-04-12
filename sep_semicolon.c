/*
** EPITECH PROJECT, 2024
** MINISHELL 2
** File description:
** Minishell 2
*/

#include "include/shell.h"
#include "include/my.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int cnt_semicolons(char *line)
{
    int len = my_strlen(line);
    int cnt = 0;

    for (int i = 0; i < len; i++) {
        if (line[i] == ';')
            cnt ++;
    }
    return cnt;
}

int it_line_semicolon(redirection_map_semic_t *red, char *line)
{
    char *newline = my_strdup(line);
    char *token = strtok(newline, ";");
    char *new;

    while (token != NULL) {
        new = my_strdup(token);
        red->arr[red->cnt] = new;
        red->cnt ++;
        token = strtok(NULL, ";");
    }
    free(newline);
}

redirection_map_semic_t *sep_semicolon(char *line)
{
    int len = my_strlen(line);
    redirection_map_semic_t *red = malloc(sizeof(redirection_map_semic_t));
    int cnt = cnt_semicolons(line);

    red->cnt = 0;
    red->arr = malloc(sizeof(char *) * (cnt + 1));
    it_line_semicolon(red, line);
    return red;
}
