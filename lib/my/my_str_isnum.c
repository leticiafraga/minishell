/*
** EPITECH PROJECT, 2023
** MY_STR_ISNUM
** File description:
** Function that returns 1 if the string passed as parameter only
** contains digits and 0 otherwise
*/
#include "my.h"

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_number(str[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}
