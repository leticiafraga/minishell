/*
** EPITECH PROJECT, 2023
** MINISHELL
** File description:
** Shell lib header
*/

#ifndef SHELL_H
    #define SHELL_H
    #include "linked_list.h"
    #include "redirection.h"

typedef struct cmd_state_t {
    char **cmdargs;
    char **arrenv;
    char **paths;
    linked_list_t **env;
} cmd_state_t;

int exec_prompt(int argc, char **argv, char **env);
int run_prog(char *argv, global_state_t *g_state);
int it_semicolons(global_state_t *state, char *line);
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
void *delete_in_list(linked_list_t **begin,
    void const *ref, int (*cmp_fct) ());
int add_item(char *key, char *value, linked_list_t **env);

void free_env(linked_list_t *list);
void free_ptr_arr(char **args);
void free_ptr_arr_content(char **args);
void free_vars(char **args, char **arr, char **paths);
void free_cmd_state(cmd_state_t *state);
char *clear_filename(char *prev);

void put_arg_err(char *arg, char *err);

char **get_paths(char *name, linked_list_t *env);

int handle_status(int status);

#endif
