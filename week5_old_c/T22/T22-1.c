#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int a, ret;
    ret = scanf("%d", &a);
    printf("a=%d, ret=%d\n", a, ret);
    return 0;
}