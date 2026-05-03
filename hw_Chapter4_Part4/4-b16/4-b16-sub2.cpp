//2550703 卓03 李良玉
#include<iostream>
using namespace std;

double judge_zero(double input);

void same_answer(double a, double b)
{
	cout << "有两个相等实根：" << endl;
	cout << "x1=x2=" << judge_zero(-b / (2 * a)) << endl;
}
