/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include "include/my.h"
#include "include/shell.h"
#include "include/commands.h"

char **get_paths(char *name, linked_list_t *env)
{
    char *path_var = my_getenv(env, "PATH");
    char **paths;

    if (path_var == 0)
        return 0;
    paths = my_str_to_word_array_sep(path_var, ':');
    return paths;
}

static int handle_signaled(int status)
{
    if (WTERMSIG(status) == SIGSEGV)
        my_put_err("Segmentation fault");
    if (WTERMSIG(status) == SIGFPE)
        my_put_err("Floating exception");
    if (WTERMSIG(status) == SIGABRT)
        my_put_err("Abort");
    if (__WCOREDUMP(status)) {
        my_put_err(" (core dumped)\n");
    } else
        my_put_err("\n");
    return status;
}

int handle_status(int status)
{
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    if (WIFSIGNALED(status)) {
        return handle_signaled(status);
    }
    return 84;
}

static void free_vars(char **args, char **arr, char **paths)
{
    free_ptr_arr(args);
    free_ptr_arr(arr);
    free_ptr_arr(paths);
}

int handle_fork(char **args, char **arr, char **paths,
    linked_list_t *env)
{
    pid_t child;
    int status = 0;

    child = fork();
    if (child == 0) {
        handle_exec(args, arr, paths, env);
    } else
        waitpid(child, &status, 0);
    return status;
}

int run_prog(char *argv, linked_list_t **env)
{
    char **args = my_str_to_word_array(argv);
    int status;
    char **arr = getenv_arr(*env);
    char **paths = get_paths(args[0], *env);

    for (int i = 0; i < 5; i++) {
        if (commands[i] == 0) {
            status = handle_status(handle_fork(args, arr, paths, *env));
            break;
        }
        if (my_strcmp(args[0], commands[i]) == 0) {
            status = ((commands_fn[i])(args, env));
            break;
        }
    }
    free_vars(args, arr, paths);
    return status;
}
