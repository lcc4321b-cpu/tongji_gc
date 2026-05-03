#include <iostream>
using namespace std;

int main()
{
    int a = 8, n = 13;
    cout << (a%=4) << endl;
    cout << a << ' ' << n << endl;
    cout << (n %= a %= 4) << endl;
    cout << a << ' ' << n << endl;
    return 0;
}