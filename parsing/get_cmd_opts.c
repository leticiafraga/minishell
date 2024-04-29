/*
** EPITECH PROJECT, 2024
** MINISHELL 2
** File description:
** Minishell 2
*/

#include "../include/shell.h"
#include "../include/my.h"
#include <stdlib.h>
#include <stdio.h>

static int one_or_two_char(char *line, int i, char searched)
{
    if (line[i + 1] == searched)
        return 1;
    else
        return 0;
}

static int it_until_symbol(int start, char *line)
{
    int len = my_strlen(line);

    for (int i = start; i < len; i++) {
        switch (line[i]) {
            case '<':
                return i;
            case '>':
                return i;
            default:
                break;
        }
    }
    return len;
}

static char *my_strdup_part(int start, int end, char *line)
{
    int diff = end - start + 1;
    char *dest = malloc(sizeof(char) * diff);
    int cnt = 0;

    for (int i = start; i < end; i++) {
        dest[cnt] = line[i];
        cnt++;
    }
    dest[cnt] = '\0';
    return dest;
}

static int create_in(int i, cmd_opts_t *red, char *line)
{
    redirection_opts_t *new = malloc(sizeof(redirection_opts_t));
    int filename_end = 0;

    red->in = new;
    if (one_or_two_char(line, i, '<')) {
        new->symbol = in2;
        filename_end = it_until_symbol(i + 2, line);
        new->filename = my_strdup_part(i + 2, filename_end, line);
    } else {
        new->symbol = in1;
        filename_end = it_until_symbol(i + 1, line);
        new->filename = my_strdup_part(i + 1, filename_end, line);
    }
    return filename_end - 1;
}

static int create_out(int i, cmd_opts_t *red, char *line)
{
    redirection_opts_t *new = malloc(sizeof(redirection_opts_t));
    int filename_end = 0;

    red->out = new;
    if (one_or_two_char(line, i, '>')) {
        new->symbol = out2;
        filename_end = it_until_symbol(i + 2, line);
        new->filename = my_strdup_part(i + 2, filename_end, line);
    } else {
        new->symbol = out1;
        filename_end = it_until_symbol(i + 1, line);
        new->filename = my_strdup_part(i + 1, filename_end, line);
    }
    return filename_end - 1;
}

static void it_seps(int end_cmd, int len, cmd_opts_t *red, char *line)
{
    for (int i = end_cmd; i < len; i++) {
        switch (line[i]) {
            case '<':
                i = create_in(i, red, line);
                break;
            case '>':
                i = create_out(i, red, line);
                break;
            default:
                break;
        }
    }
}

static void it_line(cmd_opts_t *red, int len, char *line)
{
    int end_cmd = len;
    char *cmds_line;

    for (int i = 0; i < len; i++) {
        if (line[i] == '>' || line[i] == '<') {
            end_cmd = i;
            break;
        }
    }
    cmds_line = malloc(sizeof(char *) * (end_cmd + 1));
    my_strncpy(cmds_line, line, end_cmd);
    red->cmd = cmds_line;
    it_seps(end_cmd, len, red, line);
}

cmd_opts_t *get_cmd_opts(char *line)
{
    int len = my_strlen(line);
    cmd_opts_t *red = malloc(sizeof(cmd_opts_t));

    red->in = 0;
    red->out = 0;
    it_line(red, len, line);
    return red;
}
