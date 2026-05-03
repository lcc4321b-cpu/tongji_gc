#include <iostream>
using namespace std;
int main()
{
    int score;
    cout << "请输入成绩[0-100]" << endl;
    cin >> score;
    switch (score / 10) {
        case 10:
        case 9:
            cout << "优" << endl;
            break;
        case 8:
            cout << "良" << endl;
            break;
        case 7:
            cout << "中" << endl;
            break;
        case 6:
            cout << "及格" << endl;
            break;
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            cout << "不及格" << endl;
            break;
        default:
            cout << "输入错误" << endl;
            break;
    }

    return 0;
}