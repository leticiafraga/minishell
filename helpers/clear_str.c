/*
** EPITECH PROJECT, 2024
** clear_str
** File description:
** clear_str
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int is_not_space(char c)
{
    return c != ' ' && c != '\n' && c != '\t';
}

static int is_new_word(char const *str, int i)
{
    return is_not_space(str[i]) == 1 &&
        i != 0 &&
        is_not_space(str[i - 1]) == 0;
}

char *clear_str(char *prev)
{
    int len = strlen(prev);
    char *new = malloc(sizeof(char) * len);
    int cnt = 0;

    for (int i = 0; i < len; i++) {
        if (is_new_word(prev, i)) {
            new[cnt] = ' ';
            cnt++;
        }
        if (is_not_space(prev[i])) {
            new[cnt] = prev[i];
            cnt++;
        }
    }
    new[cnt] = '\0';
    return new;
}
