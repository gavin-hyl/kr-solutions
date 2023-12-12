/*
    Modify the program detab to accept a list of tab stops as arguments.
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
        if ((tab = atoi((*argv)+1)) != 0)
        {   // technically the +1 is not needed, and we can just use an abs
            *ptabstops++ = tab;
        }
        else
        {
            printf("arguments must be nonnegative ints, dummy!");
            return 1;
        }
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
                if (*ptabstops == 0)
                {
                    while (cols % TABSPACES != 0)
                    {
                        add_space(&cols);
                    }
                }
                else
                {
                    while (cols < *ptabstops)
                    {
                        add_space(&cols);
                    }
                }
                ptabstops++;
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