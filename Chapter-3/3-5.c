/**
 * @file 3-5.c
 * @author Gavin Hua
 * @brief 3-5: Write the function itob(n,s,b) that converts the integer n into
 * a base b character representation in the string s. In particular, 
 * itob(n,s,16) formats s as a hexadecimal integer in s.
 */

#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void)
{
    const int MAX_STR = 100;
    char s[MAX_STR];
    itob(1234567, s, 16);
    printf(s);
    return 0;
}

/**
 * @brief Converts an integer into a representation in another base
 * 
 * @param n the integer
 * @param s the string representation
 * @param b the base
 */
void itob(int n, char s[], int b)
{
    int i, sign;

    if ((sign = n) < 0)
    {
        n = -n;
    }
    i = 0;

    if (b<10 && b>0)
    {
        do 
        {
            s[i++] = n % b + '0';
        } while ((n /= b) > 0);

        if (sign < 0)
        {
            s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
    } 
    else if (b >= 10)
    {
        do
        {
            s[i++] = (n%b>9) ? ((n%b)-10+'A') : ((n%b)+'0');
        } while ((n=(n-n%b)/b) > 0);

        if (sign < 0)
        {
            s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
    }
    else
    {
        printf("b must be greater than 0");
    }
}

/**
 * @brief Reverses a string in place
 * 
 * @param s the string
 */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}