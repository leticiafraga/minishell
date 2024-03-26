/*
** EPITECH PROJECT, 2024
** clear_filename
** File description:
** clear_filename
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/my.h"

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
