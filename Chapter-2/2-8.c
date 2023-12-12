/**
 * @file 2-8.c
 * @author Gavin Hua
 * @brief Write a function rightrot(x,n) that returns the value of the integer x
 * rotated to the right by n positions.
 */

#include<math.h>
#include<stdio.h>

#define UINT_BITS sizeof(unsigned) * 8

unsigned rightrot(unsigned, unsigned);

int main()
{
    printf("%u", rightrot(1, 1));
}

/**
 * @brief Returns the value of the integer x rotated to the right by n positions.
 * 
 * @param x the integer
 * @param n the number of positions to rotate
 * @return the value of the integer x rotated to the right by n positions.
 */
unsigned rightrot(unsigned x, unsigned n){
    unsigned right_mask = pow(2,n)-1;
    unsigned right_x = x&right_mask;
    unsigned left_x = x&(~right_mask);
    unsigned val = (right_x << (UINT_BITS-n)) + (left_x >> n);
    return val;
}