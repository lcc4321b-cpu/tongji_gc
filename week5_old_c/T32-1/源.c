#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    char c1, c2;
    scanf("%c %c", &c1, &c2); //两个%c间有空格
    printf("c1=%c c2=%c\n", c1, c2);
    return 0;
}