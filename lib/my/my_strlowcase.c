/*
** EPITECH PROJECT, 2023
** MY_STRLOWCASE
** File description:
** Function that puts every letter of every word in it in lowercase
*/
#include "my.h"

char *my_strlowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_upcase(str[i]) == 1)
            str[i] += 32;
        i++;
    }
    return str;
}
