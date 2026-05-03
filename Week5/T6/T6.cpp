#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "2550703" << endl;  //此处必须改为你的学号，否则本作业0分（后续含学号的所有作业要求相同）
    short a1 = 1234, a2 = 0x1234, a3 = 01234, a4 = 0b1101001;  //常量为各进制表示正数
    //setbase(7);
    //setbase(1);

    cout << "dec:" << setbase(10) << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << endl;
    cout << "hex:" << setbase(16) << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << endl;
    cout << "oct:" << setbase(8) << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << endl;
    cout << endl;
    short b1 = -1234, b2 = -0x1234, b3 = -01234, b4 = -0b1101001;  //常量为各进制表示负数
    cout << "dec:" << setbase(10) << b1 << ' ' << b2 << ' ' << b3 << ' ' << b4 << endl;
    cout << "hex:" << setbase(16) << b1 << ' ' << b2 << ' ' << b3 << ' ' << b4 << endl;
    cout << "oct:" << setbase(8) << b1 << ' ' << b2 << ' ' << b3 << ' ' << b4 << endl;
    cout << endl;
    short c1 = 40000, c2 = 0x9876, c3 = 0171234, c4 = 0b1101010100111100;  //赋值后最高位均为1，有warning
    cout << "dec:" << setbase(10) << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4 << endl;
    cout << "hex:" << setbase(16) << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4 << endl;
    cout << "oct:" << setbase(8) << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4 << endl;
    cout << endl;
    return 0;
}