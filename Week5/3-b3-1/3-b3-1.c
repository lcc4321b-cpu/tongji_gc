//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	printf("请输入[0-100亿)之间的数字：\n");

	double original_value;
	long number, noriginal_value;
	scanf("%lf", &original_value);
	original_value /= 10;
	number = original_value;
	original_value -= number;
	original_value *= 1000;
	original_value += 0.5;
	noriginal_value = original_value;

	printf("%-8s : %d\n", "十亿位", number / 100000000);
	printf("%-8s : %d\n", "亿位", number / 10000000 % 10);
	printf("%-8s : %d\n", "千万位", number / 1000000 % 10);
	printf("%-8s : %d\n", "百万位", number / 100000 % 10);
	printf("%-8s : %d\n", "十万位", number / 10000 % 10);
	printf("%-8s : %d\n", "万位", number / 1000 % 10);
	printf("%-8s : %d\n", "千亿位", number / 100 % 10);
	printf("%-8s : %d\n", "百位", number / 10 % 10);
	printf("%-8s : %d\n", "十位", number  % 10);
	printf("%-8s : %d\n", "圆", noriginal_value /100);
	printf("%-8s : %d\n", "角", noriginal_value / 10 % 10);
	printf("%-8s : %d\n", "分", noriginal_value % 10);

	return 0;
}
