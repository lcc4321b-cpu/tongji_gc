//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
#include<cmath>
using namespace std;

int main()
{
    const double pi = 3.14159;
    double r, h;
    cout << "请输入半径和高度" << endl;
    cin >> r >> h;

    double circle_c = 2 * pi * r;
    double circle_s = pi * r * r;
    double sph_s = 4.0 * pi * r * r;
    double sph_v = 4.0 / 3.0 * pi * r * r * r;
    double cyl_v = circle_s * h;

    cout << setiosflags(ios::fixed) << setiosflags(ios::left) << setprecision(2);
    cout << setw(10) << "圆周长" << " : " << circle_c << endl;
    cout << setw(10) << "圆面积" << " : " << circle_s << endl;
    cout << setw(10) << "圆球表面积" << " : " << sph_s << endl;
    cout << setw(10) << "圆球体积" << " : " << sph_v << endl;
    cout << setw(10) << "圆柱体积" << " : " << cyl_v << endl;

    return 0;
}