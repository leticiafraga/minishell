/*
** EPITECH PROJECT, 2023
** MY_STRUPCASE
** File description:
** Function that puts every letter of every word in it in uppercase
*/
#include "my.h"

char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_lowcase(str[i]) == 1)
            str[i] -= 32;
        i++;
    }
    return str;
}
