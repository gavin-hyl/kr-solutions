/**
 * @file 3-4.c
 * @author Gavin Hua
 * @brief 3-4: In a two's complement number representation, our version of itoa
 * does not handle the largest negative number, that is, the value of n equal to
 * -(2^ * (wordsize-1)). Explain why not. 
 * 
 * ANS: The negative sign will not be stored in the array bounds.
 * 
 * Modify it to print that value correctly, regardless of the machine on which
 * it runs. 
 */

#include <string.h>
#include <stdio.h>

void itoa(int n, char s[]);
void reverse(char s[]);


int main()
{
    const int MAX_STR = 100;
    char s[MAX_STR];
    itoa(-100, s);
    printf(s);
}

/**
 * @brief Converts an integer into a string representation
 * 
 * @param n the integer
 * @param s the string representation
 */
void itoa(int n, char s[])
{
    int i=0, sign;
    
    if ((sign = n) < 0)
    {
        n = -n;
    }

    do 
    {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

/**
 * @brief Reverses a string in place
 * 
 * @param s the string
 */
void reverse(char s[])
{
    int c, i, j;

    for (i=0, j=strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}