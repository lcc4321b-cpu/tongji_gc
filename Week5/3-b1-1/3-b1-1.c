//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    const double pi = 3.14159;
    double r, h;
    double circle_c, circle_s, sph_s, sph_v, cyl_v;

    printf("请输入半径和高度\n");
    scanf("%lf%lf", &r, &h);

    circle_c = 2.0 * pi * r;
    circle_s = pi * r * r;
    sph_s = 4.0 * pi * r * r;
    sph_v = 4.0 / 3.0 * pi * r * r * r;
    cyl_v = circle_s * h;

    printf("%-10s : %.2lf\n", "圆周长", circle_c);
    printf("%-10s : %.2lf\n", "圆面积", circle_s);
    printf("%-10s : %.2lf\n", "圆球表面积", sph_s);
    printf("%-10s : %.2lf\n", "圆球体积", sph_v);
    printf("%-10s : %.2lf\n", "圆柱体积", cyl_v);

    return 0;
}