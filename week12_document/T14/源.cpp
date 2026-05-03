#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int i;
    char a[] = "Student";

    /* 数组 a 缺省长度为8，输出[0]-[6]，尾零不输出 */
    for (i = 0; i < 7; i++)
        printf("%c", a[i]);
    cout << endl; //换行

    for (i = 0; i < 7; i++)
        cout << a[i];
    cout << endl; //换行

    return 0;
}