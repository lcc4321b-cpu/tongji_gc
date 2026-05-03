#define _CRT_SECURE_NO_WARNINGS  //VSÐèÒª
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int i;
    char a[] = "student", b[] = "hello";
    strncpy(a, &b[2], 2);
    cout << a << endl;
    for (i = 0; i < 8; i++)
        cout << int(a[i]) << ' ';
    cout << endl;

    return 0;
}