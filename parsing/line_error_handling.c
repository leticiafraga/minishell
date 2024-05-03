/*
** EPITECH PROJECT, 2024
** line_error_handling
** File description:
** Function that checks if the line is valid
*/

#include "../include/my.h"
#include "../include/helpers.h"
#include "../include/shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int it_inhibitors(char const *str, int i)
{
    int delimiter = str[i];

    i++;
    while (str[i] != delimiter) {
        if (str[i] == '\0' || str[i] == '\n') {
            dprintf(2, "Unmatched '%c'.\n", delimiter);
            return -1;
        }
        i++;
    }
    return i;
}

static int it_parentheses(char const *str, int i)
{
    while (str[i] != ')') {
        if (str[i] == '\0') {
            dprintf(2, "Too many ('s.\n");
            return -1;
        }
        i++;
    }
    return i;
}

static int validate_parentheses_inner(char const *str, int i)
{
    if (str[i] == '(')
        return it_parentheses(str, i);
    else {
        dprintf(2, "Too many )'s.\n");
        return -1;
    }
}

static int validate_parentheses(char const *line)
{
    int i = 0;

    while (line[i] != '\0' && line[i] != '\n') {
        if (line[i] == '(' || line[i] == ')') {
            i = validate_parentheses_inner(line, i);
        }
        if (i == -1)
            return 1;
        i++;
    }
    return 0;
}

static int validate_inhibitors(char const *line)
{
    int i = 0;

    while (line[i] != '\0' && line[i] != '\n') {
        if (is_inhibitor(line[i]) || line[i] == '`') {
            i = it_inhibitors(line, i);
        }
        if (i == -1)
            return 1;
        i++;
    }
    return 0;
}

int line_error_handling(char const *line)
{
    if (validate_inhibitors(line) == 1
        || validate_parentheses(line) == 1)
        return 1;
    return 0;
}
