/**
 * @file 1-3.c
 * @author Gavin Hua 
 * @brief 1-3: Modify the temperature conversion program to print a 
 * heading above the table.
 */

#include <stdio.h>

int main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    printf("  F   C\n");
    for (fahr=lower; fahr<=upper; fahr+=step)
    {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
    }
} 