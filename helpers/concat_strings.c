/*
** EPITECH PROJECT, 2024
** shel
** File description:
** descr
*/
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <unistd.h>
/**
 * @brief concatinates known amount of strings
 *
 * @param num_strings string number
 * @return allocated, concatinated string
 */
char *concat_strings(int num_strings, ...)
{
    va_list args;
    size_t total_length = 0;
    char *result;
    size_t index = 0;
    const char *current_str;

    va_start(args, num_strings);
    for (int i = 0; i < num_strings; ++i) {
        total_length += strlen(va_arg(args, const char *));
    }
    result = malloc((total_length + 1) * sizeof(char));
    va_start(args, num_strings);
    for (int i = 0; i < num_strings; ++i) {
        current_str = va_arg(args, const char *);
        strcpy(result + index, current_str);
        index += strlen(current_str);
    }
    result[index] = '\0';
    va_end(args);
    return result;
}
