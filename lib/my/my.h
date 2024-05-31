/*
** EPITECH PROJECT, 2024
** MY
** File description:
** My lib header
*/

#ifndef MY_H
    #define MY_H
int is_upcase(char c);
int is_lowcase(char c);
int is_letter(char c);
int is_number(char c);
void my_putchar(char c);
void my_put_err(char *str);
int my_putstr(char const *str);
int my_str_isalphanum(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strncpy(char *dest, char const *src, int n);
char **my_str_to_word_array(char const *str);
char **my_str_to_word_array_sep(char const *str, char sep_t);

#endif
