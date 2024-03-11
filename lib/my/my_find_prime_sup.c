/*
** EPITECH PROJECT, 2023
** MY_FIND_PRIME_SUP
** File description:
** Function that returns the smallest prime number that is
** greater than, or equal to, the number given as a parameter
*/
#include "my.h"

int my_find_prime_sup(int nb)
{
    int found = 0;

    while (found == 0) {
        if (my_is_prime(nb) == 1) {
            found = nb;
        }
        nb ++;
    }
    return found;
}
