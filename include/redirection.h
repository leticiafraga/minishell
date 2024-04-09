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
    in1,
    in2,
    out1,
    out2,
    end,
    pipe_symbol
} sep;

typedef struct {
    char *cmd;
    sep symbol;
    int next_cmd_index;
    int prev_cmd_end;
} redirection_opts;

typedef struct {
    redirection_opts **arr;
    int cnt;
} redirection_map;

typedef struct {
    char **arr;
    int cnt;
} redirection_map_semic;

redirection_map *find_seps(char *line);
redirection_map_semic *sep_semicolon(char *line);
redirection_map *get_cmds(char *semic);
redirection_map **get_pipes(redirection_map_semic *semic);

int free_seps(redirection_map *r);
int free_semic(redirection_map_semic *r);
void free_ptr_arr_content(char **args);

int handle_semicolon(char **args, linked_list_t **env, int *index,
    redirection_map *red);
int handle_redir_stdout(char **args, linked_list_t **env, int *index,
    redirection_map *red);
int handle_redir_stdout_append(char **args, linked_list_t **env,
    int *index, redirection_map *red);
int handle_redir_stdin(char **args, linked_list_t **env, int *index,
    redirection_map *red);

int handle_pipe(linked_list_t **env, redirection_map *red);
#endif
