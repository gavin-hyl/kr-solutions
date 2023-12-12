/*
    Modify the program entab to accept a list of tab stops as arguments.
    Use the default tab settings if there are no arguments.
*/ 

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TABSPACES 4
#define MAXTABS 100
#define MAXLINE 1000

int tabstops[MAXTABS];
int *ptabstops = tabstops;

void extrapolate_tabstops(int);
int get_line(char *, int);

int main(int argc, char *argv[])
{   
    int arg, cols, spaces;
    char line[MAXLINE];
    char *pline = line;

    extrapolate_tabstops(TABSPACES);

    printf((argc == 1) ? "Usage: substitute spaces for tabs.\n" : "");

    while (*++argv != NULL)
    {   // construct the tabstop array
        arg = atoi((*argv)+1);
        if (arg == 0)
        {
            printf("arguments must be nonnegative ints, dummy!");
            return 1;
        }
        if ((*argv)[0] == '-')
        {
            *ptabstops++ = arg;
            extrapolate_tabstops(TABSPACES);
        }
        else
        {
            printf("arguments should be preceded by a '-'.\n");
            return 1;
        }
    }

    for (int i = 0; i<MAXTABS; i++)
    {
        printf("%d ", tabstops[i]);
    }

    while (get_line(line, MAXLINE) != EOF)
    {   // transform all suitable lengths of spaces into tabs
        pline = line;
        cols = spaces = 0;
        ptabstops = tabstops;
        while(*pline)
        {
            if (*pline == '\t')
            {   
                spaces = 0;
                ptabstops++;
                pline++;
                printf("\\t");
            }
            else if (*pline == ' ')
            {
                while (*pline == ' ')
                {
                    pline++;
                    cols++;
                    spaces++;
                    if (cols == *ptabstops)
                    {   
                        printf("\\t");
                        spaces = 0;
                        ptabstops++;    // beware of increments in comparisons!
                    }
                }
                while (spaces > 0)
                {   // spaces not converted to tabs
                    spaces--;
                    printf(" ");
                }
            }
            else
            {
                printf("%c", *pline++);
                cols++;
                ptabstops += (cols == *ptabstops);
            }
        }
    }

    return 0;
}

void extrapolate_tabstops(int v)
{
    int *ex_root = ptabstops;
    while (ptabstops - tabstops < MAXTABS)
    {
        *ptabstops = *(ptabstops-1) + v;
        ptabstops++;
    }
    ptabstops = ex_root;
}

int get_line(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c!='\n'; i++)
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