/**
 * @file 1-8.c
 * @author Gavin Hua 
 * @brief 1-8: Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

int main()
{
    int c = 0, spaces = 0, tabs = 0, newlines = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            spaces++;
        }
        else if (c == '\t')
        {
            tabs++;
        }
        else if (c == '\n')
        {
            newlines++;
        }
    }
    printf("%d spaces, %d tabs, %d newlines\n", spaces, tabs, newlines);
}