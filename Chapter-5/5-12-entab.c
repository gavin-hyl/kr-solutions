/**
 * @file 5-12-entab.c
 * @author Gavin Hua
 * @brief 5-12: Extend entab to accept the shorthand "-m +n" to mean tab stops
 * every n columns, starting at column m. Choose convenient (for the user)
 * default behavior.
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
int extrp_flag = 0;

void extrapolate_tabstops(int);
int get_line(char *, int);

int main(int argc, char *argv[])
{
    int arg, cols, spaces;
    char line[MAXLINE];
    char *line_p = line;

    extrapolate_tabstops(TABSPACES);

    printf((argc == 1) ? "Usage: substitute spaces for tabs.\n" : "");

    while (*++argv != NULL)
    { // construct the tabstop array
        arg = atoi((*argv) + 1);
        if (arg == 0)
        {
            printf("arguments must be nonnegative ints, dummy!");
            return 1;
        }
        arg = atoi((*argv) + 1);
        if ((*argv)[0] == '-')
        {
            while (*tabstops_p < arg && extrp_flag)
            {
                tabstops_p++;
            }
            *tabstops_p++ = arg;
            extrapolate_tabstops(TABSPACES);
            extrp_flag = 0;
        }
        else if ((*argv)[0] == '+')
        {
            extrp_flag = 1;
            extrapolate_tabstops(arg);
        }
        else
        {
            printf("arguments should be preceded by either a '-' or '+'.\n");
            return 1;
        }
    }

    for (int i = 0; i < MAXTABS; i++)
    {
        printf("%d ", tabstops[i]);
    }

    while (get_line(line, MAXLINE) != EOF)
    { // transform all suitable lengths of spaces into tabs
        line_p = line;
        cols = spaces = 0;
        tabstops_p = tabstops;
        while (*line_p)
        {
            if (*line_p == '\t')
            {
                spaces = 0;
                tabstops_p++;
                line_p++;
                printf("\\t");
            }
            else if (*line_p == ' ')
            {
                while (*line_p == ' ')
                {
                    line_p++;
                    cols++;
                    spaces++;
                    if (cols == *tabstops_p)
                    {
                        printf("\\t");
                        spaces = 0;
                        tabstops_p++; // beware of increments in comparisons!
                    }
                }
                while (spaces > 0)
                { // spaces not converted to tabs
                    spaces--;
                    printf(" ");
                }
            }
            else
            {
                printf("%c", *line_p++);
                cols++;
                tabstops_p += (cols == *tabstops_p);
            }
        }
    }

    return 0;
}

/**
 * @brief Populates the tabstops array with the arithmetic sequence starting at
 * the current stop, and common difference v
 *
 * @param v the common difference
 */
void extrapolate_tabstops(int v)
{
    int *ex_root = tabstops_p;
    while (tabstops_p - tabstops < MAXTABS)
    {
        *tabstops_p = *(tabstops_p - 1) + v;
        tabstops_p++;
    }
    tabstops_p = ex_root;
}

/**
 * @brief Read a line from user input
 *
 * @param s the char array for which the line will be read into
 * @param lim maximum length to read
 * @return the number of characters read
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