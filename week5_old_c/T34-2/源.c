#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    int a, b, ret;
    ret = scanf("%d %d", &a, &b);
    printf("a=%d b=%d ret=%d\n", a, b, ret);
    return 0;
}