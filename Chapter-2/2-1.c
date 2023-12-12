/**
 * @file 2-1.c
 * @author Gavin Hua
 * @brief 2-1：Write a program to determine the ranges of char, short, int, and
 * long variables, both signed and unsigned, by printing appropriate values 
 * from standard headers and by direct computation.
 */

#include <limits.h>
#include <float.h>
#include <stdio.h>

#define printf __mingw_printf // microsoft C runtime doesn't accept long double

int main()
{
    printf("-----signed integer types-----\n");
    printf("char min: %d\n", CHAR_MIN);
    printf("char max: %d\n", CHAR_MAX);
    printf("short (int) min: %d\n", SHRT_MIN);
    printf("short (int) max: %d\n", SHRT_MAX);
    printf("int min: %d\n", INT_MIN);
    printf("int max: %d\n", INT_MAX);
    printf("long (int) min: %ld\n", LONG_MIN);
    printf("long (int) max: %ld\n", LONG_MAX);
    printf("-----unsigned integer types-----\n");
    printf("unsigned min: 0\n");
    printf("unsigned char max: %d\n", UCHAR_MAX);
    printf("unsigned short (int) max: %d\n", USHRT_MAX);
    printf("unsigned int max: %u\n", UINT_MAX);
    printf("unsigned (int) long max: %u\n", ULONG_MAX);
    printf("-----decimal types-----\n");
    /* g -> f when |exponent| is less than 4, otherwise e */
    printf("float min: %g\n", FLT_MIN);
    printf("float max: %g\n", FLT_MAX);
    printf("double min: %g\n", DBL_MIN);
    printf("double max: %g\n", DBL_MAX);
    printf("long double min: %Lg\n", LDBL_MIN);
    printf("long double max: %Lg\n", LDBL_MAX);
    return 0;
}