//2550703 卓03 李良玉
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

int main()
{
	int number_of_users = -100;

	//detect whether the user's input is correct
	while (number_of_users > 65 || number_of_users < -10)
	{
		cout << "请输入x的值[-10~+65]" << endl;
		cin >> number_of_users;
		if (number_of_users > 65 || number_of_users < -10)
		{
			cout << "输入非法，请重新输入" << endl;
		}
	}

	//caculate
	double sum = 1.0;
	double term = 1.0;
	int n = 1;
	while (true) {
		term = term * (static_cast<double>(number_of_users) / n); // 递推：x^n/n! = (x^(n-1)/(n-1)!) * (x/n)
		if (term < 0.000001)
		{
			break;
		}
		sum += term;
		n += 1;
	}

	//print
	cout << "e^" << number_of_users << "=" << setprecision(10) <<sum << endl;

	return 0;
}