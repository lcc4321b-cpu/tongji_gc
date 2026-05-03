#include <iostream>
using namespace std;

int fun(int x, int y)
{
    cout << "x=" << x << endl;
    cout << "y=" << y << endl;
    return 0;
}
int main()
{
    int x = 10, y = 15;
    int fun(int x, int y); //mainµÄµÚ2¾ä
    return 0;
}