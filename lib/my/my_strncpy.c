/*
** EPITECH PROJECT, 2023
** MY_STRNCPY
** File description:
** Function that copies n characters from a string into another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int c;
    int i = 0;

    if (n <= 0)
        return dest;
    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
