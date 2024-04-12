/*
** EPITECH PROJECT, 2024
** handle_semicolon
** File description:
** handle_semicolon
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

int handle_semicolon2(
    char *args, global_state_t *state)
{
    return run_prog(args, state);
}
