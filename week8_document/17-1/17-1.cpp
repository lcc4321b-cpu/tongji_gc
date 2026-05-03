#include <iostream>
using namespace std;
int main()
{
    int x = 10, y = 15;
    fun(x, y);
    return 0;
}
int fun(int x, int y);
void f()
{
    fun(10, 15);
}
int fun(int x, int y)
{
    cout << "x=" << x << endl;
    cout << "y=" << y << endl;
    return 0;
}