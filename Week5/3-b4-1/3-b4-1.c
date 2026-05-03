//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main()
{
	const double pi = 3.14159;
	int a, b, t;

	printf("请输入三角形的两边及其夹角(角度)\n");
	scanf("%d%d%d", &a, &b, &t);

	float answer = 0.5 * a * b * sin(t / 180.0 * pi);

	printf("三角形面积为 : %.3f\n", answer);

	return 0;
}