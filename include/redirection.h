/*
** EPITECH PROJECT, 2023
** redirection specifiers
** File description:
** Header file for redirection specifiers in minishell
*/

#ifndef REDIRECTION_H
    #define REDIRECTION_H
    #include "linked_list.h"

typedef enum sep_t {
    in1,
    in2,
    out1,
    out2,
    end,
    pipe_symbol
} sep_t;

typedef struct {
    char *cmd;
    sep_t symbol;
    int next_cmd_index;
    int prev_cmd_end;
} redirection_opts_t;

typedef struct {
    redirection_opts_t **arr;
    int cnt;
} redirection_list_t;

typedef struct {
    char *filename;
    sep_t symbol;
} redirection_opts2_t;

typedef struct {
    char *cmd;
    redirection_opts2_t *in;
    redirection_opts2_t *out;
} redirection_list2_t;

typedef struct {
    char **arr;
    int cnt;
} redirection_map_semic_t;

typedef struct global_state_t {
    linked_list_t **env;
    int global_pipe[2];
    redirection_list_t *red;
    redirection_list2_t *red_inner;
} global_state_t;

redirection_map_semic_t *sep_semicolon(char *line);
redirection_list2_t *get_cmds(char *semic);
redirection_list_t **get_pipes(redirection_map_semic_t *semic);

int free_seps(redirection_list_t *r);
int free_semic(redirection_map_semic_t *r);
void free_ptr_arr_content(char **args);

int handle_semicolon(char **args, linked_list_t **env, int *index,
    redirection_list_t *red);
int handle_semicolon2(
    char *args, linked_list_t **env, redirection_list2_t *red);
int handle_redir_stdout(
    char *args, linked_list_t **env, redirection_list2_t *red);
int handle_redir_stdout_append(
    char **args, linked_list_t **env,
    int *index, redirection_list_t *red);
int handle_redir_stdin(
    char *args, linked_list_t **env, redirection_list2_t *red);

int it_pipes(global_state_t *state);
#endif
