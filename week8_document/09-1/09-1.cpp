#include <iostream>
using namespace std;

int fun(short x)
{
    cout << "x=" << x << endl;
    return 0;
}

int main()
{
    /* 注意：输出必须改为自己学号-姓名 */
    cout << "2550703-李良玉" << endl;

    long k = 70000;
    fun(k);
    cout << "k=" << k << endl;

    return 0;
}