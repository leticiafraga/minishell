/*
** EPITECH PROJECT, 2023
** MY_STRSTR
** File description:
** Reproduce the behavior of the strstr function.
*/
#include <stddef.h>

static int compare_to_find(char *str, char const *to_find, int i)
{
    int j = 0;

    while (str[i] != '\0' && to_find[j] != 0) {
        if (str[i] != to_find[j]) {
            return 0;
        }
        j++;
        i++;
    }
    if (str[i] == '\0' && (to_find[j] != '\0'))
        return 0;
    return 1;
}

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;

    while (str[i] != '\0') {
        if (compare_to_find(str, to_find, i) == 1)
            return &str[i];
        i++;
    }
    return NULL;
}
