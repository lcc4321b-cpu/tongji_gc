#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char str1[] = "abcd", str2[] = "abcd";

    cout << strncmp(str1, str2, 3) << endl;
    cout << strncmp(str1, str2, 4) << endl;
    cout << strncmp(str1, str2, 5) << endl;
    cout << strncmp(str1, str2, 100) << endl;

    return 0;
}