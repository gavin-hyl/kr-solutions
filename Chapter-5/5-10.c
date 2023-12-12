/**
 * @file 5-10.c
 * @author Gavin Hua
 * @brief 5-10: Write the program expr, which evaluates a reverse Polish 
 * expression from the command line, where each operator or operand is a 
 * separate argument.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100   // max size of operand or operator
#define NUMBER '0'  // signal that a number was found
#define VARIABLE -2
#define MAXVAL 100  // maximum depth of val stack

int get_op_type(char*);
void push(double);
double pop(void);

int sp = 0;         // next free stack position
double val[MAXVAL]; // value stack

// expr
int main(int argc, char *argv[])
{
    int type=0, err_flag=0;
    double op2=0;
    while ((type = get_op_type(*++argv)) != EOF) {
        switch (type)
        {
            case NUMBER:
                push(atof(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '^':   // terminal screws up the * sign for some reason
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0)
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("error: zero divisor\n");
                    err_flag = 1;
                }
                break;
            default:
                printf("error: unknown command %s\n", *argv);
                err_flag = 1;
                break;
        }
    }
    printf(err_flag ? "" : "%g", val[sp-1]);
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
double pop(void)
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/**
 * @brief Get next character or numeric operand and writes it into a string
 *
 * @param op the string
 * @return the type of token written
 */
int get_op_type(char *op)
{
    int c;
    if (op == NULL)
    {   // reached end of argv
        return EOF;
    }

    while (isspace(c = *op))
    {   // skip whitespace
        op++;
    }
        
    if (!isalnum(c) && c != '.' && c != '-')
    {   // not a number
        return c;
    }
    else if (c == '-' && !isdigit(*++op))
    {   // subtraction sign
        return c;
    }
    else    
    {   // none of the above, is a number
        return NUMBER;
    }
}