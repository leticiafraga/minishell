/*
** EPITECH PROJECT, 2024
** PUT_ERR
** File description:
** Puts error message
*/

#include <unistd.h>
#include <string.h>

void my_put_err(char *str)
{
    int len = strlen(str);

    write(2, str, len);
}
