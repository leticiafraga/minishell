/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

static int is_not_space(char c)
{
    return c != ' ' && c != '\n' && c != '\t';
}

char *clear_filename(char *prev)
{
    int len = my_strlen(prev);
    char *new = malloc(sizeof(char) * len);
    int cnt = 0;

    for (int i = 0; i < len; i++) {
        if (is_not_space(prev[i])) {
            new[cnt] = prev[i];
            cnt++;
        }
    }
    new[cnt] = '\0';
    return new;
}

int handle_redir_stdout(char **args, linked_list_t **env, int *index)
{
    char *filename = clear_filename(args[*index + 1]);
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    int dupout = dup(1);
    int status;

    close(1);
    dup(fd);
    close(fd);
    status = run_prog(args[*index], env);
    dup2(dupout, 1);
    close(dupout);
    (*index) += 1;
    free(filename);
    return status;
}
