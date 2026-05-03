#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;

    if (a > b)
        cout << "max=" << a << endl;
    else
        cout << "max=" << b << endl;

    a > b ? cout << "max=" << a << endl : cout << "max=" << b << endl; //1
    cout << "max=" << (a > b ? a : b) << endl; //2
    printf("max=%d", a > b ? a : b); //3

    return 0;
}