
#define _CRT_SECURE_NO_WARNINGS //VSÐèÒª
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int i;
    char a[] = "student", b[] = "hello\0china";
    strcpy(a, b);
    cout << a << endl;
    for (i = 0; i < 8; i++)
        cout << int(a[i]) << ' ';
    cout << endl;

    return 0;
}