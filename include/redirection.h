/*
** EPITECH PROJECT, 2023
** redirection specifiers
** File description:
** Header file for redirection specifiers in minishell
*/

#ifndef REDIRECTION_H
    #define REDIRECTION_H

typedef enum {
    semic,
    pipe_symbol,
    in1,
    in2,
    out1,
    out2,
} sep;

typedef struct {
    sep symbol;
    int next_cmd_index;
} redirection_opts;

typedef struct {
    redirection_opts **arr;
    int cnt;
} redirection_map;

#endif
