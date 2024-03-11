/*
** EPITECH PROJECT, 2023
** MY_STR_ISUPPER
** File description:
** Function that returns 1 if the string passed as parameter only
** contains uppercase alphabetical characters
*/
#include "my.h"

int my_str_isupper(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_upcase(str[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}
