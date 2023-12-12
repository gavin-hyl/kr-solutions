/**
 * @file 1-21.c
 * @author Gavin Hua
 * @brief 1-21: Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab.
 *
 * When either a tab or a single blank would suffice to reach a tab stop,
 * which should be given preference?
 *
 * The single blank.
 */

#include <stdio.h>
#include <ctype.h>

#define TAB_SPACING 4
#define MAX_LINE 100

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
        else if (c == ' ')
        {
            int n_spaces = 1;
            while ((c = getchar()) == ' ')
            {
                n_spaces++;
            }
            int to_next_stop = TAB_SPACING - (col % TAB_SPACING);
            if (to_next_stop >= n_spaces)
            {
                putchar('\t');
                n_spaces -= to_next_stop;
                int n_tabs = n_spaces / TAB_SPACING;
                n_spaces -= n_tabs * TAB_SPACING;
                for (int i = 0; i < n_tabs; i++)
                {
                    putchar('\t');
                }
            }
            for (int i = 0; i < n_spaces; i++)
            {
                putchar(' ');
            }
            putchar(c); // the while loop got an extra character
        }
        else
        {
            putchar(c);
            col++;
        }
    }
}