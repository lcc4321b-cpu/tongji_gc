#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "2550703" << endl;

    int a = 123, b = -123;

    cout << b << " " << a << endl;
    cout << setiosflags(ios::showpos) << b << " " << a << endl;
    cout << resetiosflags(ios::showpos) << b << " " << a << endl;

    return 0;
}