/*
** EPITECH PROJECT, 2024
** MINISHELL 2
** File description:
** Minishell 2
*/

#include "include/shell.h"
#include "include/my.h"
#include <stdlib.h>

int one_or_two_char(char *line, int i, char searched)
{
    if (line[i + 1] == searched)
        return 1;
    else
        return 0;
}

static int cnt_cmds(char *line)
{
    int len = my_strlen(line);
    int cnt = 0;

    for (int i = 0; i < len; i++) {
        if (line[i] == ';' || line[i] == '|')
            cnt ++;
        switch (line[i]) {
            case '>':
                cnt ++;
                i += one_or_two_char(line, i, '>');
                break;
            case '<':
                cnt ++;
                i += one_or_two_char(line, i, '<');
                break;
            default:
                break;
        }
    }
    return cnt;
}

static int add_to_map(redirection_opts *new, redirection_map *red)
{
    red->arr[red->cnt] = new;
    red->cnt ++;
}

static int create_sep(sep s, int i, redirection_map *red)
{
    redirection_opts *new = malloc(sizeof(redirection_opts));

    new->symbol = s;
    new->next_cmd_index = i + 1;
    add_to_map(new, red);
}

static int create_in(int i, redirection_map *red, char *line)
{
    redirection_opts *new = malloc(sizeof(redirection_opts));

    if (one_or_two_char(line, i, '<')) {
        new->symbol = in2;
        new->next_cmd_index = i + 2;
        add_to_map(new, red);
        return 1;
    } else {
        new->symbol = in1;
        new->next_cmd_index = i + 1;
        add_to_map(new, red);
        return 0;
    }
}

static int create_out(int i, redirection_map *red, char *line)
{
    redirection_opts *new = malloc(sizeof(redirection_opts));

    if (one_or_two_char(line, i, '>')) {
        new->symbol = out2;
        new->next_cmd_index = i + 2;
        add_to_map(new, red);
        return 1;
    } else {
        new->symbol = out1;
        new->next_cmd_index = i + 1;
        add_to_map(new, red);
        return 0;
    }
}

int it_line(redirection_map *red, int len, char *line)
{
    for (int i = 0; i < len; i++) {
        switch (line[i]) {
            case ';':
                create_sep(semic, i, red);
                break;
            case '|':
                create_sep(pipe_symbol, i, red);
                break;
            case '<':
                i += create_in(i, red, line);
                break;
            case '>':
                i += create_out(i, red, line);
                break;
            default:
                break;
        }
    }
}

redirection_map *find_seps(char *line)
{
    int len = my_strlen(line);
    redirection_map *red = malloc(sizeof(redirection_map));
    int cnt = cnt_cmds(line);

    red->cnt = 0;
    red->arr = malloc(sizeof(redirection_opts *) * (cnt + 1));
    it_line(red, len, line);
    return red;
}
