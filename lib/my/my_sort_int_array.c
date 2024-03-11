/*
** EPITECH PROJECT, 2023
** MY_SORT_INT_ARRAY
** File description:
** function that sorts an integer array in ascending order,
** given a pointer to the first element of the array and its size.
*/
#include "my.h"

static void interior_it(int *array, int size, int i)
{
    for (int j = 0; j < size - i - 1; j ++) {
        if (array[j] > array[j + 1]) {
            my_swap(&array[j], &array[j + 1]);
        }
    }
}

void my_sort_int_array(int *array, int size)
{
    for (int i = 0; i < size; i++) {
        interior_it(array, size, i);
    }
}
