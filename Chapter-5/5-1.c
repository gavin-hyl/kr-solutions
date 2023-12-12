/**
 * @file 5-1.c
 * @author Gavin Hua
 * @brief 5-1：As written, getint treats a + or - not followed by a digit as a
 * valid representation of zero. Fix it to push such a character
 * back on the input.
 */

#include <stdio.h>
#include <ctype.h>

int getint(int *);
int getch(void);
void ungetch(int);

int main(int argc, char const *argv[])
{
    int *i;
    getint(i);
    printf("%d", *i + 1);
    return 0;
}

/**
 * @brief Get next integer from input into *int_p
 *
 * @param int_p the pointer to store the integer
 * @return -1 if EOF occurred, 0 if not a number, any positive integer otherwise
 */
int getint(int *int_p)
{
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    { // not a number
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
    {
        c = getch();
        if (c == ' ')
        {
            return 0;
        }
    }

    for (*int_p = 0; isdigit(c); c = getch())
    {
        *int_p = 10 * *int_p + (c - '0');
    }
    *int_p *= sign;

    if (c != EOF)
    {
        ungetch(c);
    }

    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

/**
 * @brief Get a (possibly pushed-back) character
 *
 * @return the character
 */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/**
 * @brief Push character back on input
 *
 * @param c the character
 */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }
}