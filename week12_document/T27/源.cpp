#define _CRT_SECURE_NO_WARNINGS  //VSÐèÒª
#include <iostream>
using namespace std;

int main()
{
    char a[3][30] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                   "abcdefghijklmnopqrstuvwxyz",
                   "0123456789" };

    cin >> a[1];
    cout << "a[0]=" << a[0] << endl;
    cout << "a[1]=" << a[1] << endl;
    cout << "a[2]=" << a[2] << endl;

    return 0;
}