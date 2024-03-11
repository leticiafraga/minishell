/*
** EPITECH PROJECT, 2023
** MY_STRNCMP
** File description:
** Reproduce the behavior of the strncmp function.
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;
    int compare;

    while (i < n) {
        if (s1[i] != s2[i])
            return (unsigned char) s1[i] - (unsigned char) s2[i];
        if (s1[i] == '\0')
            return 0;
        i++;
    }
    return 0;
}
