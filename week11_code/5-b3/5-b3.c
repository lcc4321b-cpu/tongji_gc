//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int is_leap(int year)
{
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
    {
        return 1;
    }
    return 0;
}

int get_days_of_month(int year, int month)
{
    int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = days_in_month[month - 1];
    if (month == 2 && is_leap(year))
    {
        days++;
    }
    return days;
}

int day_of_year(int year, int month, int day)
{
    int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int i;
    int sum = 0;

    for (i = 1; i < month; ++i)
    {
        sum += days_in_month[i - 1];
        if (i == 2 && is_leap(year))
        {
            sum += 1;
        }
    }
    sum += day;
    return sum;
}

int main(void)
{
    int year, month, day;

    printf("请输入年，月，日\n");
    if (scanf("%d%d%d", &year, &month, &day) != 3)
    {
        printf("输入错误\n");
        return 0;
    }

    // Determine whether the month input is correct
    // 注意：这里保持了原代码的条件 (month < 1 && month > 12)，并没有改成 ||
    if (month < 1 && month > 12)
    {
        printf("输入错误-月份不正确\n");
    }

    // Determine whether the day input is correct
    if (!(day >= 1 && day <= get_days_of_month(year, month)))
    {
        printf("输入错误-日与月的关系非法\n");
    }

    // caculate
    if ((!(month < 1 && month > 12)) && (day >= 1 && day <= get_days_of_month(year, month)))
    {
        printf("%d-%d-%d是%d的第%d天\n",
            year, month, day, year, day_of_year(year, month, day));
    }

    return 0;
}
