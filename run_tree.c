/*
** EPITECH PROJECT, 2024
** MINISHELL
** File description:
** Minishell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "include/my.h"
#include "include/shell.h"
#include "include/linked_list.h"

// NOTE: maybe it's better to define static const commands in the header
// and not use extern here. In my opinion it's a bit ambigious.
extern const char *commands[5];

// The same goes here
extern int (*commands_fn[]) (char **args, global_state_t *state);

int handle_fork(tree_t *node, global_state_t *state)
{
    pid_t child = fork();
    int status = 0;

    if (child == 0) {
        status = run_prog(node->data, state);
        exit(status);
    } else {
        waitpid(child, &status, 0);
    }
    return handle_status(status);
}

static int exec_cmd(tree_t *root, global_state_t *state)
{
    char **cmdargs = my_str_to_word_array(root->data);
    int status = 0;

    for (int i = 0; i < 5; i++) {
        if (commands[i] == 0) {
            status =
                handle_fork(root, state);
            break;
        }
        if (my_strcmp(cmdargs[0], commands[i]) == 0) {
            status = run_prog(root->data, state);
            break;
        }
    }
    free_ptr_arr(cmdargs);
    return status;
}

static int switch_redirections(tree_t *root, global_state_t *state)
{
    if (root == NULL)
        return 0;
    switch (root->type) {
    case OP_IN1:
        return handle_redir_stdin(root, state);
    case OP_IN2:
        return handle_redir_stdin_word(root, state);
    case OP_OUT1:
        return handle_redir_stdout(root, state);
    case OP_OUT2:
        return handle_redir_stdout_append(root, state);
    default:
        return 0;
    }
}

int run_tree(tree_t *root, global_state_t *state)
{
    if (root == NULL)
        return 0;
    switch (root->type) {
    case STRING:
        return exec_cmd(root, state);
    case OP_SEMICOLON:
        run_tree(root->left, state);
        return run_tree(root->right, state);
    case OP_PIPE:
        return handle_pipe(root, state);
    default:
        return switch_redirections(root, state);
    }
}
