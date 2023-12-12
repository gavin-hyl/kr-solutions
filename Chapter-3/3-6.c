/**
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#include <string.h>

#define MAXSTR 100

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(void){
    char s[MAXSTR];
    itoa(123456, s, 9);
    printf(s);
    return 0;
}

void itoa(int n, char s[], int w)
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

    while (strlen(s) < w)
    {
        char temp[MAXSTR];
        sprintf(temp, " %s", s);
        strcpy(s, temp);
    }
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}