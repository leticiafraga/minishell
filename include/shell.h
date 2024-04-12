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
int run_prog(char *argv, linked_list_t **env);
int it_semicolons(linked_list_t **env, char *line);
char *my_getenv(linked_list_t *env, char *var);
int try_paths(cmd_state_t *state);
linked_list_t *getenv_list(char **arr);
char **getenv_arr(linked_list_t *list);

int handle_cd(char **args, linked_list_t **env);
int handle_setenv(char **args, linked_list_t **env);
int handle_env(char **args, linked_list_t **env);
void handle_exec(cmd_state_t *state);
int handle_unsetenv(char **args, linked_list_t **env);

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
