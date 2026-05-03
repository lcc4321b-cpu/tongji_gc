#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    char a[] = "Student";   //长度缺省为8

    cout << sizeof(a) << endl;

    printf("%c*\n", a[5]);

    cout << a[3] << '*' << endl;

    return 0;
}
//输出加*是为了确认只输出了一个字符