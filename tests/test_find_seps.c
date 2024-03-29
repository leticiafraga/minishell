#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(find_seps_test, basic_test)
{
    char line[] = "ls -la >> cat file";
    redirection_map *r = find_seps(line);

    cr_assert_eq(r->cnt, 2);
    cr_assert_eq(r->arr[0]->symbol, out2);
    cr_assert_eq(r->arr[0]->prev_cmd_end, 6);
    cr_assert_eq(r->arr[0]->next_cmd_index, 9);

    cr_assert_eq(r->arr[1]->symbol, end);
    cr_assert_eq(r->arr[1]->prev_cmd_end, 17);

    free_seps(r);
}

Test(find_seps_test, many_reds_test)
{
    char line[] = "ls -l | wc -l >> cat file";
    redirection_map *r = find_seps(line);
    redirection_opts *opts;

    cr_assert_eq(r->cnt, 3);

    opts = r->arr[0];
    cr_assert_eq(opts->symbol, pipe_symbol);
    cr_assert_eq(opts->prev_cmd_end, 5);
    cr_assert_eq(opts->next_cmd_index, 7);

    opts = r->arr[1];
    cr_assert_eq(opts->symbol, out2);
    cr_assert_eq(opts->prev_cmd_end, 13);
    cr_assert_eq(opts->next_cmd_index, 16);

    free_seps(r);   
}

Test(find_seps_test, in_out_test)
{
    char line[] = "ls -l< ls -l > wc -l << cat file";
    redirection_map *r = find_seps(line);
    redirection_opts *opts;

    cr_assert_eq(r->cnt, 4);

    opts = r->arr[0];
    cr_assert_eq(opts->symbol, in1);
    cr_assert_eq(opts->prev_cmd_end, 4);
    cr_assert_eq(opts->next_cmd_index, 6);

    opts = r->arr[1];
    cr_assert_eq(opts->symbol, out1);
    cr_assert_eq(opts->prev_cmd_end, 12);
    cr_assert_eq(opts->next_cmd_index, 14);

    opts = r->arr[2];
    cr_assert_eq(opts->symbol, in2);
    cr_assert_eq(opts->prev_cmd_end, 20);
    cr_assert_eq(opts->next_cmd_index, 23);

    free_seps(r);   
}

Test(find_seps_test, different_spacing)
{
    char line[] = " ls -l|wc -l >>cat file";
    redirection_map *r = find_seps(line);
    redirection_opts *opts;

    cr_assert_eq(r->cnt, 3);

    opts = r->arr[0];
    cr_assert_eq(opts->symbol, pipe_symbol);
    cr_assert_eq(opts->prev_cmd_end, 5);
    cr_assert_eq(opts->next_cmd_index, 7);

    opts = r->arr[1];
    cr_assert_eq(opts->symbol, out2);
    cr_assert_eq(opts->prev_cmd_end, 12);
    cr_assert_eq(opts->next_cmd_index, 15);

    free_seps(r);   
}

