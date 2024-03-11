/*
** EPITECH PROJECT, 2023
** MY_STR_TO_WORD_ARRAY
** File description:
** Function that splits a string into words.
*/
#include "my.h"
#include <stdlib.h>

static int is_not_sep(char c, char sep)
{
    return c != sep && c != '\n';
}

static int is_sep(char const *str, int i, char sep)
{
    return is_not_sep(str[i], sep) == 1
        && (str[i + 1] == '\0'
            || is_not_sep(str[i + 1], sep) == 0);
}

static int is_new_word(char const *str, int i, char sep)
{
    return i == 0 ||
        (is_not_sep(str[i], sep) == 1 && is_not_sep(str[i - 1], sep) == 0);
}

static int count_words(char const *str, char sep)
{
    int i = 0;
    int words = 0;

    while (str[i] != '\0') {
        if (is_sep(str, i, sep) == 1) {
            words++;
        }
        i++;
    }
    return words;
}

char **my_str_to_word_array_sep(char const *str, char sep)
{
    int i = 0;
    int cur = 1;
    int words = 0;
    char **res;

    res = malloc(sizeof(char *) * (count_words(str, sep) + 1));
    while (str[i] != '\0') {
        if (is_new_word(str, i, sep))
            cur = 1;
        if (is_sep(str, i, sep) == 1) {
            res[words] = malloc(sizeof(char) * (cur + 1));
            my_strncpy(res[words], &str[i - cur + 1], cur);
            cur = 0;
            words += 1;
        }
        i++;
        cur++;
    }
    res[words] = 0;
    return res;
}
