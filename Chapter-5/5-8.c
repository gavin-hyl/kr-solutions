// There is no error checking in day_of_year or month_day. Remedy this defect.

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
    int leap = (year%4 == 0) && (year%100 != 0) || (year%400 == 0);
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

// month_day: set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i;
    int leap = (year%4 == 0) && (year%100 != 0) || (year%400 == 0);
    if ((yearday>=365 + leap) || (yearday <= 0))
    {
        *pmonth = *pday = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
    {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

int main()
{
    printf("DoY = %d\n", day_of_year(2023, 10, 32));
    int m, d;
    month_day(2023, 366, &m, &d);
    printf("month = %d\n", m);
    printf("day = %d", d);
    return 0;
}
