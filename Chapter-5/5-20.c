/**
 * @file 5-20.c
 * @author Gavin Hua
 * @brief Exercise 5-20.
 *
 * Expand dcl to handle declarations with function argument types, and
 * qualifiers like const and static.
 *
 * The most complex problem yet :)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN 63
#define MAXDCL 1023
#define MAXOUT 2047

enum tokentypes
{
    NAME,
    PARENS,
    BRACKETS,
    ARGS
};

typedef struct
{
    char str[MAXDCL];         // declaration string to be parsed
    int pstr;                 // index of the next character to be read
    int tokentype;            // type of last token
    char token[MAXTOKEN];     // last token string
    char name[MAXTOKEN];      // identifier name
    char datatype[MAXTOKEN];  // data type = char, int, etc.
    char quals[MAXTOKEN];     // qualifiers = const, static, etc.
    char description[MAXOUT]; // description of the declaration
    char out[MAXOUT];         // total output - NOT the original out!
} declaration_t;

declaration_t *alloc_dclr(void);
void parse(declaration_t *dclr);
void dcl(declaration_t *dclr);
void dirdcl(declaration_t *dclr);
int gettoken(declaration_t *dclr);
int is_keyword(char **kw, char *element);

int get_line(char s[], int lim);
int dcl_getch(declaration_t *dclr);
void dcl_ungetch(declaration_t *dclr);
void error_msg(char *s);

char *datatypes[] = {"char", "int", "float", "double", NULL};
char *qualifiers[] = {"static", "const", NULL};

int main()
{
    declaration_t *main = alloc_dclr();

    while (get_line(main->str, MAXDCL) != EOF)
    {
        parse(main);
        printf("%s\n", main->out);
        main = alloc_dclr();
    }

    return 0;
}

/**
 * @brief Parse a declaration_t
 *
 * @param dclr the declaration to be parsed
 */
void parse(declaration_t *dclr)
{
    while (gettoken(dclr) == NAME)
    {
        if (is_keyword(qualifiers, dclr->token))
        {
            strcat(dclr->quals, dclr->token);
            strcat(dclr->quals, " ");
        }
        else if (is_keyword(datatypes, dclr->token))
        {
            strcpy(dclr->datatype, dclr->token);
            break; // also ensures no extra tokens are read.
        }
        else
        {
            error_msg("unknown keyword.");
        }
    }
    dcl(dclr);
    if (dclr->tokentype != '\n' && dclr->tokentype != '\0')
    {
        error_msg("wrong syntax (trailing symbols).");
    }
    sprintf(dclr->out, "%s: %s%s%s", dclr->name, dclr->quals,
            dclr->description, dclr->datatype);
}

/**
 * @brief Parse a declarator
 *
 * @param dclr the declarator to be parsed
 */
void dcl(declaration_t *dclr)
{
    int nstars = 0;
    while (gettoken(dclr) == '*')
    {
        nstars++;
    }
    dirdcl(dclr);
    while (nstars)
    {
        nstars--;
        strcat(dclr->description, "pointer to ");
    }
}

/**
 * @brief Parse a direct declarator
 *
 */
void dirdcl(declaration_t *dclr)
{
    int type;

    if (dclr->tokentype == '(')
    { // ( dcl ), deals with all the pointers first
        dcl(dclr);
        if (dclr->tokentype != ')')
        {
            error_msg("missing ')'.");
        }
    }
    else if (dclr->tokentype == NAME)
    { // variable name
        if (is_keyword(datatypes, dclr->token) || is_keyword(qualifiers, dclr->token))
        {
            error_msg("cannot use keyword as variable name.");
        }
        strcpy(dclr->name, dclr->token);
    }
    else
    {
        error_msg("expected name or (dcl).");
    }

    // optional (), [], or (func_args)
    while ((type = gettoken(dclr)) == PARENS || type == BRACKETS || type == ARGS)
    {
        if (type == PARENS)
        {
            strcat(dclr->description, "function (with no arguments) returning ");
        }
        else if (type == BRACKETS)
        {
            strcat(dclr->description, "array");
            strcat(dclr->description, dclr->token);
            strcat(dclr->description, " of ");
        }
        else if (type == ARGS)
        {
            strcat(dclr->description, "function (with argument(s) ");

            int add_comma = 0;
            do
            { // parse arguments one by one
                strcat(dclr->description, (add_comma ? ", " : ""));

                declaration_t *arg = alloc_dclr();
                int nparens = 0;
                char c;
                char *ptemp = arg->str;
                while ((c = dcl_getch(dclr)) != ',' &&
                       ((c != ')') || (c == ')' && nparens != 0)))
                { // function argument declarations may include parens
                    // we want to find the one that matches the outermost one.
                    *ptemp++ = c;
                    nparens += (c == '(') - (c == ')');
                }
                *ptemp = '\0';
                dcl_ungetch(dclr);
                parse(arg);
                strcat(dclr->description, arg->out);
                add_comma = 1;
            } while ((type = gettoken(dclr)) == ',');

            strcat(dclr->description, ") returning ");
        }
        else
        {
            error_msg("how did we get here?");
        }
    }
}

/**
 * @brief Get the next token
 *
 * @return the token type
 */
int gettoken(declaration_t *dclr)
{
    int c;
    char *ptoken = dclr->token;

    while (isspace(c = dcl_getch(dclr)))
        ;

    if (c == '(')
    {
        if (dcl_getch(dclr) == ')')
        {
            strcpy(dclr->token, "()");
            return dclr->tokentype = PARENS;
        }
        else if (dclr->name[0] == '\0')
        { // precedence parentheses
            dcl_ungetch(dclr);
            return dclr->tokentype = '(';
        }
        else
        {
            dcl_ungetch(dclr);
            return dclr->tokentype = ARGS;
        }
    }
    else if (c == '[')
    {
        *ptoken++ = c;
        while ((*ptoken = dcl_getch(dclr)) != ']')
        {
            if ((*ptoken > '9' || *ptoken < '0') ||
                (ptoken == &(dclr->token)[1] && *ptoken == '0'))
            { // checks for non-numeric index
                error_msg("array must be notated as [nonzero_integer].");
            }
            ptoken++;
        }
        *++ptoken = '\0';
        return dclr->tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        *ptoken++ = c;
        while (isalnum(c = dcl_getch(dclr)) || c == '_')
        {
            *ptoken++ = c;
        }
        *ptoken = '\0';
        dcl_ungetch(dclr);
        return dclr->tokentype = NAME;
    }
    else
    { // for * and )
        return dclr->tokentype = c;
    }
}

/**
 * @brief Checks whether an element is a keyword
 *
 * @param element
 * @return int
 */
int is_keyword(char **kw, char *element)
{
    while (*kw)
    {
        if (strcmp(*kw, element) == 0)
        {
            return 1;
        }
        kw++;
    }
    return 0;
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

/**
 * @brief Get a (possibly pushed-back) character from a dcl struct
 *
 * @return the character
 */
int dcl_getch(declaration_t *dclr)
{
    return dclr->str[(dclr->pstr)++];
}

/**
 * @brief Push character back on the dcl struct buffer
 *
 * @param c the character
 */
void dcl_ungetch(declaration_t *dclr)
{
    (dclr->pstr)--;
}

/**
 * @brief Create and initialize a new declaration_t struct
 *
 * @return a pointer to the created struct
 */
declaration_t *alloc_dclr()
{
    declaration_t *dclr = (declaration_t *)malloc(sizeof(declaration_t));
    dclr->str[0] = dclr->token[0] = dclr->name[0] = dclr->datatype[0] = '\0';
    dclr->quals[0] = dclr->description[0] = dclr->out[0] = '\0';
    dclr->pstr = dclr->tokentype = 0;
    return dclr;
}

/**
 * @brief Print an error message and die
 *
 * @param s the message
 */
void error_msg(char *s)
{
    printf("[ERROR]: %s\n", s);
    exit(1);
}