#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int w,p;
    double number;
    char mess[128];
    printf("请输入double型数据及显示总宽度、小数点位数\n");
    scanf("%lf %d %d", &number, &w, &p);
    printf("01234567890123456789\n"); //标尺
    sprintf(mess, "%%%d.%dlf*\n", w, p);
    printf(mess, number);
    return 0;
}