#include <iostream>
using namespace std;

void fun(int x)
{
    cout << "x1=" << x << endl;
    x = 5;
    cout << "x2=" << x << endl;
}

int main()
{
    /* 注意：输出必须改为自己学号-姓名 */
    cout << "2550703-李良玉" << endl;

    int k = 15;
    cout << "k1=" << k << endl;
    fun(k);
    cout << "k2=" << k << endl;

    return 0;
}