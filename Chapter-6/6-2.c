/*
    Write a program that reads a C program and prints in alphabetical order 
    each group of variable names that are identical in the first 6 characters but different somewhere thereafter. 
    Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.
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

char *keywords[] = { "auto", "break", "case", "char", "const", "continue", 
                    "default", "do", "double", "else", "enum", "extern", "float", 
                    "for", "goto", "if", "int", "long", "register", "return", 
                    "short", "signed", "sizeof", "static", "struct", "switch", 
                    "typedef", "union", "unsigned", "void", "volatile", "while"};

int main(int argc, char *argv[])
{
    int c;

    if (argc==2 && **++argv=='-')
    {
        same = atoi((*argv)+1);
    }

    struct tnode *root = NULL;
    char word[MAXWORD];

    while ((c=getword(word, MAXWORD)) != EOF)
    {
        if (c == '\n')
        {
            ignore_line = 0;
        }
        if (isalpha(word[0]) && c!='(' && !in_string && !in_comment && !ignore_line)
        {
            root = add_word(root, word);
        }
    }
    
    treeprint(root);
    return 0;
}

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *add_word(struct tnode *p, char *w)
{
    int comp;

    if (is_keyword(w, NKEYS) != -1)
    {   // do nothing
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

// all names that aren't keywords are variable names
int is_keyword(char *word, int n)
{
    int comp;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low+high) / 2;
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

struct tnode *alloc_tnode()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

// dynamically allocates memory instead of using maxword
char *str_dup(char *s) 
{
    char *p = (char *) malloc(strlen(s) + 1); // +1 for \0

    if (p != NULL)
    {
        strncpy(p, s, same);
        p[same] = '\0';         // strncpy doesn't add a \0
    }
    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while ((c=getch())==' ' || c=='\t') ;
    if (c != EOF)
    {
        *w++ = c;
    }
    if (!isalpha(c))
    {
        *w = '\0';
        if (c == '\\' && (c=getch())=='\"')
        {   // skip any escaped quotes
            return c;
        }

        if (c == '/')
        {
            if ((c=getch()) == '*')
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
            if ((c=getch()) == '/')
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
        if (!isalnum(*w = getch()) && *w!='_' && *w!='(')
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