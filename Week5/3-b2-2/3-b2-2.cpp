//2550703 卓03 李良玉
#include<iostream>
using namespace std;

int main()
{
	cout << "请输入一个[1..30000]间的整数：" << endl;
	int number;
	cin >> number;

	cout << "万位 : " << number / 10000 << endl;
	cout << "千位 : " << number / 1000 % 10 << endl;
	cout << "百位 : " << number / 100 % 10 << endl;
	cout << "十位 : " << number / 10 % 10 << endl;
	cout << "个位 : " << number % 10 << endl;

	return 0;
}