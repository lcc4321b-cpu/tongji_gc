#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    char c1, c2;
    scanf("%c%c", &c1, &c2); //两个%c间无空格
    printf("c1=%d c2=%d\n", c1, c2);
    return 0;
}