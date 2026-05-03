#include <iostream>
#include <iomanip>    //格式输出
#include <cmath>      //fabs
#include <windows.h>  //取系统时间
using namespace std;

int main()
{
    int s = 1;
    float n = 1, t = 1, pi = 0;  //语句1

    LARGE_INTEGER tick, begin, end;
    QueryPerformanceFrequency(&tick);	//取计数器频率
    QueryPerformanceCounter(&begin);	//取初始硬件定时器计数

    while (fabs(t) > 1e-7) {  //语句2
        pi = pi + t;
        n = n + 2;
        s = -s;
        t = s / n;
    }

    QueryPerformanceCounter(&end);//获得终止硬件定时器计数

    pi = pi * 4;
    cout << "n=" << setprecision(10) << n << endl;
    cout << "pi=" << setiosflags(ios::fixed) << setprecision(9) << pi << endl;

    cout << "计数器频率：" << tick.QuadPart << "Hz" << endl;
    cout << "时钟计数  ：" << end.QuadPart - begin.QuadPart << endl;
    cout << setprecision(6) << (end.QuadPart - begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

    return 0;
}