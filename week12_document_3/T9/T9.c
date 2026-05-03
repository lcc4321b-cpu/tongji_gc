#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int w;
    char m[13];
    char a[41];
    char n[40];
    printf("请输入长度[3..12]间的字符串及显示宽度[len+1..20]\n");
    scanf("%s %d", m, &w);
    printf("01234567890123456789\n"); //标尺
    sprintf(a, "%%-%ds*\n", w);
    sprintf(n, "%s ", m);
    printf(a, n);
    return 0;
}