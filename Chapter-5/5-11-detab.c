/**
 * @file 5-11-detab.c
 * @author Gavin Hua
 * @brief 5-11: Modify the program detab to accept a list of tab stops as
 * arguments. Use the default tab settings if there are no arguments.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TABSPACES 4
#define MAXTABS 100
#define MAXLINE 1000

int tabstops[MAXTABS];
int *tabstops_p = tabstops;

void add_space(int *);
int get_line(char *, int);

int main(int argc, char *argv[])
{
    int tab, cols;
    char line[MAXLINE];
    char *pline = line;

    printf((argc == 1) ? "Usage: substitute tabs for spaces.\n" : "");

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        if ((tab = atoi((*argv) + 1)) != 0)
        { // technically the +1 is not needed, and we can just use an abs
            *tabstops_p++ = tab;
        }
        else
        {
            printf("arguments must be nonnegative ints, dummy!");
            return 1;
        }
    }

    while (get_line(line, MAXLINE) != EOF)
    {
        pline = line;
        cols = 0;
        tabstops_p = tabstops;
        while (*pline)
        {
            if (*pline == '\t')
            {
                add_space(&cols);
                if (*tabstops_p == 0)
                {
                    while (cols % TABSPACES != 0)
                    {
                        add_space(&cols);
                    }
                }
                else
                {
                    while (cols < *tabstops_p)
                    {
                        add_space(&cols);
                    }
                }
                tabstops_p++;
            }
            else
            {
                printf("%c", *pline);
                cols++;
            }
            pline++;
        }
    }

    return 0;
}

/**
 * @brief Prints a space to stdout, and increments a column count
 *
 * @param c the column count
 */
void add_space(int *c)
{
    (*c)++; // ++ has higher precedence than *
    printf(" ");
}

/**
 * @brief Populates the tabstops array with the arithmetic sequence starting at
 * the current stop, and common difference v
 *
 * @param v the common difference
 */
int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    else if (c == EOF)
    {
        return -1;
    }
    s[i] = '\0';
    return i;
}