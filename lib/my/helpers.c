/*
** EPITECH PROJECT, 2023
** DAY 6
** File description:
** Helper functions
*/

int is_upcase(char c)
{
    return (c >= 'A' && c <= 'Z') ? 1 : 0;
}

int is_lowcase(char c)
{
    return (c >= 'a' && c <= 'z') ? 1 : 0;
}

int is_letter(char c)
{
    return (is_upcase(c) || is_lowcase(c)) ? 1 : 0;
}

int is_number(char c)
{
    return (c >= '0' && c <= '9') ? 1 : 0;
}
