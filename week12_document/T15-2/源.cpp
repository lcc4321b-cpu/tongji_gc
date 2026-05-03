#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    char a[] = "Student\0china";
    cout << sizeof(a) << endl;

    printf("%s*\n", a);
    cout << a << '*' << endl;
    cout << a[12] << endl;

    return 0;
}