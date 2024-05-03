/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** TREE_H
*/

#ifndef TREE_H
    #define TREE_H

typedef enum operator_t {
    OP_SEMICOLON,
    OP_OR,
    OP_AND,
    OP_PIPE,
    OP_IN1,
    OP_IN2,
    OP_OUT1,
    OP_OUT2,
    STRING,
} operator_t;

typedef struct tree_s {
    char *data;
    operator_t type;
    struct tree_s *right;
    struct tree_s *left;
} tree_t;

#endif /* TREE_H */
