//2550703 卓03 李良玉
#include<iostream>
#include<cmath>
using namespace std;


double judge_zero(double input)
{
	if (input < 0.000001&&input>-0.000001)
	{
		return 0;
	}
	else
	{
		return input;
	}
}

void no()
{
	cout << "不是一元二次方程" << endl;
	return;
}
void same_answer(double a, double b)
{
	cout << "有两个相等实根：" << endl;
	cout << "x1=x2=" << judge_zero(-b / (2 * a)) << endl;
}
void different_answer(double a, double b, double c)
{
	cout << "有两个不等实根：" << endl;
	double x_1 = judge_zero(-b / (2 * a) + sqrt((b * b - 4 * a * c)) / 2 / a);
	double x_2 = judge_zero(-b / (2 * a) - sqrt((b * b - 4 * a * c)) / 2 / a);
	cout << "x1=" << x_1 << endl;
	cout << "x2=" << x_2 << endl;
}
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


int main()
{
	cout << "请输入一元二次方程的三个系数a, b, c:" << endl;
	double a, b, c;
	cin >> a >> b >> c;
	a = judge_zero(a);
	b = judge_zero(b);
	c = judge_zero(c);
	double delta = judge_zero(b * b - 4 * a * c);
	if (a == 0)
	{
		no();
	}
	else if (delta == 0)
	{
		same_answer(a, b);
	}
	else if (delta > 0)
	{
		different_answer(a, b, c);
	}
	else
	{
		complex(a, b, c);
	}
	return 0;
}
