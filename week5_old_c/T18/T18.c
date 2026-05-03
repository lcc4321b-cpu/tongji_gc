#include <stdio.h>

#define str "Student"
int main()
{
    printf("2550703\n");//此处必须改为你的学号，否则本作业0分

    int a = 65;

    /* 第1组 */
    printf("a=%o\n", a);
    printf("a=%x\n", a);
    printf("ch=%c\n", a);
    printf("s=%s\n\n", str);

    /* 第2组 */
    printf("a=0%o\n", a);
    printf("a=0x%x\n", a);
    printf("ch=\'%c\'\n", a);
    printf("s=\"%s\"\n\n", str);

    /* 第3组 */
    double d = 0.783;
    printf("百分比=%.2f%%\n", d * 100);

    return 0;
}