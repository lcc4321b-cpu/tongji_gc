#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int a, b;

    scanf("%3d %*2d %3d", &a, &b);
    printf("a=%d b=%d\n", a, b);

    return 0;
}