#include <iostream>
using namespace std;

void f()
{
    int x = 10;
}
int main()
{
    int k = 10;

    k = k + f();
    k, f();
    cout << (k, f()) << endl;
    cout << (k, f(), k + 2) << endl;

    return 0;
}