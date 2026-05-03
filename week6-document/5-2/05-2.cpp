#include <iostream>
using namespace std;

int main()
{
    int a = 3, b = 2, c = 1, d;
    d = a > b > c;
    cout << d << endl;
    d = a < b < c;
    cout << d << endl;
    d = b > a < c;
    cout << d << endl;
    return 0;
}