/**
 * @file 7-3.c
 * @author Gavin Hua
 * @brief Exercise 7-3.
 *
 * Revise minprintf to handle more of the other facilities of printf.
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXEXPAND 100

void my_printf(char *fmt, ...);
void pad(int n);

int main(int argc, char const *argv[])
{
    my_printf(":%%:\n");
    my_printf(":%d:\n", 12345);
    my_printf(":%f:\n", 12.345);
    my_printf(":%s:\n", "12345");
    my_printf(":%10.3f:\n", 12.345); // floating point precision doesn't quite work, but oh well
    my_printf(":%10.3s:\n", "12345");
    my_printf(":%-10.3s:\n", "12345");
    my_printf(":%s %s:\n", "12345", "abcde");
    return 0;
}

/**
 * @brief Minimal printf with variable argument list
 *
 * @param fmt the format string
 * @param ... variable length argument list
 */
void my_printf(char *fmt, ...)
{
    va_list argp;
    char *sval, c, temp[MAXEXPAND], *ptemp, out[MAXEXPAND];
    int ival;
    double dval;

    temp[0] = '\0';
    va_start(argp, fmt);
    while (c = *fmt)
    {
        fmt++;
        ptemp = temp;
        if (c != '%')
        {
            putchar(c);
            continue;
        }

        c = *fmt++;
        int precision = 0, padding = 0, pad_right = 0;
        if (c == '-')
        {
            pad_right = 1;
            c = *fmt++;
        }
        if (isdigit(c))
        {
            padding = c - '0';
            while (isdigit(c = *fmt++))
            {
                padding = 10 * padding + c - '0';
            }
        }
        if (c == '.')
        {
            while (isdigit(c = *fmt++))
            {
                precision = 10 * precision + c - '0';
            }
        }

        switch (c)
        {
        case 'd':
            ival = va_arg(argp, int);
            sprintf(temp, "%d", ival);
            break;
        case 'f':
            dval = va_arg(argp, double);
            sprintf(temp, "%f", dval);
            break;
        case 's':
            sval = va_arg(argp, char *);
            strcpy(temp, sval);
            break;
        default:
            putchar(c);
            break;
        }

        if (temp[0] != '\0')
        {
            if (precision != 0)
            {
                strncpy(out, temp, precision);
                out[precision] = '\0';
            }
            else
            {
                strcpy(out, temp);
            }

            if (padding != 0 && strlen(out) < padding)
            {
                int npads = padding - strlen(out);
                if (pad_right)
                {
                    printf(out);
                    pad(npads);
                }
                else
                {
                    pad(npads);
                    printf(out);
                }
            }
            else
            {
                printf(out);
            }
        }
    }
    va_end(argp);
}

/**
 * @brief Pads n blanks to the output
 *
 * @param n the number of blanks to pad
 */
void pad(int n)
{
    while (n-- > 0)
    {
        putchar(' ');
    }
}
