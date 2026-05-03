//2550703 卓03 李良玉
#include<iostream>
using namespace std;

double judge_zero(double input);

void complex(double a, double b, double c)
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
