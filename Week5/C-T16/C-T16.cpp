#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "2550703" << endl;  //此处必须改为你的学号，否则本作业0分

    int a = 12345;
    cout << "0         1         2         3" << endl;
    cout << "0123456789012345678901234567890123456789" << endl;

    cout << setfill('=') << setw(10) << a << '#' << setw(10) << a + 1 << '*' << endl;
    cout << setw(15) << setfill('-') << a << '#' << a + 1 << '*' << endl;

    return 0;
}