/* 
    In a two's complement number representation, our version of itoa does not handle the largest negative number,
    that is, the value of n equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
*/

#include <string.h>
#include <stdio.h>

#define MAXSTR 100

void itoa(int n, char s[]);
void reverse(char s[]);

char s[MAXSTR];

int main()
{
    itoa(-100, s);
    printf(s);
}

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