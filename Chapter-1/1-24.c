/**
 * @file 1-24.c
 * @author Gavin Hua
 * @brief 1-24: Write a program to check a C program for rudimentary syntax
 * errors like unmatched parentheses, brackets and braces. Don't forget about
 * quotes, both single and double, escape sequences, and comments.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 2048

enum match_types
{
    PAREN,
    BRACKETS,
    BRACES,
};

int cumulative_count[BRACES + 1];   // init to zeroes

int main()
{
    char *match_stack = malloc(MAX_CHARS * sizeof(char));
    char c;

    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case ('('):
            *match_stack++ = PAREN;
            cumulative_count[PAREN]++;
            break;
        case (')'):
            if (*--match_stack != PAREN)
            {
                printf("error: unmatched parentheses");
                exit(1);
            }
            cumulative_count[PAREN]--;
            break;
        case ('['):
            *match_stack++ = BRACKETS;
            cumulative_count[BRACKETS]++;
            break;
        case (']'):
            if (*--match_stack != BRACKETS)
            {
                printf("error: unmatched brackets");
                exit(1);
            }
            cumulative_count[BRACKETS]--;
            break;
        case ('{'):
            *match_stack++ = BRACES;
            cumulative_count[BRACES]++;
            break;
        case ('}'):
            if (*--match_stack != BRACES)
            {
                printf("error: unmatched braces");
                exit(1);
            }
            cumulative_count[BRACES]--;
            break;
        case ('\"'):
            while ((c = getchar()) != '\"')
            {
                if (c == EOF)
                {
                    printf("error: unclosed double quote");
                    exit(1);
                }
            }
            break;
        case ('\''):
            while ((c = getchar()) != '\'')
            {
                if (c == EOF)
                {
                    printf("error: unclosed single quote");
                    exit(1);
                }
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
            }
            break;
        case ('\\'):
            getchar();
            break;
        default:
            break;
        }
    }

    char error = 0;
    for (int i = 0; i <= BRACES; i++)
    {
        if (cumulative_count[i] != 0)
        {
            printf("error: extra tokens (code %d)\n", i);
            error = 1;
        }
    }
    if (!error)
    {
        printf("no errors detected.");
    }
    return 0;
}
