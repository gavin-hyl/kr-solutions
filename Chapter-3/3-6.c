/**
 * @file 3-6.c
 * @author Gavin Hua
 * @brief 3-6: Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.
 */

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(void)
{
    const int MAX_STR = 100;
    char s[MAX_STR];
    itoa(123456, s, 9);
    printf(s);
    return 0;
}

/**
 * @brief Converts an integer into a string representation
 * 
 * @param n the integer
 * @param s the string representation
 * @param w the minimum width of the string
 */
void itoa(int n, char s[], int w)
{
    int i = 0, sign;

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
    int n_blanks = w - strlen(s);
    while (n_blanks-- > 0)
    {
        s[i++] = ' ';
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

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}