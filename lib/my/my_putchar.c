/*
** EPITECH PROJECT, 2024
** MY_PUTCHAR
** File description:
** Puts a char
*/
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
