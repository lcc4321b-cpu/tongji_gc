#include <iostream>
using namespace std;

int main()
{
    char a[10];
    int i;

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    /* 直接数组名,无下标,也不加& */
    cin >> a;

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    return 0;
}