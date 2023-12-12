/**
 * @file 1-12.c
 * @author Gavin Hua
 * @brief 1-12: Write a program that prints its input one word per line.
 */

#include <stdio.h>

int main()
{
    char c, last_line_blank = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (!last_line_blank)
            {
                putchar('\n');
                last_line_blank = 1;
            }
        }
        else
        {
            putchar(c);
            last_line_blank = 0;
        }
    }
    return 0;
}