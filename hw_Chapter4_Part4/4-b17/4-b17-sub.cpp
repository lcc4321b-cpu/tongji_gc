//2550703 卓03 李良玉
#include<iostream>
#include<cmath>
using namespace std;
extern double a, b, c;
double judge_zero(double input);

void no()
{
	cout << "不是一元二次方程" << endl;
	return;
}
void same_answer()
{
	cout << "有两个相等实根：" << endl;
	cout << "x1=x2=" << judge_zero(-b / (2 * a)) << endl;
}
void different_answer()
{
	cout << "有两个不等实根：" << endl;
	double x_1 = judge_zero(-b / (2 * a) + sqrt((b * b - 4 * a * c)) / 2 / a);
	double x_2 = judge_zero(-b / (2 * a) - sqrt((b * b - 4 * a * c)) / 2 / a);
	cout << "x1=" << x_1 << endl;
	cout << "x2=" << x_2 << endl;
}
void complex()
{
	cout << "有两个虚根：" << endl;
	if (judge_zero(-b / (2 * a)) == 0)
	{
		if (judge_zero(b * b - 4 * a * c) / 4 / a / a == -1)
		{
			cout << "x1=i" << endl;
			cout << "x2=-i" << endl;
			return;
		}
		cout << "x1=" << fabs(judge_zero(sqrt((-b * b + 4 * a * c)) / 2 / a)) << "i" << endl;
		cout << "x2=-" << fabs(judge_zero(sqrt((-b * b + 4 * a * c)) / 2 / a)) << "i" << endl;
		return;
	}
	else
	{
		if (judge_zero(b * b - 4 * a * c) == 1)
		{
			cout << "x1=" << judge_zero(-b / (2 * a)) << "+i" << endl;
			cout << "x2=" << judge_zero(-b / (2 * a)) << "-i" << endl;
			return;
		}
		cout << "x1=" << judge_zero(-b / (2 * a)) << "+" << fabs(judge_zero(sqrt((-b * b + 4 * a * c)) / 2 / a)) << "i" << endl;
		cout << "x2=" << judge_zero(-b / (2 * a)) << "-" << fabs(judge_zero(sqrt((-b * b + 4 * a * c)) / 2 / a)) << "i" << endl;
		return;
	}
}
