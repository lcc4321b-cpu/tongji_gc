#include <iostream>
using namespace std;

int fun(int x)
{
    if (x > 10) {
        if (x > 20)
            return 1;
    }
    else
        return 0;
}
int main()
{
    /* 注意：输出必须改为自己学号-姓名 */
    cout << "2550703-李良玉" << endl;

    cout << fun(5) << endl;
    cout << fun(15) << endl;
    cout << fun(25) << endl;
    return 0;
}