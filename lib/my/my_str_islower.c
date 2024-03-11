/*
** EPITECH PROJECT, 2023
** MY_STR_ISLOWER
** File description:
** Function that returns 1 if the string passed as parameter only
** contains lowercase alphabetical characters
*/
#include "my.h"

int my_str_islower(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_lowcase(str[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}
