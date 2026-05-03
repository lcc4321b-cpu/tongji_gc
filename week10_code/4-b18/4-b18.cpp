//2550703 卓03 李良玉
#include<iostream>
using namespace std;

void clean()
{
    cin.clear();
    cin.ignore(1024, '\n');
}

int max(int a, int b)
{
    return (a > b ? a : b);
}

int max(int a, int b, int c)
{
    return max(max(a, b), c);
}

int max(int a, int b, int c, int d)
{
    return max(max(a, b, c), d);
}


int main()
{
    int a, b, c, d;
    int num;
    int finish = 1;
    while (finish)
    {
        cout << "请输入个数num及num个正整数：" << endl;
        cin >> num;
        if (cin.good() == 1)
        {
            if (num == 2)
            {
                cin >> a;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                cin >> b;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                finish = 0;
                cout << "max=" << max(a, b) << endl;
            }
            else if (num == 3)
            {
                cin >> a;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                cin >> b;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                cin >> c;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                finish = 0;
                cout << "max=" << max(a, b, c) << endl;
            }
            else if (num == 4)
            {
                cin >> a;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                cin >> b;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                cin >> c;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                cin >> d;
                if (cin.good() == 0)
                {
                    clean();
                    continue;
                }
                finish = 0;
                cout << "max=" << max(a, b, c, d) << endl;
            }
            else
            {
                cout << "个数输入错误" << endl;
                return 0;
            }
        }
        else
        {
            clean();
        }
    }

    return 0;
}