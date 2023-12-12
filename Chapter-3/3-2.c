/**
 * @file 3-2.c
 * @author Gavin Hua
 * @brief 3-2: Write a function escape(s,t) that converts characters like 
 * newline and tab into visible escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function for the other direction as
 * well, converting escape sequences into the real characters.
 */

#include <stdio.h>

void unescape(char[], const char[]);
void escape(char[], const char[]);
int get_line(char[], int);

int main()
{
    const int MAX_STR = 1000;
    char s[MAX_STR], t[MAX_STR];

    get_line(t, MAX_STR);
    escape(s, t);
    printf("%s\n", s);
    get_line(t, MAX_STR);
    unescape(s, t);
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
 * @brief Converts string representations into escape characters.
 * 
 * @param s the converted string
 * @param t the string to be converted
 */
void unescape(char s[], const char t[])
{
    int c, c1, i = 0, j = 0;
    while ((c = t[j++]) != '\0')
    {
        switch (c)
        {
        case '\\':
            switch ((c1 = t[j++]))
            {
            case 'n':
                s[i++] = '\n';
                break;
            case 't':
                s[i++] = '\t';
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

/**
 * @brief Read a line from user input
 *
 * @param s the char array for which the line will be read into
 * @param lim maximum length to read
 * @return the number of characters read
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
