/**
 * @file 7-5.c
 * @author Gavin Hua
 * @brief Exercise 7-5.
 *
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
 * the input and number conversion.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE -2
#define MAXVAL 100

int getop(char[]);
void push(double);
double pop(void);
int getch(char *);

int sp = 0;
double val[MAXVAL];
double variables[27];
int varp = 0;

int main()
{
    int type;
    double op2, i_1, i_2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
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
            push(op2 ? (pop() / op2) : op2);
            printf(op2 ? "" : "error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            push(op2 ? ((int)pop() % (int)op2) : op2);
            printf(op2 ? "" : "error: zero divisor\n");
            break;
        case '?': // show top of stack
            printf("%f\n", val[sp - 1]);
            variables[26] = val[sp - 1];
            break;
        case '&': // duplicate
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
        case '_': // log (base e)
            op2 = pop();
            push((op2 > 0) ? log(op2) : op2);
            printf((op2 > 0) ? "" : "error: negative logarithm argument.\n");
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
 * @brief Get next character or numeric operand and writes it into a string
 *
 * @param s the string
 * @return the type of token written
 */
int getop(char s[])
{
    int c;
    char temp[MAXOP];

    c = scanf("%s", temp);
    if (c == EOF)
    {
        return EOF;
    }

    c = temp[0];
    strcpy(s, temp);
    if (!isalnum(c) && c != '.' && c != '-' && c != '>' && c != '<')
    {
        return c;
    }
    else if (strcmp("-", temp) == 0)
    {
        return c;
    }
    else if (c == '>')
    {
        varp = tolower(temp[1]) - 'a';
        return VARIABLE;
    }
    else if (isalpha(c))
    {
        sprintf(s, "%f", variables[tolower(c) - 'a']);
        return NUMBER;
    }
    else if (c == '<')
    {
        sprintf(s, "%f", variables[26]);
        return NUMBER;
    }
    else
    {
        strcpy(s, temp);
        return NUMBER;
    }
}

/**
 * @brief Push a value onto value stack
 *
 * @param f the value
 */
void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can't push %g\n", f);
    }
}

/**
 * @brief Pop and return top value from stack
 *
 * @return the top value
 */
double pop()
{
    printf((sp > 0) ? "" : "error: stack empty\n");
    return (sp > 0) ? val[--sp] : 0;
}