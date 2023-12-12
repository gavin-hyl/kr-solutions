/**
 * @file 1-9.c
 * @author Gavin Hua 
 * @brief 1-9: Write a program to copy its input to its output, 
 * replacing each string of one or more blanks by a single blank.
 */

#include <stdio.h>

int main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        if (c == ' ')
        {
            while ((c = getchar()) == ' ');
            putchar(c);
        }
    }
}