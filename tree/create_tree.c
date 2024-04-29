/*
** EPITECH PROJECT, 2024
** create_tree
** File description:
** Function that creates tree
*/

#include "../include/my.h"
#include "../include/helpers.h"
#include "../include/shell.h"
#include "../include/tree.h"
#include "../include/operators.h"
#include <stdlib.h>
#include <string.h>

static operator_t get_curr_operator(char *token)
{
    operator_t current_operator = STRING;
    int i = 0;

    while (OPERATORS[i] != 0) {
        if (strcmp(token, OPERATORS[i]) == 0)
            return i;
        i++;
    }
    return STRING;
}

static tree_t *create_node(char *command)
{
    tree_t *node = (tree_t *) malloc(sizeof(tree_t));
    operator_t type = get_curr_operator(command);

    node->data = command;
    node->type = type;
    node->left = 0;
    node->right = 0;
    return node;
}

static tree_t *add_item_tree(tree_t **root,
    char *cur_token, tree_t *prev_node)
{
    tree_t *node = create_node(cur_token);

    if ((*root) == 0) {
        *root = node;
        return node;
    }
    if (node->type >= prev_node->type) {
        node->left = prev_node->right;
        prev_node->right = node;
    } else {
        node->left = (*root);
        (*root) = node;
    }
    return node;
}

tree_t *create_tree(linked_list_t *tokens)
{
    linked_list_t *cur_pos = tokens;
    tree_t *root = NULL;
    tree_t *prev_node = NULL;
    char *cur_token;

    while (cur_pos != 0) {
        cur_token = cur_pos->data;
        prev_node = add_item_tree(&root, cur_token, prev_node);
        cur_pos = cur_pos->next;
    }
    return root;
}
