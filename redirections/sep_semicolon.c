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

static void it_line_semicolon(cmds_arr_t *semic, char *line)
{
    char *newline = my_strdup(line);
    char *token = strtok(newline, ";");
    char *new;

    while (token != NULL) {
        new = my_strdup(token);
        semic->arr[semic->cnt] = new;
        semic->cnt ++;
        token = strtok(NULL, ";");
    }
    free(newline);
}

cmds_arr_t *sep_semicolon(char *line)
{
    cmds_arr_t *semicolons = malloc(sizeof(cmds_arr_t));
    int cnt = cnt_semicolons(line);

    semicolons->cnt = 0;
    semicolons->arr = malloc(sizeof(char *) * (cnt + 1));
    it_line_semicolon(semicolons, line);
    return semicolons;
}
