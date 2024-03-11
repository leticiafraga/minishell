/*
** EPITECH PROJECT, 2023
** my_strncat
** File description:
** my_strncat
*/
#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int len = my_strlen(dest);

    while (src[i] != '\0' && i < nb) {
        dest[len] = src[i];
        len++;
        i++;
    }
    return dest;
}
