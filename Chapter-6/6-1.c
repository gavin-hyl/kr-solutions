/*
    Our version of getword does not properly handle 
    // underscores, 
    // string constants, 
    // comments, 
    // or preprocessor control lines
    Write a better version.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytable / sizeof (keytable[0]))

struct key {
    char *word;
    int count;
} keytable[] = {    // preprocessor lines are ignored
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    { "do", 0 },
    { "double", 0 },
    { "else", 0 },
    { "enum", 0 },
    { "extern", 0 },
    { "float", 0 },
    { "for", 0 },
    { "goto", 0 },
    { "if", 0 },
    { "int", 0 },
    { "long", 0 },
    { "register", 0 },
    { "return", 0 },
    { "short", 0 },
    { "signed", 0 },
    { "sizeof", 0 },
    { "static", 0 },
    { "struct", 0 },
    { "switch", 0 },
    { "typedef", 0 },
    { "union", 0 },
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 }
};

int getword(char *, int);
int binsearch(char *word, struct key tab[], int n);
int getch(void);
void ungetch(int c);

int in_string, in_comment, ignore_line; // ignore line: single-line comments

int main()
{
    int n, c;
    char word[MAXWORD];

    while ((c=getword(word, MAXWORD)) != EOF)
    {
        if (c == '\n')
        {
            ignore_line = 0;
        }
        else if (isalpha(word[0]) && (n = binsearch(word, keytable, NKEYS)) >= 0
            && !in_string && !in_comment && !ignore_line)
        {
            keytable[n].count++;
        }
    }

    for (n = 0; n < NKEYS; n++)
    {
        if (keytable[n].count > 0)
        {
            printf("%4d %s\n", keytable[n].count, keytable[n].word);
        }
    }

    return 0;
} 

int binsearch(char *word, struct key tab[], int n)
{
    int comp;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low+high) / 2;
        if ((comp = strcmp(word, tab[mid].word)) < 0)
        {
            high = mid - 1;
        }
        else if (comp > 0)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }  
    }
    return -1;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while ((c=getch())==' ' || c=='\t') ;   // must return \n to terminate single-line ignores
    if (c != EOF)
    {
        *w++ = c;
    }
    if (!isalpha(c))
    {
        *w = '\0';
        if (c == '\\' && (c=getch())=='\"')
        {   // skip any escaped quotes
            return c;
        }

        if (c == '/')
        {
            if ((c=getch()) == '*')
            {
                in_comment = 1;
            }
            else if (c == '/')
            {
                ignore_line = 1;
            }
            else
            {
                ungetch(c);
            }
        }
        else if (c == '*')
        {
            if ((c=getch()) == '/')
            {
                in_comment = 0;
            }
            else
            {
                ungetch(c);
            }
        }    
        else if (c == '#')
        {
            ignore_line = 1;
        }
        else if (c == '\"')
        {
            in_string = !in_string;
        }
        return c;
    }

    while (lim-- >= 0)
    {
        if (!isalnum(*w = getch()) && *w!='_' && *w!='(')
        {
            ungetch(*w);
            break;
        }
        else if (*w == '(')
        {
            return '(';
            break;
        }
        w++;
    }

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }   
}