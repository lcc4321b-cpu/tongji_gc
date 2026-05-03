//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
using namespace std;

// 是否闰年
bool is_leap(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }
    if (year % 100 == 0)
    {
        return false;
    }
    if (year % 4 == 0)
    {
        return true;
    }
    return false;
}

// 某年某月有多少天
int days_in_month(int year, int month)
{
    static const int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int d = days[month - 1];
    if (month == 2 && is_leap(year))
    {
        ++d;
    }
    return d;
}

int zeller(int year, int month, int day)
{
    month = month + 12 * (month == 1 || month == 2);
    year = year - 1 * (month == 13 || month == 14);
    int answer;
    answer = year % 100 + (year % 100) / 4 + (year / 100) / 4 - 2 * (year / 100) + (13 * (month + 1)) / 5 + day - 1;
    answer = ((answer % 7) + 7) % 7;
    return answer;
}

// 输出若干空格
void print_spaces(int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << ' ';
    }
}

int main()
{
    int year;
    int perRow;

    cout << "请输入年份[1900-2100]"<<endl;
    cin >> year;
    cout << "请输入每行打印的月份数[1/2/3/4/6/12]"<<endl;
    cin >> perRow;

    cout << year << "年的日历:" << endl;
    cout << endl;
    cout << std::left;

    const int MONTH_WIDTH = 27;
    const int per_width = 4;

    for (int startMonth = 1; startMonth <= 12; startMonth += perRow) 
    {
        int endMonth = startMonth + perRow - 1;
        if (endMonth > 12)
        {
            endMonth = 12;
        }
        // 第一行：月份标题（简单居中）
        cout << std::right;
        for (int m = startMonth; m <= endMonth; ++m) 
        {
            print_spaces(per_width*3-1);
            cout << setw(2) << m << "月";
            print_spaces(per_width * 3 + 1);
            if (m < endMonth)
            {
                print_spaces(per_width);
            }
        }
        cout << std::left;
        cout << endl;

        // 第二行：星期标题
        for (int m = startMonth; m <= endMonth; ++m) 
        {
            cout << "Sun Mon Tue Wed Thu Fri Sat ";
            if (m < endMonth)
            {
                print_spaces(per_width);
            }
        }
        cout << endl;

        // 该行中各月份所需的最大周数（4~6）
        int maxLines = 0;
        for (int m = startMonth; m <= endMonth; ++m) 
        {
            int first = zeller(year, m, 1); // 0=Sun
            int days = days_in_month(year, m);
            int lines = (first + days + 6) / 7;  // 向上取整
            if (lines > maxLines)
            {
                maxLines = lines;
            }
        }

        // 逐周输出
        for (int line = 0; line < maxLines; ++line) 
        {
            for (int m = startMonth; m <= endMonth; ++m) 
            {
                int first = zeller(year, m, 1);
                int days = days_in_month(year, m);

                for (int d = 0; d < 7; ++d) 
                {
                    int num = line * 7 + d + 1 - first;
                    if (num >= 1 && num <= days) 
                    {
                        cout << setw(per_width) << num;
                    }
                    else {
                        cout << "    ";
                    }
                }
                if (m < endMonth) print_spaces(per_width);
            }
            cout << endl;
        }
        cout << endl; // 每行月份之间空一行
    }
    cout << endl;
    return 0;
}
