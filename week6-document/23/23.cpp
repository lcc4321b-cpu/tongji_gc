#include <iostream>
using namespace std;
int main()
{
    const int k = 5;  //1
    int score;      //2
    cout << "请输入成绩[0-100]" << endl;
    cin >> score;
    switch (score / 10) {
        case 10:
        case 9:
            cout << "优" << endl;
            break;
            //      case 6:  //3
        case 4 + 2:
            cout << "及格" << endl;
            break;
        default:
            cout << "输入错误" << endl;
            break;
        case k + 2:
            cout << "中" << endl;
            break;
        case 8:
            cout << "良" << endl;
            break; //4
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            cout << "不及格" << endl;
            break;
    }

    return 0;
}