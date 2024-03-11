/*
** EPITECH PROJECT, 2023
** MY_COMPUTE_SQUARE_ROOT
** File description:
** Function that returns the square root (if it is a whole number)
** of the number given as argument.
*/
int my_compute_square_root(int nb)
{
    int res;

    for (int i = 0; i <= nb; i++) {
        res = i * i;
        if (res == nb) {
            return i;
        }
        if (res > nb) {
            return 0;
        }
    }
    return 0;
}
