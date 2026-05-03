#define _CRT_SECURE_NO_WARNINGS  //VS需要
#include <iostream>
using namespace std;

int main()
{
    char a[10];
    int i;

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    /* 直接数组名，无下标，也不加&，
       因为C/C++规定，数组名代表数组的起始地址 */
    scanf("%s", a);

    for (i = 0; i < 10; i++)
        cout << int(a[i]) << endl;

    return 0;
}