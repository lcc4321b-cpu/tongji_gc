// 2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int x;
    int good;        
    while (1) {
        printf("请输入x的值[0-100] : ");
        int rc = scanf("%d", &x);   
        good = (rc == 1);           

        if (good == 1 && (x >= 0 && x <= 100))
        {
            break;
        }
        else if (good == 0) 
        {
            clearerr(stdin); 
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {

            }
        }
        printf("输入有错[ret=%d x=%d],请重新输入\n", good, x);
    }

    printf("ret=%d x=%d\n", good, x);

    return 0;
}
