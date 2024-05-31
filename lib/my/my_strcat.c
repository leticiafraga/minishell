/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** my_strcat
*/
#include <string.h>

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int len = strlen(dest);

    while (src[i] != '\0') {
        dest[len + i] = src[i];
        i++;
    }
    dest[len + i] = '\0';
    return dest;
}
