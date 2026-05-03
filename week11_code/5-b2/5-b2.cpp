//2550703 卓03 李良玉
#include <iostream>
using namespace std;

int main()
{
    const int N = 100;
    bool light[N + 1];
    for (int i = 1; i <= N; ++i)
    {
        light[i] = false;
    }

    // 100 个人依次操作
    for (int person = 1; person <= N; ++person)
    {
        // 该人只对自己编号的倍数开关灯
        for (int k = person; k <= N; k += person)
        {
            light[k] = !light[k];   // 取反：灭->亮，亮->灭
        }
    }

    // 输出所有亮灯的编号，中间一个空格，行尾不能多空格
    bool first = true;  // 控制空格输出
    for (int i = 1; i <= N; ++i)
    {
        if (light[i]) 
        {
            if (!first) 
            {
                cout << " ";
            }
            cout << i;
            first = false;
        }
    }
    cout << endl;

    return 0;
}

