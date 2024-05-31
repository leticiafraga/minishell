/*
** EPITECH PROJECT, 2023
** parse_args
** File description:
** parse_args
*/
#include "../include/my.h"
#include <stdlib.h>
#include <string.h>

int is_inhibitor(char c)
{
    return c == '\'' || c == '"';
}

int is_special_char(char c)
{
    return c == ';' || c == '|' || c == '&' || c == '`'
        || c == '>' || c == '<' || c == '(' || c == ')'
        || c == '$';
}

int is_not_space(char c)
{
    return c != ' ' && c != '\n' && c != '\t';
}

int is_word_separator(char const *str, int i)
{
    return is_not_space(str[i]) == 1
        && (str[i + 1] == '\0'
            || is_not_space(str[i + 1]) == 0);
}

int is_new_word(char const *str, int i)
{
    return is_not_space(str[i]) == 1 &&
        (i == 0 || is_not_space(str[i - 1]) == 0
            || is_special_char(str[i - 1]));
}
