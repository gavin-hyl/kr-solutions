/**
 * @file 6-5.c
 * @author Gavin Hua
 * @brief Exercise 6-5.
 *
 * Write a function undef that will remove a name and definition from the table
 * maintained by lookup and install.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 1000

struct def_element
{
    struct def_element *next;
    char *name;
    char *defn;
};

struct def_element *install(char *name, char *defn);
void undef(char *name);
struct def_element *lookup(char *s);
char *str_dup(char *s);
unsigned hash(char *s);
int getword(char *w, int lim);
int getch(void);
void ungetch(int c);

struct def_element *hashtab[HASHSIZE];

int main()
{
    int c;
    char name[MAXWORD], defn[MAXWORD];
    printf("------define------\n");
    while (getword(name, MAXWORD) != EOF)
    {
        if (!isalpha(name[0]))
        {
            printf("identifiers should begin with a letter.\n");
            return 1;
        }
        getword(defn, MAXWORD);
        install(name, defn);
        if (getword(name, MAXWORD) != '\n')
        {
            printf("every definition should be on a new line.\n");
            return 1;
        }
    }
    printf("------undefine------\n");
    while (getword(name, MAXWORD) != EOF)
    {
        if (isalpha(name[0]))
        {
            undef(name);
        }
    }
    printf("------lookup------\n");
    struct def_element *defnelementp;
    while (getword(name, MAXWORD) != EOF)
    {
        if (isalpha(name[0]))
        {
            printf(((defnelementp = lookup(name)) == NULL) ? "Identifier not found." : defnelementp->defn);
            printf("\n");
        }
    }
    return 0;
}

/**
 * @brief Remove a name-definition pair from the linked list
 *
 * @param name the name
 */
void undef(char *name)
{
    struct def_element *elementp, *headp, *tailp;
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

/**
 * @brief Install a name-definition pair into linked list
 *
 * @param name the name
 * @param defn the definition
 * @return a pointer to the def_element struct that was installed
 */
struct def_element *install(char *name, char *defn)
{
    struct def_element *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL)
    {
        np = (struct def_element *)malloc(sizeof(*np));
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

/**
 * @brief Custom hash function
 *
 * @param s the string to be hashed
 * @return the hash value
 */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/**
 * @brief Lookup a name-value pair in the linked list
 *
 * @param s the name to look up
 * @return a pointer to the found def_element
 */
struct def_element *lookup(char *s)
{
    struct def_element *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
        {
            return np;
        }
    }
    return NULL;
}

/**
 * @brief Dynamically allocates memory for a string
 *
 * @param s the string to be duplicated
 * @return the duplicated string
 */
char *str_dup(char *s)
{
    char *p = (char *)malloc(strlen(s) + 1); // +1 for \0

    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p;
}

/**
 * @brief Get a word from the input text, assumed to be a C program
 *
 * @param word the pointer to store the word
 * @param lim the length limit of the word
 * @return int
 */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c != EOF)
    {
        *w++ = c;
    }
    if (!isalpha(c))
    {
        *w = '\0';
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