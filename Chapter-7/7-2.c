/**
 * @file 7-2.c
 * @author Gavin Hua
 * @brief Exercise 7-2.
 * 
 * Write a program that will print arbitrary input in a sensible way. As a 
 * minimum, it should print non-graphic characters in octal or hexadecimal 
 * according to local custom, and break long text lines.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000

int get_break(char *line, int force_break);
int get_line(char s[], int lim);

int main()
{
    char line[MAXLINE], split[MAXLINE], *linep;
    int force_break = 20;
    int len, breakp;
    
    printf("My terminal handles Chinese characters quite well :D\n");

    while ((len=get_line(line, MAXLINE)) != EOF)
    {
        if (len < force_break)
        {
            printf(line);
        }
        else
        {
            linep = line;
            while (&line[len] - linep > force_break)
            {
                breakp = get_break(linep, force_break);
                strncpy(split, linep, breakp);
                split[breakp] = '\0';
                printf("%s\n", split);
                linep += breakp;
            }
            printf(linep);
        }
    }
}

/**
 * @brief Determine where a line should be broken, going from back to front
 *
 * @param line the line
 * @param force_break the maximum length for the line to continue
 * @return the break position
 */
int get_break(char *line, int force_break)
{
    int p = force_break;
    while (p > 0)
    {
        if (isspace(line[p]))
        {   // include the space so that it doesn't appear at the beginning of the next line
            return p+1;
        }
        p--;
    }
    return force_break;
}

/**
 * @brief Read a line from user input
 *
 * @param s the char array for which the line will be read into
 * @param lim maximum length to read
 * @return the number of characters read
 */
int get_line(char s[], int lim)
{
    int c, i=0;
    while (i<lim-1 && (c=getchar())!='\n' && c!=EOF)
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
        s[i] = '\0';
        return i;
    }
    else
    {
        s[i] = '\0';
        return EOF;
    }
}