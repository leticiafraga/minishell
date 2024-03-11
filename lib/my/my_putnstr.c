/*
** EPITECH PROJECT, 2023
** MY_PUTNSTR
** File description:
** Function that displays, one-by-one, n characters of a string.
*/
#include "my.h"
#include <unistd.h>

int my_putnstr(char const *str, int n)
{
    write(1, str, n);
    return 0;
}
