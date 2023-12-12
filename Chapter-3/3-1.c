/**
 * @file 3-1.c
 * @author Gavin Hua
 * @brief 3-1: Our binary search makes two tests inside the loop, when one would
 * suffice (at the price of more tests outside.) Write a version with only one
 * test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARR_LEN 1000000

int binsearch_v1(int, int[], int);
int binsearch_v2(int, int[], int);

int arr[ARR_LEN];

int main()
{
    clock_t start, end;
    double time;
    int index;

    for (int i = 0; i < ARR_LEN; i++)
    {
        arr[i] = i;
    }
    start = clock();
    for (int i = 0; i < 10000000; i++)
    {
        // index = binsearch_v1(3, arr, ARR_LEN);
        index = binsearch_v2(3, arr, ARR_LEN);
    }
    printf("%d\n", index);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%.4f", time);
    return 0;
}

/**
 * @brief Binary search v1, with two conditional statements
 *
 * @param x the search target
 * @param v the array
 * @param n the length of the array
 * @return the index of the target in the array
 */
int binsearch_v1(int x, int v[], int n)
{
    int low, high, mid;
    low = v[0];
    high = v[n - 1];
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
        {
            high = mid - 1;
        }
        else if (x > v[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/**
 * @brief Binary search v2, with one conditional statement
 *
 * @param x the search target
 * @param v the array
 * @param n the length of the array
 * @return the index of the target in the array
 */
int binsearch_v2(int x, int v[], int n)
{
    int low, high, mid, i = 0;

    low = v[0];
    high = v[n - 1];
    mid = (low + high) / 2;
    while (low < high - 1)
    {
        if (x < v[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid;
        }
        mid = (low + high) / 2;
    }
    return (x == v[mid]) ? mid : -1;
}