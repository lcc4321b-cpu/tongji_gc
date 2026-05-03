#include <iostream>
#include <cmath> //VS可不加
using namespace std;

int main()
{
	double d1 = 123.456789012345678;
	double d2 = 123.456789123456789;
	cout << (d1 == d2) << endl;
	cout << (fabs(d1 - d2) < 1e-6) << endl;
	cout << (fabs(d1 - d2) < 1e-7) << endl;

	float f1 = 123.456789012345678;
	float f2 = 123.456789123456789;
	cout << (f1 == f2) << endl;
	cout << (fabs(f1 - f2) < 1e-6) << endl;
	cout << (fabs(f1 - f2) < 1e-7) << endl;

	return 0;
} //VS有两个warning