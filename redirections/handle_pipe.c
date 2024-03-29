/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

static int handle_fork(int p_read, int p_write,
    char *args, linked_list_t **env)
{
    pid_t child = fork();
    int status = 0;
    char **cmdargs = my_str_to_word_array(args);
    char **arrenv = getenv_arr(*env);
    char **paths = get_paths(cmdargs[0], *env);

    if (child == 0) {
        if (p_read != 0) {
            dup2(p_read, 0);
            close(p_read);
        }
        dup2(p_write, 1);
        close(p_write);
        handle_exec(cmdargs, arrenv, paths, *env);
    } else {
        close(p_read);
        close(p_write);
    }
    free_ptr_arr(cmdargs);
    return status;
}

static int handle_second(char *args, linked_list_t **env)
{
    pid_t child = fork();
    int status = 0;
    char **cmdargs = my_str_to_word_array(args);
    char **arrenv = getenv_arr(*env);
    char **paths = get_paths(cmdargs[0], *env);

    if (child == 0) {
        handle_exec(cmdargs, arrenv, paths, *env);
    } else {
        waitpid(child, &status, 0);
    }
    free_ptr_arr(cmdargs);
    return status;
}

static int restore_copies(int copies[2])
{
    dup2(copies[0], 0);
    dup2(copies[1], 1);
}

static int handle_inner(char **args, linked_list_t **env, int *index,
    redirection_map *red)
{
    int mypipe[2];
    int p_read = 0;
    int status;

    while (red->arr[*index]->symbol == pipe_symbol) {
        if (pipe(mypipe))
            return 84;
        handle_fork(p_read, mypipe[1], args[*index], env);
        p_read = mypipe[0];
        if (p_read != 0) {
            dup2(p_read, 0);
        }
        (*index += 1);
    }
    status = handle_second(args[*index], env);
    wait(NULL);
    return status;
}

int handle_pipe(char **args, linked_list_t **env, int *index,
    redirection_map *red)
{
    int copies[2] = { dup(STDIN_FILENO), dup(STDOUT_FILENO) };
    int status = handle_inner(args, env, index, red);

    restore_copies(copies);
    return status;
}
