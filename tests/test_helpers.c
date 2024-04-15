#include "../include/linked_list.h"
#include "../include/my.h"
#include "../include/shell.h"
#include <stdlib.h>

linked_list_t *create_env()
{
    linked_list_t *env = malloc(sizeof(linked_list_t));
    env->data = malloc(sizeof(env_item_t));
    env->data->key = my_strdup("PATH");
    env->data->value = my_strdup("/usr/bin");
    return env;
}

global_state_t *create_state()
{
    global_state_t *state = malloc(sizeof(global_state_t));
    linked_list_t **env_ptr = malloc(sizeof(linked_list_t*));
    *env_ptr = create_env();
    state->env = env_ptr;
    return state;
}

void free_state(global_state_t *state)
{
    linked_list_t *env = *(state->env);
    free(env->data->key);
    free(env->data->value);
    free(env->data);
    free(env);
    free(state->env);
    free(state);
}
