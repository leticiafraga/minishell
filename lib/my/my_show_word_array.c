/*
** EPITECH PROJECT, 2023
** MY_SHOW_WORD_ARRAY
** File description:
** Function that displays the content of an array of words
*/
#include <stdlib.h>
#include "my.h"

int my_show_word_array(char *const *tab)
{
    int i = 0;

    while (tab[i] != NULL) {
        my_putstr(tab[i]);
        my_putstr("\n");
        i++;
    }
    return 0;
}
