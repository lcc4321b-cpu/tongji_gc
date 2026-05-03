//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 1000

int main(void)
{
    int score[MAX_N];
    int cnt[101];
    int n = 0;
    int x;
    int i;
    int ch;

    for (i = 0; i <= 100; ++i)
    {
        cnt[i] = 0;
    }

    printf("请输入成绩（最多1000个），负数结束输入\n");

    while (n < MAX_N)
    {
        if (scanf("%d", &x) != 1)
        {
            // 读取失败就结束
            break;
        }
        if (x < 0)
        {
            break;
        }
        score[n] = x;
        n++;
        cnt[x]++;
    }

    // 模拟 cin.ignore(1024, '\n');
    // 把当前行剩余内容读掉
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* do nothing */
    }

    if (n == 0)
    {
        printf("无有效输入\n");
        return 0;
    }

    printf("输入的数组为:\n");

    for (i = 0; i < n; ++i)
    {
        printf("%d", score[i]);
        if ((i + 1) % 10 == 0 || i == n - 1)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }

    printf("分数与人数的对应关系为:\n");

    for (i = 100; i >= 0; --i)
    {
        if (cnt[i] >= 1)
        {
            printf("%d %d\n", i, cnt[i]);
        }
    }

    return 0;
}
