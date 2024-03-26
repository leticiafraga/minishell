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

static int handle_fork(int mypipe[2], char **env)
{
    pid_t child = fork();
    int status = 0;

    if (child == 0) {
        dup2(mypipe[1], 1);
        return execvp(env[0], env);
    } else {
        dup2(mypipe[0], 0);
        waitpid(child, &status, 0);
        close(mypipe[1]);
    }
    return status;
}

int handle_pipe(char **args, linked_list_t **env, int *index)
{
    int mypipe[2];
    char **arrenv = getenv_arr(*env);

    if (pipe(mypipe))
        return 84;
    return handle_fork(mypipe, arrenv);
}
