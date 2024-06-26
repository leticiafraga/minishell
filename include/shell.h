/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Shell lib header
*/

#ifndef SHELL_H
    #define SHELL_H
    #include "linked_list.h"
    #include "tree.h"
    #include "redirection.h"

typedef struct cmd_state_t {
    char **cmdargs;
    char **arrenv;
    char **paths;
    linked_list_t **env;
} cmd_state_t;

int exec_prompt(int argc, char **env);
int exec_line(char *line, global_state_t *state);
int line_error_handling(char const *line);
int run_prog(char *argv, global_state_t *g_state);
char *my_getenv(linked_list_t *env, char *var);
int try_paths(cmd_state_t *state);
linked_list_t *getenv_list(char **arr);
char **getenv_arr(linked_list_t *list);

cmd_state_t *getcmd_state(char *args, linked_list_t **env);

int handle_cd(char **args, global_state_t *state);
int handle_setenv(char **args, global_state_t *state);
int handle_env(char **args, global_state_t *state);
void handle_exec(cmd_state_t *state);
int handle_unsetenv(char **args, global_state_t *state);

void push_to_list(linked_list_t **begin, void *data);
void push_unique_to_list(linked_list_t **begin, env_item_t *data);
void append_to_list(linked_list_t **begin, void *data);
void *delete_in_list(linked_list_t **begin,
    void const *ref, int (*cmp_fct) ());
void add_item(char *key, char *value, linked_list_t **env);
linked_list_t *clone_list_env(linked_list_t **begin);

tree_t *create_tree(linked_list_t *tokens);
int run_tree(tree_t *root, global_state_t *state);

void free_env(linked_list_t *list);
void free_ptr_arr(char **args);
void free_ptr_arr_content(char **args);
void free_cmd_state(cmd_state_t *state);
char *clear_filename(char *prev);

void put_arg_err(char *arg, char *err);

char **get_paths(linked_list_t *env);
char **parse_args(char const *str);
linked_list_t *parse_line(char const *str);

int handle_status(int status);


#endif
