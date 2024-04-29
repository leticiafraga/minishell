/*
** EPITECH PROJECT, 2023
** parse_line
** File description:
** Function that parses line separating it in tokens
*/

#include "../include/my.h"
#include "../include/helpers.h"
#include "../include/shell.h"
#include <stdlib.h>
#include <string.h>

static char *create_word(char const *str, int end, int beg)
{
    char *word = malloc(sizeof(char) * (end - beg + 2));

    my_strncpy(word, &str[beg], end - beg + 1);
    return word;
}

static int it_outside_str(char const *str, int i,
    linked_list_t **res)
{
    int beg = i;

    while (str[i] != '\0' && is_end_of_cmd(str, i) == 0) {
        i++;
    }
    append_to_list(res, create_word(str, i, beg));
    return i + 1;
}

static int it_special_char(char const *str, int i,
    linked_list_t **res)
{
    int beg = i;

    if (str[i] == str[i + 1])
        i++;
    append_to_list(res, create_word(str, i, beg));
    return i + 1;
}

static int validate_pos(char const *str, int i,
    linked_list_t **res)
{
    if (is_special_char(str[i])) {
        return it_special_char(str, i, res);
    }
    if (is_new_word(str, i)) {
        return it_outside_str(str, i, res);
    }
    return i + 1;
}

linked_list_t *parse_line(char const *str)
{
    linked_list_t *tokens = 0;
    int i = 0;

    while (str[i] != '\0' && str[i] != '\n') {
        i = validate_pos(str, i, &tokens);
        if (i == -1)
            return 0;
    }
    return tokens;
}
