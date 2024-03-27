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

int handle_pipe(char **args, linked_list_t **env, int *index)
{
    int mypipe[2];
    int p_read = 0;
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);
    int status;

    if (pipe(mypipe))
        return 84;
    handle_fork(p_read, mypipe[1], args[*index], env);
    p_read = mypipe[0];
    if (p_read != 0) {
        dup2(p_read, 0);
    }
    (*index += 1);
    status = handle_second(args[*index], env);
    wait(NULL);
    dup2(stdin_copy, 0);
    dup2(stdout_copy, 1);
    return status;
}
