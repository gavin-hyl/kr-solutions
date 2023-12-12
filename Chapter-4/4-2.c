/**
 * @file 4-2.c
 * @author Gavin Hua
 * @brief 4-2: Extend atof to handle scientific notation of the form 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent
 */

#include <ctype.h>
#include <stdio.h>

double atof(char[]);

int main()
{
    double atof(char s[]);
    char s[] = "1234.5e-8";
    printf("%.9f", atof(s));
    return 0;
}

/**
 * @brief Converts a string s to a double
 * 
 * @param s the string
 * @return the corresponding double
 */
double atof(char s[])
{
    double val, power, exp, exp_10 = 1.0;
    int i, sign, pow_sign, e;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }

    for (val = 0.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.')
    {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        pow_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
        {
            i++;
        }
        for (exp = 0.0; isdigit(s[i]); i++)
        {
            exp = 10.0 * exp + (s[i] - '0');
        }
        for (e = 0; e < exp; e++, exp_10 *= 10)
            ;
        exp_10 = (pow_sign > 0) ? exp_10 : (1.0 / exp_10);
    }
    return sign * val * exp_10 / power;
}