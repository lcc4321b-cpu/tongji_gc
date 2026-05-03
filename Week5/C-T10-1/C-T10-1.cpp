#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    cout << "2550703" << endl;  //此处必须改为你的学号，否则本作业0分

    float f1 = 1234.5678F;
    float f2 = 8765.4321F;

    /* 第1组：不设precision */
    cout << f1 << ' ' << f2 << endl;
    cout << setiosflags(ios::fixed) << f1 << ' ' << f2 << endl;

    /* 第2组：设置precision */
    cout << endl;
    cout << setprecision(1) << f1 << ' ' << f2 << endl;
    cout << setprecision(4) << f1 << ' ' << f2 << endl;
    cout << setprecision(7) << f1 << ' ' << f2 << endl;
    cout << setprecision(10) << f1 << ' ' << f2 << endl;
    cout << setprecision(25) << f1 << ' ' << f2 << endl;

    return 0;
}
