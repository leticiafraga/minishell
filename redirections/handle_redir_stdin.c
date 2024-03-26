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

int handle_redir_stdin(char **args, linked_list_t **env, int *index)
{
    char *filename = clear_filename(args[*index + 1]);
    int fd = open(filename, O_RDONLY);
    int dupin = dup(STDIN_FILENO);
    int status;

    if (fd < 0) {
        free(filename);
        (*index) += 1;
        return 1;
    }
    close(STDIN_FILENO);
    dup(fd);
    close(fd);
    status = run_prog(args[*index], env);
    dup2(dupin, STDIN_FILENO);
    close(dupin);
    (*index) += 1;
    free(filename);
    return status;
}
