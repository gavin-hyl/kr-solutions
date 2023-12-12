/**
 * @file 5-8.c
 * @author Gavin Hua
 * @brief 5-8: There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int main()
{
    printf("DoY = %d\n", day_of_year(2023, 10, 32));
    int m, d;
    month_day(2023, 366, &m, &d);
    printf("month = %d\n", m);
    printf("day = %d", d);
    return 0;
}

/**
 * @brief Set day of year from month & day
 *
 * @param year the year
 * @param month the month
 * @param day the day of the month
 * @return the day of the year
 */
int day_of_year(int year, int month, int day)
{
    int leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
    if ((month > 12) || (day > daytab[leap][month]) || (month <= 0) || (day <= 0))
    {
        return -1;
    }
    for (int i = 1; i < month; i++)
    {
        day += daytab[leap][i];
    }
    return day;
}

/**
 * @brief Set month, day from day of year
 *
 * @param year the year
 * @param yearday the day of year
 * @param month_p the pointer to store the month
 * @param day_p the pointer to store the day
 */
void month_day(int year, int yearday, int *month_p, int *day_p)
{
    int i;
    int leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
    if ((yearday >= 365 + leap) || (yearday <= 0))
    {
        *month_p = *day_p = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
    {
        yearday -= daytab[leap][i];
    }
    *month_p = i;
    *day_p = yearday;
}
