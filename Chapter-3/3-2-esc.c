/*
    Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.
*/

#include <stdio.h>

#define MAXSTR 1000

void escape(char s[], const char t[]);
int get_line(char s[], int lim);

char s[MAXSTR], t[MAXSTR];

int main()
{
    get_line(t, MAXSTR);
    escape(s, t);
    printf(s);
    return 0;
}

/**
 * @brief Converts escape characters into string representations
 *
 * @param s the converted string
 * @param t the stirng to be converted
 */
void escape(char s[], const char t[])
{
    int c, i = 0, j = 0;
    while ((c = t[j++]) != '\0')
    {
        switch (c)
        {
        case '\n':
            s[i++] = '\\';
            s[i++] = 'n';
            break;
        case '\t':
            s[i++] = '\\';
            s[i++] = 't';
            break;
        default:
            s[i++] = c;
            break;
        }
    }
    s[i] = '\0';
}

/**
 * @brief Get the line object
 * 
 * @param s 
 * @param lim 
 * @return int 
 */
int get_line(char s[], int lim)
{
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
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
