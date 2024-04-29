/*
** EPITECH PROJECT, 2023
** redirection specifiers
** File description:
** Header file for redirection specifiers in minishell
*/

#ifndef REDIRECTION_H
    #define REDIRECTION_H
    #include "linked_list.h"
    #include "tree.h"

typedef enum sep_t {
    in1,
    in2,
    out1,
    out2,
    end,
    pipe_symbol
} sep_t;

typedef struct {
    char *filename;
    sep_t symbol;
} redirection_opts_t;

typedef struct {
    char *cmd;
    redirection_opts_t *in;
    redirection_opts_t *out;
} cmd_opts_t;

typedef struct {
    char **arr;
    int cnt;
} cmds_arr_t;

typedef struct global_state_t {
    linked_list_t **env;
    int global_pipe[2];
    cmds_arr_t *cmd;
    cmd_opts_t *red_inner;
    char *pwd;
} global_state_t;

cmds_arr_t *sep_semicolon(char *line);
cmd_opts_t *get_cmd_opts(char *semic);
cmds_arr_t **sep_pipes(cmds_arr_t *semic);

int free_cmds_arr(cmds_arr_t *r);
void free_ptr_arr_content(char **args);

int handle_semicolon(
    char *args, global_state_t *state);
int handle_redir_stdout(
    char *args, global_state_t *state);
int handle_redir_stdout_append(
    char *args, global_state_t *state);
int handle_redir_stdin(
    char *args, global_state_t *state);
int handle_redir_stdin_word(
    char *args, global_state_t *state);

int tree_redir_stdin(
    tree_t *root, global_state_t *state);
int tree_redir_stdin_word(
    tree_t *root, global_state_t *state);
int tree_redir_stdout(
    tree_t *root, global_state_t *state);
int tree_redir_stdout_append(
    tree_t *root, global_state_t *state);
int tree_pipe(
    tree_t *root, global_state_t *state);

int it_pipes(global_state_t *state);
#endif
