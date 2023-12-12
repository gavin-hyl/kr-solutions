/*
    Write a private version of scanf analogous to minprintf from the previous section.
*/

#include <stdio.h>
#include <stdarg.h>

int minscanf(char *, ...);

int main(void)
{
    int sum, v;

    sum = 0;
    while (minscanf("%d", &v) == 1)
        printf("\t%d\n", sum += v);

    return 0;
}

int minscanf(char *fmt, ...)
{
    int converted = 1;
    va_list ap;
    int *ival;
    char *cval;

    va_start(ap, fmt);
    while (*fmt)
    {
        if (*fmt != '%')
        {
            putchar(*fmt);
            continue;
        }

        switch (*++fmt)
        {
        case 'i':
        case 'd':
            ival = va_arg(ap, int *);
            converted = scanf("%d", ival);
        case 'x':
            ival = va_arg(ap, int *);
            converted = scanf("%x", ival);
            break;
        case 'c':
            cval = va_arg(ap, char *);
            converted = scanf("%c", cval);
            break;
        default:
            break;
        }

        if (converted != 1)
        {
            return converted;
        }
        fmt++;
    }
    va_end(ap);
    return 1;
}