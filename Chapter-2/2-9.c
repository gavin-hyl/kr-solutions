// 
/**
 * @file 2-9.c
 * @author Gavin Hua
 * @brief In a two's complement number system, x &= (x-1) deletes the 
 * rightmost 1-bit in x. Explain why.
 * 
 * Suppose the least significant bit is 1, and the statement holds trivially. 
 * If the least significant bit is 0, then the subtraction carries over to the
 * next significant bit. The original bit is changed to 1, which does not 
 * affect x & (x-1). Proceed until the bit from which 1 is subtracted is 1, 
 * and apply the first statement.
 * 
 * Use this observation to write a faster version of bitcount (count 1 bits in x).
 */

#include <stdio.h>

int bitcount(unsigned);

int main()
{
    printf("%d", bitcount(0b101010101));
    return 0;
}

/**
 * @brief Counts the number of 1 bits in a number
 *
 * @param x the number
 * @return the number of 1 bits
 */
int bitcount(unsigned x)
{
    int count = 0;
    while (x != 0)
    {
        count++;
        x &= (x - 1);
    }
    return count;
}
