/*
    Extend detab to accept the shorthand "-m +n" to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior. 
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
int extrp_flag = 0;

void extrapolate_tabstops(int);
void add_space(int *);
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
        arg = atoi((*argv)+1);
        if ((*argv)[0] == '-')
        {
            while (*ptabstops < arg && extrp_flag)
            {
                ptabstops++;
            }
            *ptabstops++ = arg;
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

    for (int i = 0; i<MAXTABS; i++)
    {
        printf("%d ", tabstops[i]);
    }


    while(get_line(line, MAXLINE) != EOF)
    {
        pline = line;
        cols = 0;
        ptabstops = tabstops;
        while(*pline)
        {
            if (*pline == '\t')
            {   
                add_space(&cols);
                while (cols < *ptabstops)
                {
                    add_space(&cols);
                }
                ptabstops++;
            }
            else
            {
                printf("%c", *pline);
                cols++;
                ptabstops += (cols == *ptabstops);
            }
            pline++;
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

void add_space(int *c)
{
    (*c)++; // ++ has higher precedence than *
    printf(" ");
}

// read a line into s (including \n), return length
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