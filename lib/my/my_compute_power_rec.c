/*
** EPITECH PROJECT, 2023
** MY_COMPUTE_POWER_REC
** File description:
** Recursive function that returns the first argument raised to
** the power p, where p is the second argument
*/
int my_compute_power_rec(int nb, int p)
{
    if (p == 0) {
        return 1;
    }
    if (p < 0 || nb == 0) {
        return 0;
    }
    return nb * my_compute_power_rec(nb, p - 1);
}
