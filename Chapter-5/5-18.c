/**
 * @file 5-18.c
 * @author Gavin Hua
 * @brief Exercise 5-18.
 *
 * Make dcl recover from input errors.
 */

/*
Possible input errors:
missing brackets
using non-int type as array index
using keywords for variable names
data type not specified
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN 100

enum tokentypes
{
    NAME = 1,
    PARENS,
    BRACKETS
};

void dcl(void);
void dirdcl(void);
int gettoken(void);
int is_keyword(char *);

int tokentype;           // type of last token, 0 if not read yet
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identifier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char arrsub[MAXTOKEN];   // array subscript
char out[1000];

char *datatypes[] = {"char", "int", "float", 0}; // test list

int main()
{
    while (gettoken() != EOF)
    {                            // 1st token on line
        strcpy(datatype, token); // is the datatype
        if (!is_keyword(token))
        {
            printf("error: data type not speciced.\n");
            exit(1);
        }
        out[0] = '\0';
        dcl(); // parse rest of line
        if (tokentype != '\n')
        {
            printf("error: wrong syntax.\n");
            exit(1);
        }
        printf("%s: %s %s\n", name, out, datatype);
        tokentype = 0;
    }

    return 0;
}

/**
 * @brief Parse a declarator
 *
 */
void dcl(void)
{
    int nstars = 0;
    while (gettoken() == '*')
    {
        nstars++;
    }
    dirdcl();
    while (nstars > 0)
    {
        nstars--;
        strcat(out, " pointer to");
    }
}

/**
 * @brief Parse a direct declarator
 * 
 */
void dirdcl(void)
{
    int type;

    if (tokentype == '(')
    { // ( dcl )
        dcl();
        if (tokentype != ')')
        {
            printf("error: missing )\n");
            exit(1);
        }
    }
    else if (tokentype == NAME)
    { // variable name
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
        exit(1);
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/**
 * @brief Get the next token
 * 
 * @return the token type
 */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    char *parrsub = arrsub;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        *p++ = c;
        while ((*p = getch()) != ']')
        {
            if ((*p > '9' || *p < '0') || (p == &token[1] && *p == '0'))
            { // checks for non-numeric index
                printf("error: array subscript must be nonzero integer.\n");
                exit(1);
            }
            p++;
        }
        *++p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        do
        {
            *p++ = c;
        } while (isalnum(c = getch()));
        *p = '\0';
        ungetch(c);

        if (is_keyword(token) && tokentype != 0)
        {
            printf("error: cannot use keyword as variable name.\n");
            exit(1);
        }
        return tokentype = NAME;
    }

    return tokentype = c;
}

/**
 * @brief Checks whether an element is a keyword
 * 
 * @param element 
 * @return int 
 */
int is_keyword(char *element)
{
    char **keywords_p = datatypes;
    while (*keywords_p)
    {
        if (strcmp(*keywords_p, element) == 0)
        {
            return 1;
        }
        keywords_p++;
    }
    return 0;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/**
 * @brief Get a (possibly pushed-back) character
 *
 * @return the character
 */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/**
 * @brief Push character back on input
 *
 * @param c the character
 */
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