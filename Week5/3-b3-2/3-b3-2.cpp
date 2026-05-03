//2550703 卓03 李良玉
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	cout << "请输入[0-100亿)之间的数字：" << endl;

	double ori;
	cin >> ori;
	ori /= 10;
	int number = ori;
	ori -= number;
	ori *= 1000;
	
	ori += 0.5;
	int nori = (int)ori;

	cout << setiosflags(ios::left);
	cout << setw(8) << "十亿位" << " : " << number / 100000000 << endl;
	cout << setw(8) << "亿位" << " : " << number / 10000000 % 10 << endl;
	cout << setw(8) << "千万位" << " : " << number / 1000000 % 10 << endl;
	cout << setw(8) << "百万位" << " : " << number / 100000 % 10 << endl;
	cout << setw(8) << "十万位" << " : " << number / 10000 % 10 << endl;
	cout << setw(8) << "万位" << " : " << number / 1000 % 10 << endl;
	cout << setw(8) << "千位" << " : " << number / 100 % 10 << endl;
	cout << setw(8) << "百位" << " : " << number / 10 % 10 << endl;
	cout << setw(8) << "十位" << " : " << number % 10 << endl;
	cout << setw(8) << "圆" << " : " << nori / 100 << endl;
	cout << setw(8) << "角" << " : " << nori / 10 % 10 << endl;
	cout << setw(8) << "分" << " : " << nori % 10 << endl;

	return 0;
}
