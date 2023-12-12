/**
 * @file 4-8to9.c
 * @author Gavin Hua
 * @brief Calculator program for exercises 4-8 and 4-9.
 *
 * 4-8: Suppose that there will never be more than one character of pushback.
 * Modify getch and ungetch accordingly.
 *
 * 4-9: Our getch and ungetch do not handle a pushed-back EOF correctly.
 * Decide what their properties ought to be if an EOF is pushed back,
 * then implement your design.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found
#define VARIABLE '1'
#define MAXVAL 100 // maximum depth of val stack

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char[]);

char buf;             /* buffer for ungetch */
int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */
double variables[27]; /* the stored variables*/
int varp = 0;         /* current variable in use */
double i_1, i_2;      /* intermediate variables*/

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            variables[26] = atof(s);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
            {
                push(pop() / op2);
            }
            else
            {
                printf("error: zero divisor\n");
                push(op2);
            }
            break;
        case '%':
            op2 = pop();
            if (op2 != 0)
            {
                push((int)pop() % (int)op2);
            }
            else
            {
                printf("error: zero divisor\n");
                push(op2);
            }
            break;
        case '\n': // show top of stack
            printf("%f\n", val[sp - 1]);
            break;
        case '@': // duplicate
            push(val[sp - 1]);
            break;
        case '!': // interchange
            i_1 = pop();
            i_2 = pop();
            push(i_1);
            push(i_2);
            break;
        case '#': // clear
            while (sp > 0)
            {
                pop();
            }
            printf("stack cleared.\n");
            break;
        case '~': // sin, in radians
            push(sin(pop()));
            break;
        case '^': // power (prev ^ this)
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case '_': // log
            push(log(pop()));
            break;
        case VARIABLE:
            variables[varp] = val[sp - 1];
            break;
        case EOF:
            return 0;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

/**
 * @brief Push a value onto value stack
 *
 * @param f the value
 */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/**
 * @brief Pop and return top value from stack
 *
 * @return the top value
 */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/**
 * @brief Get next character or numeric operand and writes it into a string
 *
 * @param s the string
 * @return the type of token written
 */
int getop(char s[])
{
    int i = 0, c, d;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isalnum(c) && c != '.' && c != '-' && c != '>' && c != '<')
    { // not a number nor a variable nor an assignment
        return c;
    }
    else if (c == '-')
    { // negative sign or subtraction?
        if (isdigit((c = getchar())))
        { // negative number
            s[i++] = '-';
            s[i++] = c;
        }
        else
        { // subtraction
            return c;
        }
    }
    else if (c == '>')
    { // variable assignment into the next character
        varp = tolower(getchar()) - 'a';
        return VARIABLE;
    }
    else if (isalpha(c))
    { // get value from variable
        sprintf(s, "%g", variables[tolower(c) - 'a']);
        return NUMBER;
    }
    else if (c == '<')
    { // calling the most recently printed value
        sprintf(s, "%g", variables[26]);
        return NUMBER;
    }
    else
    { // none of the above, is a number
        if (isdigit(c))
        { // collect integer part
            while (isdigit(s[++i] = c = getch()))
                ;
        }
        if (c == '.')
        { // collect fraction part
            while (isdigit(s[++i] = c = getch()))
                ;
        }
        s[i] = '\0';
        if (c != EOF)
        {
            ungetch(c);
        }
        else if (c == EOF)
        {
            return EOF;
        }
        return NUMBER;
    }
}

/**
 * @brief Get a (possibly pushed-back) character
 *
 * @return the character
 */
int getch(void)
{
    int ret = (buf == 0) ? getchar() : buf;
    if (ret == EOF)
    {
        exit(0);
    }
    buf = 0;
    return ret;
}

/**
 * @brief Push character back on input
 *
 * @param c the character
 */
void ungetch(int c)
{
    if (c != EOF)
    {
        buf = c;
    }
    else
    {
        exit(0);
    }
}

/**
 * @brief Push string back on input
 *
 * @param s the string
 */
void ungets(char s[])
{
    int len = strlen(s);
    for (int i = len - 1; i >= 0; i--)
    {
        ungetch(s[i]);
    }
}