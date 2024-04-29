#include "../include/shell.h"
#include "../include/my.h"
#include "tests.h"
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(parse_line_test, parses_correctly)
{
    linked_list_t *list = parse_line("ls | cat >>res");

    cr_assert_str_eq(list->data, "ls");
    list = list->next;
    cr_assert_str_eq(list->data, "|");
    list = list->next;
    cr_assert_str_eq(list->data, "cat");
    list = list->next;
    cr_assert_str_eq(list->data, ">>");
    list = list->next;
    cr_assert_str_eq(list->data, "res");
    list = list->next;
}

Test(parse_line_test, with_inhibitor)
{
    linked_list_t *list = parse_line("ls; cat 'aaa;|'");

    cr_assert_str_eq(list->data, "ls");
    list = list->next;
    cr_assert_str_eq(list->data, ";");
    list = list->next;
    cr_assert_str_eq(list->data, "cat");
    list = list->next;
    cr_assert_str_eq(list->data, "aaa;|");
    list = list->next;
}

Test(parse_line_test, wrong_inhibitor)
{
    linked_list_t *list = parse_line("ls; cat 'aaa ");

    cr_assert_eq(list, 0);
}
