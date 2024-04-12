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

static int cnt_pipes(char *line)
{
    int len = my_strlen(line);
    int cnt = 0;

    for (int i = 0; i < len; i++) {
        if (line[i] == '|')
            cnt ++;
    }
    return cnt;
}

int it_line_pipe(cmds_arr_t *red, char *line)
{
    char *newline = my_strdup(line);
    char *token = strtok(newline, "|");
    char *new;

    while (token != NULL) {
        new = my_strdup(token);
        red->arr[red->cnt] = new;
        red->cnt ++;
        token = strtok(NULL, "|");
    }
    free(newline);
}

cmds_arr_t **get_pipes(cmds_arr_t *semic)
{
    int len;
    cmds_arr_t *red;
    cmds_arr_t **pipes_list = malloc(sizeof(cmds_arr_t *));
    int cnt;

    for (int i = 0; i < semic->cnt; i++) {
        red = malloc(sizeof(cmds_arr_t));
        len = my_strlen(semic->arr[i]);
        cnt = cnt_pipes(semic->arr[i]);
        red->cnt = 0;
        red->arr = malloc(sizeof(char *) * (cnt + 1));
        it_line_pipe(red, semic->arr[i]);
        pipes_list[i] = red;
    }
    return pipes_list;
}
