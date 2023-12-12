/*
    Write a function for the other direction as well, converting escape sequences into the real characters.
*/

#include <stdio.h>

#define MAXSTR 1000

void unescape(char s[], const char t[]);
int get_line(char s[], int lim);

char s[MAXSTR], t[MAXSTR];

int main()
{
    get_line(t, MAXSTR);
    unescape(s, t);
    printf(s);
    return 0;
}

// unescape: converts string representations into escape characters.
void unescape(char s[], const char t[])
{
    int c, c1, i=0,j=0;
    while((c=t[j++]) != '\0')
    {
        switch(c)
        {
            case '\\':
                switch((c1=t[j++]))
                {
                    case 'n':
                        s[i++]='\n';
                        break;
                    case 't':
                        s[i++]='\t';
                        break;
                    default:
                        s[i++] = c;
                        s[i++] = c1;
                        break;
                }
                break;
            default:
                s[i++] = c;
                break;
        }
    }
    s[i] = '\0';
}

int get_line(char s[], int lim)
{
    int c, i=0;
    while (i<lim-1 && (c=getchar())!=EOF && c!='\n')
    {
        s[i++] = c;
    }
    if (c == EOF)
    {
        return EOF;
    }
    s[i++] = '\n';
    s[i] = '\0';
    return i;
}

