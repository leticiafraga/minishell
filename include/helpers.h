/*
** EPITECH PROJECT, 2023
** HELPERS_H
** File description:
** Shell lib header
*/

#ifndef HELPERS_H
    #define HELPERS_H

int is_inhibitor(char c);
int is_not_space(char c);
int is_word_separator(char const *str, int i);
int is_new_word(char const *str, int i);
char *concat_strings(int num_strings, ...);
int is_special_char(char c);

#endif
