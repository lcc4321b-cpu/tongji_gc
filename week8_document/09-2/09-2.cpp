#include <iostream>
using namespace std;

short fun3()
{
    long a = 70000;
    return a;
}

int main()
{
    /* 注意：输出必须改为自己学号-姓名 */
    cout << "2550703-李良玉" << endl;

    long d;
    d = fun3();
    cout << d << endl;

    return 0;
}