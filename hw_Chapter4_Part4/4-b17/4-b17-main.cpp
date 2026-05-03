//2550703 卓03 李良玉
#include<iostream>
#include<cmath>
using namespace std;

void no();
void same_answer();
void different_answer();
void complex();

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

double a, b, c;

int main()
{
	cout << "请输入一元二次方程的三个系数a, b, c:" << endl;
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
		same_answer();
	}
	else if (delta > 0)
	{
		different_answer();
	}
	else
	{
		complex();
	}
	return 0;
}
