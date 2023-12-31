/**
 * @file 4-10.c
 * @author Gavin Hua
 * @brief 4-10: An alternate organization uses getline to read an entire input
 * line; this makes getch and ungetch unnecessary. Revise the calculator to use
 * this approach.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found
#define VARIABLE -2
#define MAXVAL 100 // maximum depth of val stack
#define MAXLINE 100

int getop(char[]);
int get_line(char[], int);
void push(double);
double pop(void);
int getch(void);

char line[MAXLINE];
int linep = -1;
char buf = 0;
int sp = 0;         // next free stack position
double val[MAXVAL]; // value stack
double variables[27];
int varp = 0; // current variable in use
double i_1, i_2;

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
    int i = 0, c;
    if (line[linep] == '\0' || linep == -1)
    {
        get_line(line, MAXLINE);
        linep = 0;
    }
    while ((s[0] = c = line[linep++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isalnum(c) && c != '.' && c != '-' && c != '>' && c != '<') // not a number nor a variable nor an assignment
    {
        return c;
    }
    else if (c == '-') // negative sign or subtraction?
    {
        if (isdigit((line[linep++]))) // negative number
        {
            s[i++] = '-';
            s[i++] = c;
        }
        else
        {
            return c; // subtraction
        }
    }
    else if (c == '>') // variable assignment into the next character
    {
        varp = tolower(line[linep++]) - 'a';
        return VARIABLE;
    }
    else if (isalpha(c)) // get value from variable
    {
        sprintf(s, "%g", variables[tolower(c) - 'a']);
        return NUMBER;
    }
    else if (c == '<') // calling the most recently printed value
    {
        sprintf(s, "%g", variables[26]);
        return NUMBER;
    }
    else // none of the above, is a number
    {
        if (isdigit(c)) // collect integer part
        {
            while (isdigit(s[++i] = c = line[linep++]))
                ;
        }
        if (c == '.') // collect fraction part
        {
            while (isdigit(s[++i] = c = line[linep++]))
                ;
        }
        s[i] = '\0';
        linep--;
        return NUMBER;
    }
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
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i++] = c;
    }
    else if (c == EOF)
    {
        exit(0); // more elegant solution, straight from chapter 7 :D
    }
    s[i] = '\0';
    return i;
}