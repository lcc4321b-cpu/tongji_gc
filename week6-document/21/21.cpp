#include <iostream>
using namespace std;

int main()
{
    int a = 1, b = 2;

    a == 1 ? "Hello" : 123;              //±àÒë±¨´í

    a > b ? cout << a : printf("%d", b); //±àÒë±¨´í

    a == 1 ? 'A' : 123;                  //±àÒëÕýÈ·

    return 0;
}