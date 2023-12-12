/**
 * @file 5-2.c
 * @author Gavin Hua
 * @brief 5-2: Write getfloat, the floating-point analog of getint. 
 * What type does getfloat return as its function value?
 * 
 * ANS: int
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getfloat(float *);
int getch(void);
void ungetch(int c);

int main(void)
{
    float *flt;
    getfloat(flt);
    printf("%f", *flt);
    return 0;
}

/**
 * @brief Get next integer from input into its argument
 *
 * @param flt_p the pointer to store the float
 * @return -1 if EOF occurred, 0 if not a number, any positive integer otherwise
 */
int getfloat(float *flt_p)
{
    int c = 0, sign = 0;
    double pow = 1;
    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
    {
        c = getch();
    }

    for (*flt_p = 0; isdigit(c); c = getch())
    {
        *flt_p = 10 * *flt_p + (c - '0');
    }

    if (c == '.')
    {
        c = getch();
        for (; isdigit(c); c = getch())
        {
            *flt_p = 10 * *flt_p + (c - '0');
            pow *= 10;
        }
    }

    *flt_p *= sign;
    *flt_p /= pow;

    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

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