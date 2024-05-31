/*
** EPITECH PROJECT, 2024
** HELPERS_H
** File description:
** Shell lib header
*/

#ifndef HELPERS_H
    #define HELPERS_H
    #include "tree.h"
    #include "linked_list.h"

int is_inhibitor(char c);
int is_not_space(char c);
int is_word_separator(char const *str, int i);
int is_new_word(char const *str, int i);
char *concat_strings(int num_strings, ...);
int is_special_char(char c);
int is_end_of_cmd(char const *str, int i);
void print_tree(tree_t *root, int level);
void free_tree(tree_t *tree);
void free_list(linked_list_t *list);
char *clear_str(char *prev);

#endif
