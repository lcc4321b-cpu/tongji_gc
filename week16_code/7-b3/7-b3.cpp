//2550703 卓03 李良玉
#include <iostream>
using namespace std;

class Days
{
private:
    int year;
    int month;
    int day;

private:
    static int is_leap_year(int y)
    {
        if ((y % 400) == 0)
        {
            return 1;
        }
        if ((y % 100) == 0)
        {
            return 0;
        }
        if ((y % 4) == 0)
        {
            return 1;
        }
        return 0;
    }

    static int days_in_month(int y, int m)
    {
        int mdays;

        mdays = 31;

        if (m == 2)
        {
            mdays = 28;
            if (is_leap_year(y))
            {
                mdays = 29;
            }
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
        {
            mdays = 30;
        }
        else
        {
            mdays = 31;
        }

        return mdays;
    }

public:
    Days(int y, int m, int d);
    int calc_days();
};
Days::Days(int y, int m, int d)
{
    year = y;
    month = m;
    day = d;
}
int Days::calc_days()
{
    int total_days;
    int i;
    // 检查闰年2月29日的合法性
    if (month == 2 && day == 29 && !is_leap_year(year))
    {
        return -1;
    }
    total_days = 0;
    // 计算前几个月的天数
    for (i = 1; i < month; i++)
    {
        total_days += days_in_month(year, i);
    }
    // 加上当前月的天数
    total_days += day;
    return total_days;
}
int main()
{
    if (1) {
        Days d1(2024, 3, 18);
        cout << "应该输出78， 实际是：" << d1.calc_days() << endl;
    }

    if (1) {
        Days d1(2023, 3, 18);
        cout << "应该输出77， 实际是：" << d1.calc_days() << endl;
    }

    if (1) {
        Days d1(2024, 12, 31);
        cout << "应该输出366，实际是：" << d1.calc_days() << endl;
    }

    if (1) {
        Days d1(2023, 12, 31);
        cout << "应该输出365，实际是：" << d1.calc_days() << endl;
    }

    if (1) {
        Days d1(2024, 2, 29);
        cout << "应该输出60， 实际是：" << d1.calc_days() << endl;
    }

    if (1) {
        Days d1(2023, 2, 29);
        cout << "应该输出-1， 实际是：" << d1.calc_days() << endl;
    }

    return 0;
}