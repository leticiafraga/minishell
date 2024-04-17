/*
** EPITECH PROJECT, 2023
** parse_args
** File description:
** Function that splits a string into words with ' ' as inhibitors.
*/
#include "../include/my.h"
#include "../include/helpers.h"
#include <stdlib.h>
#include <string.h>

static int parse_str(char const *str, int i)
{
    char delimiter = str[i];

    i++;
    while (str[i] != delimiter) {
        i++;
        if (str[i] == '\0') {
            return -1;
        }
    }
    return i;
}

static int count_words(char const *str)
{
    int i = 0;
    int words = 0;

    while (str[i] != '\0') {
        if (is_word_separator(str, i) == 1) {
            words++;
        }
        if (is_inhibitor(str[i])) {
            i = parse_str(str, i);
            words++;
        }
        if (i == -1)
            return -1;
        i++;
    }
    return words;
}

char *create_word(char const *str, int end, int beg)
{
    char *word = malloc(sizeof(char) * (end - beg + 2));

    my_strncpy(word, &str[beg], end - beg + 1);
    return word;
}

static int it_inside_str(char const *str, int i,
    char **res, int *word_cnt)
{
    int beg = i + 1;
    int delimiter = str[i];

    i += 1;
    while (str[i] != delimiter) {
        if (str[i] == '\0')
            return -1;
        i++;
    }
    res[*word_cnt] = create_word(str, i - 1, beg);
    (*word_cnt) += 1;
    return i;
}

static int it_outside_str(char const *str, int i,
    char **res, int *word_cnt)
{
    int beg = i;

    while (str[i] != '\0' && is_word_separator(str, i) == 0) {
            i++;
    }
    if (is_word_separator(str, i) == 1) {
        res[*word_cnt] = create_word(str, i, beg);
        (*word_cnt) += 1;
        return i + 1;
    }
        return i;
}

int validate_pos(char const *str, int i, char **res, int *word_cnt)
{
    if (is_inhibitor(str[i])) {
        i = it_inside_str(str, i, res, word_cnt);
        if (i == -1)
            return -1;
    } else if (is_new_word(str, i)) {
        i = it_outside_str(str, i, res, word_cnt);
    }
    return i + 1;
}

char **it_str(char const *str, int cnt)
{
    int i = 0;
    int word_cnt = 0;
    char **res = malloc(sizeof(char *) * (cnt + 1));

    while (str[i] != '\0' && str[i] != '\n') {
        i = validate_pos(str, i, res, &word_cnt);
        if (i == -1)
            return 0;
    }
    res[word_cnt] = 0;
    return res;
}

char **parse_args(char const *str)
{
    int i = 0;
    int beg = 0;
    int words = 0;
    char **res;
    int cnt = count_words(str);

    if (cnt == -1)
        return 0;
    return it_str(str, cnt);
}
