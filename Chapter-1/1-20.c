/**
 * @file 1-20.c
 * @author Gavin Hua
 * @brief 1-20: Write a program detab that replaces tabs in the input with the 
 * proper number of blanks to space to the next tab stop. Assume a fixed set of 
 * tab stops, say every n columns. 
 * Should n be a variable or a symbolic parameter?
 * 
 * It should be a symbolic parameter.
 */

#include <stdio.h>

#define TAB_SPACING 4

int main()
{
    int c, col = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            putchar(c);
            col = 0;
        }
        else if (c != '\t')
        {
            putchar(c);
            col++;
        }
        else
        {
            do 
            {
                col++;
                putchar(' ');
            } while (col % TAB_SPACING != 0);
        }
    }
}