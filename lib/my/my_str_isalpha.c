/*
** EPITECH PROJECT, 2023
** MY_STR_ISALPHA
** File description:
** Function that returns 1 if the string passed as parameter only
** contains alphabetical characters and 0 if the string contains
** another type of character.
*/
#include "my.h"

int my_str_isalpha(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_letter(str[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}
