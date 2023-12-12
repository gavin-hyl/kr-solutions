/**
 * @file 1-15.c
 * @author Gavin Hua
 * @brief 1-15: Rewrite the temperature conversion program of 
 * Section 1.2 (Exercise 1-4) to use a function for conversion.
 */

float celsius_to_fahrenheit(float);

#include <stdio.h>

int main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    printf("  C   F\n");
    for (celsius=lower; celsius<=upper; celsius+=step)
    {
        fahr = celsius_to_fahrenheit(celsius);
        printf("%3.0f %6.1f\n", celsius, fahr);
    }
}

/**
 * @brief Converts celsius to fahrenheit
 * 
 * @param celsius the celsius value to be converted
 * @return the corresponding fahrenheit value
 */
float celsius_to_fahrenheit(float celsius)
{
    return (9.0*celsius/5.0) + 32.0;
}
