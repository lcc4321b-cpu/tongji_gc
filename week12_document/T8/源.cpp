#include <iostream>
using namespace std;

int main()
{
    char a[10];
    int i;

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    cin >> a[3] >> a[7];
    cin >> a[0];

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    return 0;
}