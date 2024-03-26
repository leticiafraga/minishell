/*
** EPITECH PROJECT, 2023
** redirection specifiers
** File description:
** Header file for redirection specifiers in minishell
*/

#ifndef REDIRECTION_H
    #define REDIRECTION_H
    #include "linked_list.h"

typedef enum sep {
    semicolon,
    pipe_symbol,
    in1,
    in2,
    out1,
    out2,
    end
} sep;

typedef struct {
    sep symbol;
    int next_cmd_index;
    int prev_cmd_end;
} redirection_opts;

typedef struct {
    redirection_opts **arr;
    int cnt;
} redirection_map;

redirection_map *find_seps(char *line);
int free_seps(redirection_map *r);
int handle_semicolon(char **args, linked_list_t **env, int *index);
int handle_pipe(char **args, linked_list_t **env, int *index);
int handle_redir_stdout(char **args, linked_list_t **env, int *index);

#endif
