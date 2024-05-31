/*
** EPITECH PROJECT, 2024
** MY_STRCPY
** File description:
** Function that copies a string into another.
*/
char *my_strcpy(char *dest, char const *src)
{
    int i = -1;

    do {
        i++;
        dest[i] = src[i];
    } while (dest[i] != '\0');
    return dest;
}
