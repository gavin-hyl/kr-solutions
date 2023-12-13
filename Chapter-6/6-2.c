/**
 * @file 6-2.c
 * @author Gavin Hua
 * @brief Exercise 6-2.
 *
 * Write a program that reads a C program and prints in alphabetical order each
 * group of variable names that are identical in the first 6 characters but
 * different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define NKEYS 32

struct tnode *add_word(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *alloc_tnode(void);
char *str_dup(char *);
int is_keyword(char *, int n);
int getch(void);
void ungetch(int c);

int same = 6;
int in_string, in_comment, ignore_line; // ignore line: single-line comments

char *keywords[] = {"auto", "break", "case", "char", "const", "continue",
                    "default", "do", "double", "else", "enum", "extern",
                    "float", "for", "goto", "if", "int", "long", "register",
                    "return", "short", "signed", "sizeof", "static", "struct",
                    "switch", "typedef", "union", "unsigned", "void",
                    "volatile", "while"};

int main(int argc, char *argv[])
{
    int c;

    if (argc == 2 && **++argv == '-')
    {
        same = atoi((*argv) + 1);
    }

    struct tnode *root = NULL;
    char word[MAXWORD];

    while ((c = getword(word, MAXWORD)) != EOF)
    {
        if (c == '\n')
        {
            ignore_line = 0;
        }
        if (isalpha(word[0]) && c != '(' && !in_string && !in_comment && !ignore_line)
        {
            root = add_word(root, word);
        }
    }

    treeprint(root);
    return 0;
}

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/**
 * @brief Add a word to the subtree defined by a root node
 *
 * @param p the root node
 * @param w the word
 * @return the updated node
 */
struct tnode *add_word(struct tnode *p, char *w)
{
    int comp;

    if (is_keyword(w, NKEYS) != -1)
    { // do nothing
        return p;
    }

    if (p == NULL)
    {
        p = alloc_tnode();
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((comp = strncmp(w, p->word, same)) == 0)
    {
        p->count++;
    }
    else if (comp < 0)
    {
        p->left = add_word(p->left, w);
    }
    else
    {
        p->right = add_word(p->right, w);
    }
    return p;
}

/**
 * @brief Checks whether a word is a keyword by binary searching through the
 * keyword list
 *
 * @param word the word to check
 * @param n the length of the keyword list
 * @return -1 if not a keyword, a non-negative integer if it is.
 */
int is_keyword(char *word, int n)
{
    int comp;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((comp = strncmp(word, keywords[mid], same)) < 0)
        {
            high = mid - 1;
        }
        else if (comp > 0)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/**
 * @brief Create a tnode
 *
 * @return a pointer to a tnode
 */
struct tnode *alloc_tnode()
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/**
 * @brief Dynamically allocates memory instead of using maxword
 *
 * @param s the string to be duplicated
 * @return the duplicated string
 */
char *str_dup(char *s)
{
    char *p = (char *)malloc(strlen(s) + 1); // +1 for \0

    if (p != NULL)
    {
        strncpy(p, s, same);
        p[same] = '\0'; // strncpy doesn't add a \0
    }
    return p;
}

/**
 * @brief Print the word-count tree recursively
 *
 * @param p the tree
 */
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
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
        if (c == '\\' && (c = getch()) == '\"')
        { // skip any escaped quotes
            return c;
        }

        if (c == '/')
        {
            if ((c = getch()) == '*')
            {
                in_comment = 1;
            }
            else if (c == '/')
            {
                ignore_line = 1;
            }
            else
            {
                ungetch(c);
            }
        }
        else if (c == '*')
        {
            if ((c = getch()) == '/')
            {
                in_comment = 0;
            }
            else
            {
                ungetch(c);
            }
        }
        else if (c == '#')
        {
            ignore_line = 1;
        }
        else if (c == '\"')
        {
            in_string = !in_string;
        }
        return c;
    }

    while (lim-- >= 0)
    {
        if (!isalnum(*w = getch()) && *w != '_' && *w != '(')
        {
            ungetch(*w);
            break;
        }
        else if (*w == '(')
        {
            return '(';
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