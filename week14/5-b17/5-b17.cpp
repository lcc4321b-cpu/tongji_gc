//2550703 卓03 李良玉
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    static const char other[] = "!@#$%^&*-_=+,.?";
    int len, up, low, dig, oth;

    cout << "请输入密码长度(12-16)， 大写字母个数(>=2)， 小写字母个数(>=2)， 数字个数(>=2)，其它符号个数(>=2)" << endl;

    if (!(cin >> len >> up >> low >> dig >> oth))
    {
        cout << "输入非法" << endl;
        return 0;
    }

    if (len < 12 || len > 16)
    {
        cout << "密码长度[" << len << "]不正确" << endl;
        return 0;
    }
    if (up < 2 || up > len)
    {
        cout << "大写字母个数[" << up << "]不正确" << endl;
        return 0;
    }
    if (low < 2 || low > len)
    {
        cout << "小写字母个数[" << low << "]不正确" << endl;
        return 0;
    }
    if (dig < 2 || dig > len)
    {
        cout << "数字个数[" << dig << "]不正确" << endl;
        return 0;
    }
    if (oth < 2 || oth > len)
    {
        cout << "其它符号个数[" << oth << "]不正确" << endl;
        return 0;
    }
    if (up + low + dig + oth > len)
    {
        cout << "所有字符类型之和[" << up << "+" << low << "+" << dig << "+" << oth << "]大于总密码长度[" << len << "]" << endl;
        return 0;
    }

    cout << len << " " << up << " " << low << " " << dig << " " << oth << endl;

    srand((unsigned)time(NULL));

    for (int t = 0; t < 10; t++)
    {
        char pwd[17];
        int k = 0;

        for (int i = 0; i < up; i++)
        {
            pwd[k++] = char('A' + rand() % 26);
        }
        for (int i = 0; i < low; i++)
        {
            pwd[k++] = char('a' + rand() % 26);
        }
        for (int i = 0; i < dig; i++)
        {
            pwd[k++] = char('0' + rand() % 10);
        }
        for (int i = 0; i < oth; i++)
        {
            pwd[k++] = other[rand() % 15];
        }
        while (k < len)
        {
            int sel = rand() % 4;
            if (sel == 0)
                pwd[k++] = char('A' + rand() % 26);
            else if (sel == 1)
                pwd[k++] = char('a' + rand() % 26);
            else if (sel == 2)
                pwd[k++] = char('0' + rand() % 10);
            else
                pwd[k++] = other[rand() % 15];
        }

        for (int i = len - 1; i >= 1; i--)
        {
            int j = rand() % (i + 1);
            char tmp = pwd[i];
            pwd[i] = pwd[j];
            pwd[j] = tmp;
        }

        pwd[len] = '\0';
        cout << pwd << endl;
    }

    return 0;
}

