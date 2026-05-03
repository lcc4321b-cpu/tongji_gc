#define _CRT_SECURE_NO_WARNINGS  //VSÐèÒª
#include <iostream>
using namespace std;

int main()
{
    int i;
    char a[10];

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    scanf("%s", &a[3]);

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    return 0;
}