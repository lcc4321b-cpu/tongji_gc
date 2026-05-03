#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    cout << "2550703"<<endl;

    int a = 0xA3B4F5D6;
    cout << setbase(16) << a << endl;
    cout << setiosflags(ios::uppercase) << a << endl;
    cout << resetiosflags(ios::uppercase) << a << endl;
    cout << setiosflags(ios::uppercase) << a << endl;
    //第2行输出:16进制中的A-F为小写
    //第3行输出:16进制中的A-F为大写
    //第4行输出:16进制中的A-F为小写
    //第5行输出:16进制中的A-F为大写

    return 0;
}