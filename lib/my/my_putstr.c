/*
** EPITECH PROJECT, 2023
** MY_PUTSTR
** File description:
** Function that displays, one-by-one, the characters of a string.
*/
#include "my.h"

int my_putstr(char const *str)
{
    int i = 0;
    char c;

    do {
        c = str[i];
        if (c != '\0') {
            my_putchar(c);
        }
        i ++;
    } while (c != '\0');
    return 0;
}
