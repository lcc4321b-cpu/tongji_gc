#include <iostream>
using namespace std;

int main()
{
    int i;
    char a[10];

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    cin >> &a[3];

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    return 0;
}