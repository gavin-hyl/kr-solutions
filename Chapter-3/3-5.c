/*
    Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s. 
    In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/

#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void itob(int n, char s[], int b);
void reverse(char s[]);

char s[MAXSTR];

int main(void)
{
    itob(1234567, s, 16);
    printf(s);
    return 0;
}

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

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}