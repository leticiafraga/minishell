/*
** EPITECH PROJECT, 2023
** MY_STRCAPITALIZE
** File description:
** Function that capitalizes the first letter of each word
*/
#include "my.h"

static void check_prev(char *str, int i)
{
    char prev = str[i - 1];

    if ((is_letter(prev) || is_number(prev)) && is_upcase(str[i]) == 1)
        str[i] += 32;
    if ((prev == ' ' || prev == '+' || prev == '-')
        && is_lowcase(str[i]) == 1)
        str[i] -= 32;
}

char *my_strcapitalize(char *str)
{
    int i = 0;

    if (is_lowcase(str[i]) == 1)
        str[i] -= 32;
    i++;
    while (str[i] != '\0') {
        check_prev(str, i);
        i++;
    }
    return str;
}
