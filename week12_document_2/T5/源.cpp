#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char str1[] = "Hello";
    cout << sizeof(str1) << endl;
    cout << strlen(str1) << endl;

    char str2[] = "china\0Hello\0\0";
    cout << sizeof(str2) << endl;
    cout << strlen(str2) << endl;

    return 0;
} //读操作，不需要加_CRT_SECURE_NO_WARNINGS