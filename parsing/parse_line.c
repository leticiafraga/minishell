/*
** EPITECH PROJECT, 2024
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

static int it_backticks(char const *str, int i,
    linked_list_t **res)
{
    int beg = i + 1;

    append_to_list(res, strdup("`"));
    while (str[i + 1] != '`')
        i++;
    append_to_list(res, create_word(str, i, beg));
    return i + 2;
}

static int it_parentheses(char const *str, int i,
    linked_list_t **res)
{
    int beg = i + 1;

    append_to_list(res, strdup("("));
    while (str[i + 1] != ')')
        i++;
    append_to_list(res, create_word(str, i, beg));
    return i + 2;
}

static int it_special_char(char const *str, int i,
    linked_list_t **res)
{
    int beg = i;

    if (str[i] == '(')
        return it_parentheses(str, i, res);
    if (str[i] == '`')
        return it_backticks(str, i, res);
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

    if (line_error_handling(str))
        return 0;
    while (str[i] != '\0' && str[i] != '\n') {
        i = validate_pos(str, i, &tokens);
        if (i == -1)
            return 0;
    }
    return tokens;
}
