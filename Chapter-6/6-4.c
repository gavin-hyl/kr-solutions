/**
 * @file 6-4.c
 * @author Gavin Hua
 * @brief Exercise 6-4.
 *
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence. Precede each word by its count.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define NKEYS 32
#define MAXWORDS 1000

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *add_word(struct tnode *, char *);
void tree_flatten(struct tnode *);
int getword(char *w, int lim);
struct tnode *alloc_tnode(void);
void my_qsort(void *v[], int (*comp)(void *, void *), int left, int right);
int tnode_comp(struct tnode *node1, struct tnode *node2);
void swap(void *v[], int a, int b);
char *str_dup(char *);
int getch(void);
void ungetch(int c);

struct tnode *nodes[MAXWORDS];
int pnodes;

int main(int argc, char *argv[])
{
    int c;
    struct tnode *root = NULL;
    char word[MAXWORD];

    while ((c = getword(word, MAXWORD)) != EOF)
    {
        if (isalpha(word[0]))
        {
            root = add_word(root, word);
        }
    }

    tree_flatten(root);
    my_qsort((void **)nodes, (int (*)(void *, void *))tnode_comp, 0, pnodes - 1);
    for (int i = 0; i < pnodes; i++)
    {
        printf("(%d) %s\n", nodes[i]->count, nodes[i]->word);
    }
    return 0;
}

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

    if (p == NULL)
    {
        p = alloc_tnode();
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((comp = strcmp(w, p->word)) == 0)
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
        strcpy(p, s);
    }
    return p;
}

/**
 * @brief Flatten a binary tree into the nodes array
 *
 * @param p the binary tree
 */
void tree_flatten(struct tnode *p)
{
    if (p != NULL)
    {
        tree_flatten(p->left);
        nodes[pnodes++] = p;
        tree_flatten(p->right);
    }
}

/**
 * @brief Quicksort implementation
 *
 * @param v the array to be sorted
 * @param comp the comparison function
 * @param left the left index of the sub-array to sort
 * @param right the right index of the sub-array to sort
 */
void my_qsort(void *v[], int (*comp)(void *, void *), int left, int right)
{
    int i, last;

    if (left >= right)
    {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (int i = left + 1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left]))
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    my_qsort(v, comp, left, last - 1);
    my_qsort(v, comp, last + 1, right);
}

/**
 * @brief Swap two elements in an array
 *
 * @param v the array
 * @param a the index of the first element
 * @param b the index of the second element
 */
void swap(void *v[], int a, int b)
{
    void *temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

/**
 * @brief Compares two tnodes' counts
 *
 * @param node1 the first node
 * @param node2 the second node
 * @return 1 if the count of node1 > count of node2, 0 if node1 < node2. If they
 * are equal, compare the two strings lexicographically.
 */
int tnode_comp(struct tnode *node1, struct tnode *node2)
{
    if (node1->count > node2->count)
    {
        return 1;
    }
    else if (node1->count < node2->count)
    {
        return 0;
    }
    else if (strcmp(node1->word, node2->word) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
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