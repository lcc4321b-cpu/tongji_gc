//2550703 卓03 李良玉
#include <iostream>
using namespace std;

int main() 
{
    const int MAX_N = 20;
    int a[MAX_N+1];
    int n = 0;
    int x;

    cout << "请输入任意个正整数（升序，最多20个），0或负数结束输入" << endl;

    while (n < MAX_N)
    {
        cin >> x;
        if (x <= 0) 
        {       // 0 或负数：结束输入
            break;
        }
        a[n] = x;
        n+=1;
    }

    cin.clear();
    cin.ignore(1024, '\n');


    // 没有任何有效数据
    if (n == 0) 
    {
        cout << "无有效输入" << endl;
        return 0;
    }

    cout << "原数组为：" << endl;

    for (int i = 0; i < n; ++i) 
    {
        if (i > 0) 
        {
            cout << " ";
        }
        cout << a[i];
    }
    cout << endl;

    cout << "请输入要插入的正整数" << endl;

    int val;
    cin >> val;

    cout << "插入后的数组为：" << endl;


    int i = n - 1;
    while (i >= 0 && a[i] > val) 
    {
        if (i + 1 < MAX_N) 
        {
            a[i + 1] = a[i];
        }
        --i;
    }

    if (i + 1 < MAX_N) 
    {
        a[i + 1] = val;
        ++n;
    }

    for (int j = 0; j < n; ++j) 
    {
        if (j > 0) 
        {
            cout << " ";
        }
        cout << a[j];
    }
    cout << endl;

    return 0;
}
