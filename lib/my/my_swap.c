/*
** EPITECH PROJECT, 2023
** MY_SWAP
** File description:
** Swaps the content of two integers, whose addresses are given as a parameter
*/
void my_swap(int *a, int *b)
{
    int content = *a;

    *a = *b;
    *b = content;
    return;
}
