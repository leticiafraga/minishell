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

    cr_assert_eq(r->cnt, 1);
    cr_assert_eq(r->arr[r->cnt - 1]->symbol, out2);
    cr_assert_eq(r->arr[r->cnt - 1]->prev_cmd_end, 6);
    cr_assert_eq(r->arr[r->cnt - 1]->next_cmd_index, 9);

    free_seps(r);
}

Test(find_seps_test, many_reds_test)
{
    char line[] = "ls -l; ls -l | wc -l >> cat file";
    redirection_map *r = find_seps(line);
    redirection_opts *opts;

    cr_assert_eq(r->cnt, 3);

    opts = r->arr[0];
    cr_assert_eq(opts->symbol, semic);
    cr_assert_eq(opts->prev_cmd_end, 4);
    cr_assert_eq(opts->next_cmd_index, 6);

    opts = r->arr[1];
    cr_assert_eq(opts->symbol, pipe_symbol);
    cr_assert_eq(opts->prev_cmd_end, 12);
    cr_assert_eq(opts->next_cmd_index, 14);

    opts = r->arr[2];
    cr_assert_eq(opts->symbol, out2);
    cr_assert_eq(opts->prev_cmd_end, 20);
    cr_assert_eq(opts->next_cmd_index, 23);

    free_seps(r);   
}

Test(find_seps_test, in_out_test)
{
    char line[] = "ls -l< ls -l > wc -l << cat file";
    redirection_map *r = find_seps(line);
    redirection_opts *opts;

    cr_assert_eq(r->cnt, 3);

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

