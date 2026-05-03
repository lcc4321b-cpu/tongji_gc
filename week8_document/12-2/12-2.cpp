#include <iostream>
using namespace std;

int fun(int x)
{
    if (x > 1)
        return 1;
    else if (x <= 1)
        return 0;
} //if+else if已覆盖int型的全部表示范围

int main()
{
    /* 注意：输出必须改为自己学号-姓名 */
    cout << "2550703-李良玉" << endl;

    cout << fun(0) << endl;
    cout << fun(2) << endl;
    return 0;
}