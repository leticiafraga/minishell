/*
** EPITECH PROJECT, 2024
** getenv_list
** File description:
** getenv_list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/my.h"
#include "../include/shell.h"
#include "../include/linked_list.h"

env_item_t *getenv_item(char *value)
{
    env_item_t *item = malloc(sizeof(env_item_t));
    char *tok = strtok(value, "=");

    item->key = my_strdup(tok);
    tok = strtok(0, "\n");
    if (tok != 0)
        item->value = my_strdup(tok);
    else {
        item->value = malloc(sizeof(char));
        item->value[0] = '\0';
    }
    return item;
}

linked_list_t *getenv_list(char **arr)
{
    linked_list_t *env = 0;
    env_item_t *item;
    int i = 0;

    while (arr[i] != 0) {
        item = getenv_item(arr[i]);
        push_to_list(&env, item);
        i++;
    }
    return env;
}

static int cnt_list(linked_list_t *list)
{
    int cnt = 0;

    while (list != 0) {
        list = list->next;
        cnt++;
    }
    return cnt;
}

static char *get_dest(env_item_t *item)
{
    int len1;
    int len2;
    char *dest;

    len1 = strlen(item->key);
    len2 = strlen(item->value);
    dest = malloc(sizeof(char) * (len1 + len2 + 2));
    dest[0] = '\0';
    my_strcat(dest, item->key);
    my_strcat(dest, "=");
    my_strcat(dest, item->value);
    return dest;
}

char **getenv_arr(linked_list_t *list)
{
    int cnt = cnt_list(list);
    char **arr = malloc(sizeof(char *) * (cnt + 1));
    int i = 0;
    char *dest;

    while (list != 0) {
        dest = get_dest(list->data);
        arr[i] = dest;
        list = list->next;
        i++;
    }
    arr[i] = 0;
    return arr;
}
