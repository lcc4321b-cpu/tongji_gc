#include <iostream>
using namespace std;

int main() 
{
    int a = 3, n = 7;
    cout << (a += a - n) << endl;
    cout << a <<' '<< n << endl;
    return 0;
}