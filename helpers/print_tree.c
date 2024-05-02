/*
** EPITECH PROJECT, 2024
** print_tree
** File description:
** print_tree
*/

#include <stdio.h>
#include "../include/tree.h"


void print_tree(tree_t *root, int level)
{
    if (root == NULL) {
        return;
    }
    printf("Data: %s, Type: %d, Level %d\n", root->data, root->type, level);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}
