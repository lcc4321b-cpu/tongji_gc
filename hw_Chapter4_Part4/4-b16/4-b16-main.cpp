//2550703 卓03 李良玉
#include<iostream>
#include<cmath>
#include"4-b16.h"
using namespace std;

double judge_zero(double input)
{
	if (input < 0.000001 && input>-0.000001)
	{
		return 0;
	}
	else
	{
		return input;
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
