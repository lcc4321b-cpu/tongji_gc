//2550703 卓03 李良玉
#include <iostream>
using namespace std;

int main()
{
    // 用于存储输入的二进制字符串，长度不超过32
    char bin[40];

    // 输入提示
    cout << "请输入一个0/1组成的字符串，长度不超过32" << endl;

    // 读取用户输入的二进制字符串
    cin >> bin;

    // 将二进制字符串转换为无符号十进制整数
    unsigned long long v = 0;
    char* p = bin;  // 指向字符串的指针
    while (*p != '\0')
    {
        v = v * 2 + static_cast<unsigned long long>(*p - '0');
        p++;
    }

    // 输出转换后的十进制结果
    cout << v << endl;
    return 0;
}
