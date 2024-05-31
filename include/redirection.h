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

typedef struct global_state_t {
    linked_list_t **env;
    int global_pipe[2];
    char *pwd;
} global_state_t;

void free_ptr_arr_content(char **args);

int handle_semicolon(
    tree_t *root, global_state_t *state);
int handle_and(tree_t *root, global_state_t *state);
int handle_or(tree_t *root, global_state_t *state);
int handle_redir_stdin(
    tree_t *root, global_state_t *state);
int handle_redir_stdin_word(
    tree_t *root, global_state_t *state);
int handle_redir_stdout(
    tree_t *root, global_state_t *state);
int handle_redir_stdout_append(
    tree_t *root, global_state_t *state);
int handle_pipe(
    tree_t *root, global_state_t *state);
int handle_parentheses(tree_t *root, global_state_t *state);
int handle_backticks(tree_t *root, global_state_t *state);
int handle_dollar(tree_t *root, global_state_t *state);
#endif
