#include <iostream>
using namespace std;
int main()
{
    bool k;

    k = 'A';
    cout << k << ' ' << (int)k << endl;

    k = 0;
    cout << k << ' ' << (int)k << endl;

    k = 256;
    cout << k << ' ' << (int)k << endl;

    char c = 256;
    cout << (int)c << endl;

    return 0;
}