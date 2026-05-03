#define _CRT_SECURE_NO_WARNINGS //VSÐèÒª
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int i;
    char a[] = "student", b[] = "hellochina";
    strcpy(a, b);
    cout << a << endl;
    for (i = 0; a[i] != '\0'; i++)
        cout << int(a[i]) << ' ';
    cout << endl;

    return 0;
}