//2550703 卓03 李良玉
#include<iostream>
using namespace std;

double judge_zero(double input);

void different_answer(double a, double b, double c)
{
	cout << "有两个不等实根：" << endl;
	double x_1 = judge_zero(-b / (2 * a) + sqrt((b * b - 4 * a * c)) / 2 / a);
	double x_2 = judge_zero(-b / (2 * a) - sqrt((b * b - 4 * a * c)) / 2 / a);
	cout << "x1=" << x_1 << endl;
	cout << "x2=" << x_2 << endl;
}
