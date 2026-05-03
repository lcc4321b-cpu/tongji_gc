//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int number;	

	printf("请输入一个[1..30000]间的整数：\n");
	scanf("%d", &number);

	printf("万位 : %d\n", number / 10000);
	printf("千位 : %d\n", number / 1000 % 10);
	printf("百位 : %d\n", number / 100 % 10);
	printf("十位 : %d\n", number / 10 % 10);
	printf("个位 : %d\n", number % 10);

	return 0;
}