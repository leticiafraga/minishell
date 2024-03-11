/*
** EPITECH PROJECT, 2023
** MY_REVSTR
** File description:
** Function that reverses a string
*/
#include "my.h"

char *my_revstr(char *str)
{
    int len = my_strlen(str);
    char tmp;

    for (int i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
    return str;
}
