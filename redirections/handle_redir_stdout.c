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

int handle_redir_stdout(
    char *args, linked_list_t **env, redirection_list2_t *red)
{
    char *filename = clear_filename(red->out->filename);
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    int dupout = dup(1);
    int status;

    close(1);
    dup(fd);
    close(fd);
    status = run_prog(args, env);
    dup2(dupout, 1);
    close(dupout);
    free(filename);
    return status;
}
