/**
 * @file 1-23.c
 * @author Gavin Hua
 * @brief 1-23: Write a program to remove all comments from a C program. 
 * Don't forget to handle quoted strings and character constants properly. 
 * C comments don't nest. 
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;

    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case ('\"'):
            putchar(c);
            while ((c = getchar()) != '\"')
            {
                if (c == EOF)
                {
                    printf("error: unclosed double quote");
                    exit(1);
                }
                putchar(c);
            }
            break;
        case ('\''):
            putchar(c);
            while ((c = getchar()) != '\'')
            {
                if (c == EOF)
                {
                    printf("error: unclosed single quote");
                    exit(1);
                }
                putchar(c);
            }
            break;
        case ('/'):
            if ((c = getchar()) == '*')
            {
                while (1)
                {
                    while ((c = getchar()) != '*')
                    {
                        if (c == EOF)
                        {
                            printf("error: unclosed comment");
                            exit(1);
                        }
                    }
                    if ((c = getchar()) == '/')
                    {
                        break;
                    }
                }
            }
            else if (c == '/')
            {
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                if (c == '\n')
                {
                    putchar('\n');
                }
            }
            break;
        default:
            putchar(c);
            break;
        }
    }
    return 0;
}