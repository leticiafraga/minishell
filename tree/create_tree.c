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

static void add_item_tree_before(tree_t *node,
    tree_t *cur, tree_t *prev, tree_t **root)
{
    node->left = cur;
    if (cur == *root)
        *root = node;
    else if (prev)
        prev->right = node;
}

static void add_item_tree(tree_t **root,
    char *cur_token)
{
    tree_t *node = create_node(cur_token);
    tree_t *cur = *root;
    tree_t *prev = 0;

    if ((*root) == 0) {
        *root = node;
        return;
    }
    while (1) {
        if (node->type < cur->type) {
            add_item_tree_before(node, cur, prev, root);
            break;
        }
        if (cur->right == 0) {
            cur->right = node;
            break;
        }
        prev = cur;
        cur = prev->right;
    }
}

tree_t *create_tree(linked_list_t *tokens)
{
    linked_list_t *cur_pos = tokens;
    tree_t *root = NULL;
    char *cur_token;

    while (cur_pos != 0) {
        cur_token = cur_pos->data;
        add_item_tree(&root, cur_token);
        cur_pos = cur_pos->next;
    }
    return root;
}
