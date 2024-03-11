#include "../include/linked_list.h"
#include "../include/my.h"
#include <stdlib.h>

linked_list_t *create_env()
{
    linked_list_t *env = malloc(sizeof(linked_list_t));
    env->data = malloc(sizeof(env_item));
    env->data->key = my_strdup("PATH");
    env->data->value = my_strdup("/usr/bin");
    return env;
}
