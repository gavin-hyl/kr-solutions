// Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?

#include <stdio.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_BUFFLEN 10000
#define MAX_LINES 100

int getln(char *);
int readlines(char **, int, char *, int);

char *lines[MAX_LINES]; // this stores pointers to line beginnings in strBuff

/* get a single line (without the \n), len=0 if EOF encounterd*/
int getln(char *s)
{
    int len = 0;
    for (; (*s = getchar()) != '\n' && (*s++ != EOF); len++) ;
    *s = '\0';
    return len * (*s != EOF);
}

int readlines(char **lines, int maxLines, char *strbuf, int buffInd)
{
    int len = 0, nLines=0;
    char str[MAX_LINE];
    while ((len = getln(str)) > 0)
    {
        if (nLines >= maxLines || buffInd > MAX_BUFFLEN)
        {
            return -1;
        }
        lines[nLines++] = strbuf + buffInd;
        for (int i = 0; i <= len; i++)
        {
            strbuf[buffInd++] = str[i];
        }
    }
    return nLines;
}


int main(void)
{
    char strBuff[MAX_BUFFLEN];
    int buffInd = 0;
    int nLines = readlines(lines, MAX_LINES, strBuff, buffInd);
    for (int i = 0; i < nLines; i++)
        printf("Line %d: %s\n", i+1, lines[i]);
}