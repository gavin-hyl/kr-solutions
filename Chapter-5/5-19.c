/*
    Modify undcl so that it does not add redundant parentheses to declarations.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN 100
enum tokentypes { NAME = 1, PARENS, BRACKETS };

int gettoken(void);

int tokentype;              // type of last token, 0 if not read yet
char token[MAXTOKEN];       // last token string
char out[1000];
char temp[MAXTOKEN];

// undcl: convert word descriptions to declarations
int main()
{
    int type, pbuffer;
    while (gettoken() != EOF)
    {
        pbuffer = 0;
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
        {
            if (type == PARENS || type == BRACKETS)
            {
                if (pbuffer)
                {
                    sprintf(temp, "(*%s)", out);
                    strcpy(out, temp);
                    pbuffer = 0;
                }
                strcat(out, token);
            }
            else if (type == '*') 
            {
                if (pbuffer)
                {
                    sprintf(temp, "*%s", out);
                    strcpy(out, temp);
                }
                pbuffer = 1;
            }
            else if (type == NAME) 
            {
                if (pbuffer)
                {
                    sprintf(temp, "*%s", out);
                    strcpy(out, temp);
                    pbuffer = 0;
                }
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
            {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n",out);
    }

   return 0;
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t') ;

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
        while ((*p++ = getch()) != ']') ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) 
    {
        do
        {
            *p++ = c;
        } while (isalnum(c = getch()) || c=='_');
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }

    return tokentype = c;
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