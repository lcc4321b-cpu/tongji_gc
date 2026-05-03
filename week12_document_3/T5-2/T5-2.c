#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    char str[80];
    int k = 123, ret;
    double pi = 3.1415925;

    ret = sprintf(str, "k=%6dpi=%10.2f", k, pi); //本句与程序1有差异，其它语句相同
    printf("ret : %d\n", ret);
    printf("str : %s\n", str);

    return 0;
}