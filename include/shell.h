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

int exec_prompt(int argc, char **argv, char **env);
int run_prog(char *argv, linked_list_t **env);
char *my_getenv(linked_list_t *env, char *var);
int try_paths(char **args, char **env, char **paths);
linked_list_t *getenv_list(char **arr);
char **getenv_arr(linked_list_t *list);

int handle_cd(char **args, linked_list_t **env);
int handle_setenv(char **args, linked_list_t **env);
int handle_env(char **args, linked_list_t **env);
void handle_exec(char **args, char **env, char **paths,
    linked_list_t *listenv);
int handle_unsetenv(char **args, linked_list_t **env);

void push_to_list(linked_list_t **begin, void *data);
void push_unique_to_list(linked_list_t **begin, env_item *data);
void *delete_in_list(linked_list_t **begin,
    void const *ref, int (*cmp_fct) ());
int add_item(char *key, char *value, linked_list_t **env);

void free_env(linked_list_t *list);
void free_ptr_arr(char **args);
void free_ptr_arr_content(char **args);
char *clear_filename(char *prev);

void put_arg_err(char *arg, char *err);

char **get_paths(char *name, linked_list_t *env);

#endif
