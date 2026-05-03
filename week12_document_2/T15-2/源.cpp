#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    char str1[] = "abcd", str2[] = "abcde";
    int k = strcmp(str1, str2);
    if (k == 0)
        cout << "´®1 = ´®2" << endl;
    else if (k < 0)
        cout << "´®1 < ´®2" << endl;
    else
        cout << "´®1 > ´®2" << endl;

    return 0;
}