#include <iostream>
using namespace std;

int main()
{
    cout << (5 > 3 && 2 || 8 < 4 - !0) << endl; //ʽ1

    int a = 17, b = 18;
    cout << (5 > 3 && 2 || 8 < (a = 4) - !0, b = 5) << endl; //ʽ2
    cout << "a=" << a << " b=" << b << endl;
    return 0;
}