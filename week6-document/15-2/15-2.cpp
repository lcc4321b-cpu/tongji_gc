#include <iostream>
using namespace std;

int main()
{
    int i;

    cout << "请输入成绩[0-100]" << endl;
    cin >> i;

    if (i < 60) {
        cout << "不及格" << endl;
        cout << "程序结束" << endl; //未缩进
    }

    return 0;
}