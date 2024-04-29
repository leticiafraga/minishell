/*
** EPITECH PROJECT, 2023
** parse_args
** File description:
** parse_args
*/
#include "../include/my.h"
#include "../include/helpers.h"
#include <stdlib.h>
#include <string.h>

int is_end_of_cmd(char const *str, int i)
{
    return !is_special_char(str[i])
        && (str[i + 1] == '\0' || str[i + 1] == '\n'
            || is_special_char(str[i + 1]));
}
