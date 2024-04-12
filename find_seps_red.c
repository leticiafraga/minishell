/*
** EPITECH PROJECT, 2024
** MINISHELL 2
** File description:
** Minishell 2
*/

#include "include/shell.h"
#include "include/my.h"
#include <stdlib.h>
#include <stdio.h>

static int add_to_map(redirection_opts_t *new, redirection_list_t *red)
{
    red->arr[red->cnt] = new;
    red->cnt ++;
}

static int one_or_two_char(char *line, int i, char searched)
{
    if (line[i + 1] == searched)
        return 1;
    else
        return 0;
}

static int create_sep(sep_t s, int i, redirection_list_t *red)
{
    redirection_opts_t *new = malloc(sizeof(redirection_opts_t));

    new->symbol = s;
    new->next_cmd_index = i + 1;
    new->prev_cmd_end = i - 1;
    add_to_map(new, red);
}

static int cnt_cmds(char *line)
{
    int len = my_strlen(line);
    int cnt = 0;

    for (int i = 0; i < len; i++) {
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

static int create_in(int i, redirection_list_t *red, char *line)
{
    redirection_opts_t *new = malloc(sizeof(redirection_opts_t));

    if (one_or_two_char(line, i, '<')) {
        new->symbol = in2;
        new->next_cmd_index = i + 2;
        new->prev_cmd_end = i - 1;
        add_to_map(new, red);
        return 1;
    } else {
        create_sep(in1, i, red);
        return 0;
    }
}

static int create_out(int i, redirection_list_t *red, char *line)
{
    redirection_opts_t *new = malloc(sizeof(redirection_opts_t));

    if (one_or_two_char(line, i, '>')) {
        new->symbol = out2;
        new->next_cmd_index = i + 2;
        new->prev_cmd_end = i - 1;
        add_to_map(new, red);
        return 1;
    } else {
        create_sep(out1, i, red);
        return 0;
    }
}

static int it_line(redirection_list_t *red, int len, char *line)
{
    for (int i = 0; i < len; i++) {
        switch (line[i]) {
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

redirection_list_t *find_seps(char *line)
{
    int len = my_strlen(line);
    redirection_list_t *red = malloc(sizeof(redirection_list_t));
    int cnt = cnt_cmds(line);

    red->cnt = 0;
    red->arr = malloc(sizeof(redirection_opts_t *) * (cnt + 1));
    it_line(red, len, line);
    create_sep(end, len, red);
    return red;
}

static int get_cmds_text(redirection_list_t *r, char *line)
{
    int cur = 0;
    char *cur_pos = line;
    char *cmd = malloc(sizeof(char) * 500);
    int len;

    for (int i = 0; i < r->cnt; i++) {
        len = r->arr[i]->prev_cmd_end - cur + 1;
        cmd = my_strncpy(cmd, cur_pos, len);
        r->arr[i]->cmd = my_strdup(cmd);
        cur = r->arr[i]->next_cmd_index;
        cur_pos = line + cur;
    }
    free(cmd);
}

redirection_list_t *get_cmds(char *semic)
{
    redirection_list_t *r = malloc(sizeof(redirection_list_t));
    char *cmd = malloc(sizeof(char) * 100);
    int len;
    int cur = 0;
    char *cur_pos;
    char *line;

    line = semic;
    r = find_seps(line);
    get_cmds_text(r, line);
    free(cmd);
    return r;
}
