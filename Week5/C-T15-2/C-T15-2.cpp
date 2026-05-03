#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "2550703" << endl;  //此处必须改为你的学号，否则本作业0分

    double a = 0.123456789012345;
    cout << "0         1         2         3" << endl;
    cout << "0123456789012345678901234567890123456789" << endl;

    cout << setw(6) << a << '*' << endl;
    cout << setw(9) << a << '*' << endl;
    cout << setw(15) << a << '*' << endl;
    cout << setw(30) << a << '*' << endl;

    return 0;
}