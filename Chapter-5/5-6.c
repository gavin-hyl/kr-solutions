/**
 * @file 5-6.c
 * @author Gavin Hua
 * @brief 5-6: Rewrite appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing. Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (i.e., atof, Chapters 2,
 * 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int get_line(char *, int);
float atof(const char *);
void itoa(char *, int);
void reverse(char *);
char *strindex(char *, char *);
int getop(char *s);

int main()
{
    char str[100];
    get_line(str, 100);
    printf("getln test: %s", str);

    printf("atof test: %f\n", atof("123456e-3"));

    str[strlen(str) - 1] = '\0';
    reverse(str);
    printf("reverse test: %s\n", str);

    itoa(str, 13579);
    printf("itoa test: %s\n", str);

    char str2[] = "12456";
    char str3[] = "124";
    printf("strindex test: %s\n", strindex(str2, str3));
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
        *(s + i) = c;
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

/**
 * @brief Get a float value from a string
 *
 * @param s the string
 * @return the corresponding float value
 */
float atof(const char *s)
{
    double val = 0, exp_10 = 1;
    int sign = 0, exp_sign = 0, exp_lit = 0, dec_power = 1;

    for (; isspace(*s); s++)
        ; // cannot use while - s may not need incrementing

    sign = (*s == '-') ? -1 : 1;
    s += (*s == '+' || *s == '-'); // skip optional sign
    while (isdigit(*s))
    { // read integer part
        val = 10.0 * val + (*s++ - '0');
    }

    if (*s == '.')
    {        // read decimal part
        s++; // inside the if so it doesn't interfere with exponential recognition
        while (isdigit(*s))
        {
            val = 10.0 * val + (*s++ - '0');
            dec_power *= 10;
        }
    }

    if (*s == 'e' || *s == 'E')
    {        // read exponential part
        s++; // skip exponential flag
        exp_sign = (*s == '-') ? -1 : 1;
        s += (*s == '+' || *s == '-'); // skip optional sign
        while (isdigit(*s))
        {
            exp_lit = 10.0 * exp_lit + (*s++ - '0'); // literal exponential
        }
        exp_10 = pow(10, exp_lit - dec_power); // exponential multiplier
        exp_10 = pow(exp_10, exp_sign);
    }

    return sign * val * exp_10;
}

/**
 * @brief Get a string representation of an int
 * 
 * @param s the string representation
 * @param n the int
 */
void itoa(char *s, int n)
{
    char *s0 = s;
    int i, sign;
    n = ((sign = n) < 0) ? -n : n;

    do
    {                        // generate digits in reverse order
        *s++ = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    if (sign < 0)
    {
        *s++ = '-';
    }

    *s = '\0';
    reverse(s0);
}

/**
 * @brief Reverses a string in place
 * 
 * @param s the string
 */
void reverse(char *s)
{
    char c = 0;
    char *s_end = s + strlen(s) - 1; // so that '\0' isn't touched
    while (s <= s_end)
    {
        c = *s;
        *s++ = *s_end;
        *s_end-- = c;
    }
}

/**
 * @brief Finds the beginning of the first occurrence of pattern in s
 * 
 * @param s the searched string
 * @param pattern the target pattern
 * @return a pointer to the beginning of the first occurrence of pattern in s
 */
char *strindex(char *s, char *pattern)
{
    char *s0;
    while (*s)
    {
        if (*s == *pattern)
        {
            s0 = s;
            while (*pattern++ == *s++)
            {
                if (*pattern == '\0')
                {
                    return s0;
                }
            }
        }
        s++;
    }
    return NULL;
}

#define NUMBER '0'
#define VARIABLE -2
double variables[27];
int varp = 0;

/**
 * @brief Get a (possibly pushed-back) character
 *
 * @return the character
 */
int getch(char *buf)
{
    char ret = (*buf == 0) ? getchar() : *buf;
    *buf = 0;
    return ret;
}

/**
 * @brief Get next character or numeric operand and writes it into a string
 *
 * @param s the string
 * @return the type of token written
 */
int getop(char *s)
{
    char *s0 = s;
    int c;
    static char buf;
    while ((*s = c = getch(&buf)) == ' ' || c == '\t')
        ;
    *++s = '\0';

    if (!isalnum(c) && c != '.' && c != '-' && c != '>' && c != '<')
    { // not a number nor a variable nor an assignment
        return c;
    }
    else if (c == '-') // negative sign or subtraction?
    {
        if (!isdigit((c = getch(&buf))))
        {
            return c; // subtraction
        }
        *s++ = '-';
        *s++ = c;
    }
    else if (c == '>') // variable assignment into the next character
    {
        varp = tolower(getch(&buf)) - 'a';
        return VARIABLE;
    }
    else if (isalpha(c)) // get value from variable
    {
        sprintf(s0, "%g", variables[tolower(c) - 'a']);
        s = s0;
        return NUMBER;
    }
    else if (c == '<') // calling the most recently printed value
    {
        sprintf(s0, "%g", variables[26]);
        s = s0;
        return NUMBER;
    }
    else // none of the above, is a number
    {
        if (isdigit(c)) // collect integer part
        {
            while (isdigit(*s++ = c = getch(&buf)))
                ;
        }
        if (c == '.') // collect fraction part
        {
            while (isdigit(*s++ = c = getch(&buf)))
                ;
        }
        *s = '\0';
        if (c != EOF)
        {
            buf = c;
        }
        else if (c == EOF)
        {
            return EOF;
        }
        return NUMBER;
    }
}
