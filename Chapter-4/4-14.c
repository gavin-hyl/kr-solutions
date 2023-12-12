/**
 * @file 4-14.c
 * @author Gavin Hua
 * @brief 4-14:  Define a macro swap(t,x,y) that interchanges two arguments of
 * type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) \
    {                 \
        t temp;       \
        temp = x;     \
        x = y;        \
        y = temp;     \
    }

int main()
{
    int x, y;
    x = 10;
    y = 5;
    swap(int, x, y);
    printf("%d", x);
    return 0;
}
