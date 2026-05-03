//2550703 卓03 李良玉
#include <iostream>
#include <limits>
#include <climits>
using namespace std;

void clean()
{
    cin.clear();
    cin.ignore(1024, '\n');
}


int min(int a=2147483647, int b = 2147483647, int c = 2147483647, int d = 2147483647)
{
    int t = (a < b ? a : b);
    if (c < t) t = c;
    if (d < t) t = d;
    return t;
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
                cout << "min=" << min(a, b) << endl;
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
                cout << "min=" << min(a, b, c) << endl;
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
                cout << "min=" << min(a, b, c, d) << endl;
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