#include <iostream>
using namespace std;

int main()
{
    int a = 1, b = 2, c = 3, d = 4, m = 1, n = 1;

    cout << "m=" << m << " n=" << n << endl;
    (m = a > b) && (n = c > d);
    cout << "m=" << m << " n=" << n << endl;

    return 0;
}