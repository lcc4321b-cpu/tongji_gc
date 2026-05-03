//2550703 卓03 李良玉
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main()
{
	const double pi = 3.14159;

	cout << "请输入三角形的两边及其夹角(角度)" << endl;
	int a, b, t;
	cin >> a >> b >> t;

	float answer = 0.5 * a * b * sin(t / 180.0 * pi);

	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "三角形面积为 : " << answer << endl;

	return 0;
}