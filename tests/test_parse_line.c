#include "../include/shell.h"
#include "../include/helpers.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(parse_line_test, parses_correctly)
{
    linked_list_t *list = parse_line("ls | cat >>res");

    cr_assert_str_eq(list->data, "ls ");
    list = list->next;
    cr_assert_str_eq(list->data, "|");
    list = list->next;
    cr_assert_str_eq(list->data, "cat ");
    list = list->next;
    cr_assert_str_eq(list->data, ">>");
    list = list->next;
    cr_assert_str_eq(list->data, "res");
    list = list->next;

    free_list(list);
}

Test(parse_line_test, error_handling, .init=cr_redirect_stderr)
{
    linked_list_t *list;

    list = parse_line("ls \"aa || (cat ../cattest");
    cr_assert_eq(list, 0);
    list = parse_line("ls aa || (cat ../cattest'");
    cr_assert_eq(list, 0);
    list = parse_line("ls aa' || cat ../cattest");
    cr_assert_eq(list, 0);
    list = parse_line("ls aa || )cat ../cattest");
    cr_assert_eq(list, 0);
    list = parse_line("ls aa || (cat ../cattest");
    cr_assert_eq(list, 0);
    cr_assert_stderr_eq_str("Unmatched '\"'.\nUnmatched '''.\nUnmatched '''.\nToo many )'s.\nToo many ('s.\n");
}
