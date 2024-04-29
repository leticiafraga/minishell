/*
** EPITECH PROJECT, 2024
** MINISHELL 2
** File description:
** Minishell 2
*/

#include "../include/shell.h"
#include "../include/my.h"
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

void it_line_pipe(cmds_arr_t *pipes, char *line)
{
    char *newline = my_strdup(line);
    char *token = strtok(newline, "|");
    char *new;

    while (token != NULL) {
        new = my_strdup(token);
        pipes->arr[pipes->cnt] = new;
        pipes->cnt ++;
        token = strtok(NULL, "|");
    }
    free(newline);
}

cmds_arr_t **sep_pipes(cmds_arr_t *semicolons)
{
    cmds_arr_t *current_cmd;
    cmds_arr_t **pipes_list = malloc(
        sizeof(cmds_arr_t *) * (semicolons->cnt + 1));
    int cnt;

    for (int i = 0; i < semicolons->cnt; i++) {
        current_cmd = malloc(sizeof(cmds_arr_t));
        cnt = cnt_pipes(semicolons->arr[i]);
        current_cmd->cnt = 0;
        current_cmd->arr = malloc(sizeof(char *) * (cnt + 1));
        it_line_pipe(current_cmd, semicolons->arr[i]);
        pipes_list[i] = current_cmd;
    }
    return pipes_list;
}
