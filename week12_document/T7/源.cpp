#define _CRT_SECURE_NO_WARNINGS  //VSÐèÒª
#include <iostream>
using namespace std;

int main()
{
    char a[10];
    int i;

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    scanf("%c%c", &a[3], &a[7]);
    scanf("%c", &a[0]);

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    return 0;
}