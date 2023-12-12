/*
    Functions like isupper can be implemented to save space or to save time.
    Explore both possibilities.
    
    Saving time: macros offer a ~x2.5 speed boost over function calls, the algorithm
                    can also be improved for ~x1.25 speed boost.
    Saving space: ?
*/

#include <stdio.h>
#include <time.h>

#define isupper_macro1(c) ('A'<=c && 'Z'>=c)
#define isupper_macro2(c) (c - 'A') * ('Z' - c) >= 0    // worse algorithm even though it has fewer conditions
#define isupper_macro3(c) (!(('A' >= c) || ('Z' <= c)))
#define CYCLES 100000000

int isupper_func1(char c)
{
    return ('A'<=c && 'Z'>=c);
}

int isupper_func2(char c)
{
    return (c - 'A') * ('Z' - c) >= 0;
}

int main(int argc, char const *argv[])
{
    clock_t t1, t2, t3, t4, t5;

    t1 = clock();
    for (int i = 0; i < CYCLES; i++)
    {
        isupper_macro1('A');
    }
    t2 = clock();
    for (int i = 0; i < CYCLES; i++)
    {
        isupper_macro3('a');
    }
    t3 = clock();
    for (int i = 0; i < CYCLES; i++)
    {
        isupper_func1('A');
    }
    t4 = clock();
    for (int i = 0; i < CYCLES; i++)
    {
        isupper_func2('A');
    }
    t5 = clock();

    printf("%d\n", t2-t1);
    printf("%d\n", t3-t2);
    printf("%d\n", t4-t3);
    printf("%d\n", t5-t4);
    return 0;
}
