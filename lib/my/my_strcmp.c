/*
** EPITECH PROJECT, 2023
** MY_STRCMP
** File description:
** Reproduce the behavior of the strcmp function.
*/
static int compare_pos(char const *s1, char const *s2, int i)
{
    if (s1[i] > s2[i]) {
        return 1;
    }
    if (s1[i] < s2[i]) {
        return -1;
    }
    return 0;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    int compare;

    while (s1[i] != '\0' && s2[i] != '\0') {
        compare = compare_pos(s1, s2, i);
        if (compare != 0)
            return compare;
        i++;
    }
    compare = compare_pos(s1, s2, i);
    if (compare != 0)
        return compare;
    return 0;
}
