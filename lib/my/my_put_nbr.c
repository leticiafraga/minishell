/*
** EPITECH PROJECT, 2023
** MY_PUT_NBR
** File description:
** Function that displays the number given as a parameter
*/
#include "my.h"

static long int get_next(long int nb)
{
    long int next = nb % 10;

    nb = nb / 10;
    if (nb != 0) {
        get_next(nb);
    }
    my_putchar(next + '0');
    return 0;
}

int my_put_nbr(int nb)
{
    long int lg = nb;

    if (lg < 0) {
        my_putchar('-');
        lg = lg * -1;
    }
    get_next(lg);
    return 0;
}
