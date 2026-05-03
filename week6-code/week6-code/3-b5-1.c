//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
    printf("请输入年，月，日\n");
    int year, month, day, long_month, finally_correct, leap_year;
    long_month = -1;
    scanf("%d %d %d", &year, &month, &day);

    //Determine whether the month input is correct
    if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
    {
        long_month = 1;
    }
    else if ((month == 2) || (month == 4) || (month == 6) || (month == 9) || (month == 11))
    {
        long_month = 0;
    }
    else
    {
        printf("输入错误-月份不正确\n");
    }

    //Determine whether the day input is correct
    if ((long_month == 1) && (day >= 1) && (day <= 31))
    {
        finally_correct = 1;//right
    }
    else if ((long_month == 0) && (day >= 1) && (day <= 30))
    {
        finally_correct = 1;//right
    }
    else if (long_month >= 0)
    {
        printf("输入错误-日与月的关系非法\n");
        finally_correct = 0;
    }
    else
    {
        finally_correct = 0;
    }

    //Determine whether the year input is leapyear
    //0 means leap year
    leap_year = year % 4;

    //caculate
    int how_many_days;
    if (finally_correct == 1)
    {
        if ((month <= 7) || (month == 9) || (month == 11))
        {
            how_many_days = month / 2 * 31 + (month - month / 2) * 30 - 2 + ((leap_year == 0) && (month >= 2));
        }
        else
        {
            how_many_days = month / 2 * 31 + (month - month / 2) * 30 - 2 + (leap_year == 0) + 1;
        }
        printf("%d-%d-%d是%d的第%d天\n", year, month, day, year, how_many_days);
    }
    return 0;
}