/**
 * @file 2-6.c
 * @author Gavin Hua
 * @brief 2-6: Write a function setbits(x,p,n,y) that returns x with the n bits
 * that begin at position p set to the rightmost n bits of y, leaving the other
 * bits unchanged. 
 */

#include <stdio.h>
#include <math.h>

int setbits(int, int, int, int);

int main()
{
    printf("%d", setbits(0b1000, 2, 1, 0b10));
    return 0;
}

/**
 * @brief Change some bits of x with some bits of y
 * 
 * @param x 
 * @param p 
 * @param n 
 * @param y 
 * @return x with the n bits that begin at position p set to the rightmost n 
 * bits of y
 */
int setbits(int x, int p, int n, int y)
{
    int y_n = y & (int)(pow(2, n) - 1);
    y_n <<= p - n;
    int x_mask = pow(2, n) - 1;
    x_mask <<= p - n;
    int val = (x & (~x_mask)) + y_n;
    return val;
}
