/*
    Implement a simple version of the #define processor (i.e., no arguments)
    suitable for use with C programs, based on the routines of this section.
    You may also find getch and ungetch helpful.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 1000

struct defnelement
{
    struct defnelement *next;
    char *name;
    char *defn;
};

struct defnelement *install(char *name, char *defn);
void undef(char *name);
struct defnelement *lookup(char *s);
char *str_dup(char *s);
unsigned hash(char *s);
int is_ignored(void);
int getword(char *w, int lim);
int getch(void);
void ungetch(int c);

struct defnelement *hashtab[HASHSIZE];
int in_comment, in_string, ignore_line;

int main()
{
    int c;
    char name[MAXWORD], defn[MAXWORD];
    struct defnelement *elemp;

    while ((c = getword(name, MAXWORD)) != EOF)
    {
        if ((elemp = lookup(name)) != NULL && !is_ignored())
        {
            printf(elemp->defn);
        }
        else
        {
            printf(name);
        }

        if (c == '#')
        {
            getword(name, MAXWORD); // define or include
            printf(name);
            if (strcmp(name, "define") == 0 && !is_ignored())
            {
                getword(name, MAXWORD);
                printf(name);
                getword(defn, MAXWORD);
                printf(defn);
                install(name, defn);
            }
            else if (strcmp(name, "undef") == 0 && !is_ignored())
            {
                getword(name, MAXWORD);
                printf(name);
                getword(defn, MAXWORD);
                printf(defn);
                undef(name);
            }
        }
    }
    return 0;
}

void undef(char *name)
{
    struct defnelement *elementp, *headp, *tailp;
    if ((elementp = lookup(name)) == NULL)
    {
        printf("Cannot undefine a name that is not defined.\n");
        return;
    }
    unsigned hashval = hash(name);
    headp = hashtab[hashval];
    if (headp == elementp)
    { // only one name hashed to this value
        hashtab[hashval] = NULL;
        return;
    }
    tailp = elementp->next;
    while (headp->next != elementp)
    {
        headp = headp->next;
    }
    headp->next = tailp;
}

struct defnelement *install(char *name, char *defn)
{
    struct defnelement *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL)
    {
        np = (struct defnelement *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
        {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
    {
        free((void *)np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
    {
        return NULL;
    }
    return np;
}

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct defnelement *lookup(char *s)
{
    struct defnelement *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
        {
            return np;
        }
    }
    return NULL;
}

char *str_dup(char *s)
{
    char *p = (char *)malloc(strlen(s) + 1); // +1 for \0

    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p;
}

int getword(char *word, int lim)
{
    int c, c0;
    char *w = word;

    while ((c = getch()) == ' ' || c == '\t')
    {
        putchar(c); // 6-6 specific
    }

    if (c != EOF)
    {
        *w++ = c;
    }
    if (!isalnum(c))
    {
        *w = '\0';
        if (c == '\\')
        { // skip any escaped quotes
            if ((c = getch()) == '\"')
            {
                *w++ = '\"';
                *w = '\0';
                return '\\';
            }
            ungetch(c);
            c = '\\';
        }
        else if (c == '/')
        {
            if ((c = getch()) == '*')
            {
                in_comment = 1;
            }
            else if (c == '/')
            {
                ignore_line = 1;
            }
            ungetch(c);
        }
        else if (c == '*')
        {
            if ((c = getch()) == '/')
            {
                in_comment = 0;
            }
            ungetch(c);
        }
        else if (c == '\"')
        {
            in_string = !in_string;
        }
        else if (c == '\n')
        {
            ignore_line = 0;
        }
        else if (c == '%')
        {
            *w++ = '%';
            *w = '\0';
        }
        return c;
    }

    while (lim-- >= 0)
    {
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
        w++;
    }
    *w = '\0';

    return word[0];
}

int is_ignored()
{
    return in_comment || in_string || ignore_line;
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