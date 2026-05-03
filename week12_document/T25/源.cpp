#include <iostream>
using namespace std;

int main()
{
    char a[3][30] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                   "abcdefghijklmnopqrstuvwxyz",
                   "0123456789" };
    // 单个字符输出(数组名+双下标)
    printf("a[0][2]=%c\n", a[0][2]);
    cout << "a[1][20]=" << a[1][20] << endl;

    // 字符串输出(数组名+单下标)
    printf("a[0]=%s\n", a[0]);
    cout << "a[2]=" << a[2] << endl;

    return 0;
}