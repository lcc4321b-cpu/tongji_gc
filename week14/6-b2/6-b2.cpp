//2550703 卓03 李良玉
#include <iostream>
#include <cstdio>
using namespace std;

int my_strlen(const char* s)
{
    int n = 0;
    const char* p = s;
    while (*p)
    {
        n++;
        p++;
    }
    return n;
}

bool is_palindrome(const char* s)
{
    int n = my_strlen(s);
    if (n <= 1)
        return true;

    const char* l = s;
    const char* r = s;
    while (*r)
        r++;
    r--;

    while (l < r)
    {
        if (*l != *r)
            return false;
        l++;
        r--;
    }
    return true;
}

int main()
{
    char str[82];

    cout << "请输入一个长度小于80的字符串（回文串）" << endl;

    if (fgets(str, 82, stdin) == NULL)
    {
        *str = '\0';
    }

    char* p = str;
    while (*p && *p != '\n' && *p != '\r')
        p++;
    if (*p)
        *p = '\0';

    cout << (is_palindrome(str) ? "yes" : "no") << endl;

    return 0;
}

