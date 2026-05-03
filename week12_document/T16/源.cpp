#include <iostream>
using namespace std;

int main()
{
    //注意：不能以字符串方式初始化
    char a[5] = { 'C','h','i','n','a' };

    printf("%s\n", a);
    cout << a << endl;

    return 0;
}