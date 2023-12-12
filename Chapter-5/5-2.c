// Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getch(void);
void ungetch(int c);
int getfloat(float *);

int main(int argc, char const *argv[])
{
    float *flt;
    getfloat(flt);
    printf("%f", *flt);
    return 0;
}

int getfloat(float *fp)
{
    int c=0, sign=0;
    double pow = 1;
    while (isspace(c = getch()));

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

    for (*fp = 0; isdigit(c); c = getch())
    {
        *fp = 10 * *fp + (c - '0');
    }
    
    if (c == '.')
    {
        c = getch();
        for (; isdigit(c); c = getch())
        {
            *fp = 10 * *fp + (c - '0');
            pow *= 10;
        }
    }
        
    *fp *= sign;
    *fp /= pow;

    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

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