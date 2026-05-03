//2550703 ×¿03 ÀîÁ¼Óñ
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>


int main() 
{
    for (int i = 1; i <= 9; i+=1) 
    {
        for (int j = 1; j <= i; j+=1) 
        {
            int gap = (j < i) ? ((i * j) < 10 ? 3 : 2) : 0;
            printf("%dx%d=%d%*s", j, i, (i * j), gap, "");
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
