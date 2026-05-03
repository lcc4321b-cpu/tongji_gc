//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAXN 10

// 三个圆柱的栈顶下标：空栈为 -1
int topA = -1, topB = -1, topC = -1;
// 三个圆柱上的圆盘（从下到上），多开 1 个位置做哨兵 0
int A[MAXN + 1] = { 0 };
int B[MAXN + 1] = { 0 };
int C[MAXN + 1] = { 0 };

// 全局计数变量
int frequency = 0;

// 移动函数：把一个盘从 s 柱移动到 d 柱
void move(char s, char d)
{
    int* srcTop = NULL, * dstTop = NULL;
    int* srcArr = NULL, * dstArr = NULL;

    // 源柱指针
    if (s == 'A')
    {
        srcTop = &topA;
        srcArr = A;
    }
    else if (s == 'B')
    {
        srcTop = &topB;
        srcArr = B;
    }
    else  // 'C'
    {
        srcTop = &topC;
        srcArr = C;
    }

    // 目标柱指针
    if (d == 'A')
    {
        dstTop = &topA;
        dstArr = A;
    }
    else if (d == 'B')
    {
        dstTop = &topB;
        dstArr = B;
    }
    else  // 'C'
    {
        dstTop = &topC;
        dstArr = C;
    }

    // 对应 C++: plate[d][++tower[d]] = plate[s][tower[s]--];
    (*dstTop)++;
    dstArr[*dstTop] = srcArr[*srcTop];
    srcArr[*srcTop] = 0;   // 原位置清零，作为 0 哨兵
    (*srcTop)--;
}

// 打印当前三个柱子状态
void print()
{
    int i;

    // 打印 A 柱
    printf("A:");
    for (i = 0; i <= MAXN; i++)
    {
        if (A[i] == 0)
        {
            // 预留宽度：20 - 2 * 已打印的个数
            printf("%*s", 20 - 2 * i, "");
            break;
        }
        else
        {
            printf("2d", A[i]);
        }
    }

    // 打印 B 柱
    printf("B:");
    for (i = 0; i <= MAXN; i++)
    {
        if (B[i] == 0)
        {
            printf("%*s", 20 - 2 * i, "");
            break;
        }
        else
        {
            printf("%2d", B[i]);
        }
    }

    // 打印 C 柱
    printf("C:");
    for (i = 0; i <= MAXN; i++)
    {
        if (C[i] == 0)
        {
            printf("%*s", 20 - 2 * i, "");
            break;
        }
        else
        {
            printf("%2d", C[i]);
        }
    }

    printf("\n");
}

void hanoi(int n, char src, char tmp, char dst)
{
    if (n == 1)
    {
        // 第xxxx步( n): X-->Y
        printf("第%4d 步(%2d): %c-->%c ", ++frequency, n, src, dst);
        move(src, dst);
        print();
        return;
    }
    if (n == 2)
    {
        // 三步展开
        printf("第%4d 步(%2d): %c-->%c ", ++frequency, n - 1, src, tmp);
        move(src, tmp);
        print();

        printf("第%4d 步(%2d): %c-->%c ", ++frequency, n, src, dst);
        move(src, dst);
        print();

        printf("第%4d 步(%2d): %c-->%c ", ++frequency, n - 1, tmp, dst);
        move(tmp, dst);
        print();
        return;
    }
    else
    {
        hanoi(n - 1, src, dst, tmp);

        printf("第%4d 步(%2d): %c-->%c ", ++frequency, n, src, dst);
        move(src, dst);
        print();

        hanoi(n - 1, tmp, src, dst);
        return;
    }
}

int main()
{
    int n = 0;
    char src = 0, dst = 0;
    int floor;
    int finish = 1;

    // 读取汉诺塔层数（1-10）
    while (finish)
    {
        int ch;
        printf("请输入汉诺塔的层数(1-10)\n");
        if (scanf("%d", &floor) == 1 && (floor >= 1 && floor <= MAXN))
        {
            finish = 0;
            n = floor;
        }

        // 清空到行尾
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }

    // 读取起始柱（A-C，大小写均可）
    while (1)
    {
        int c;
        char ch;
        printf("请输入起始柱 (A-C)\n");

        if (scanf(" %c", &ch) == 1)
        {
            if ('a' <= ch && ch <= 'c')
                ch = ch - 'a' + 'A';

            if (ch == 'A' || ch == 'B' || ch == 'C')
            {
                src = ch;

                // 清空到行尾
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                break;
            }
        }

        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    // 读取目标柱（A-C，且不得与起始柱相同）
    while (1)
    {
        int c;
        char ch2;
        printf("请输入目标柱 (A-C)\n");

        if (scanf(" %c", &ch2) == 1)
        {
            if ('a' <= ch2 && ch2 <= 'c')
                ch2 = ch2 - 'a' + 'A';

            if (ch2 == 'A' || ch2 == 'B' || ch2 == 'C')
            {
                if (ch2 != src)
                {
                    dst = ch2;

                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                    break;
                }
                printf("目标柱(%c)不能与起始柱(%c)相同\n", src, src);
            }
        }

        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    // 计算中间柱
    {
        char tmp = 'A' + 'B' + 'C' - src - dst;
        int i;

        // 初始化栈顶
        topA = topB = topC = -1;

        // 清零三个数组
        for (i = 0; i <= MAXN; i++)
        {
            A[i] = 0;
            B[i] = 0;
            C[i] = 0;
        }

        // 把所有盘放在起始柱 src 上（从下到上：floor, floor-1, ..., 1）
        if (src == 'A')
        {
            topA = floor - 1;
            for (i = 0; i < floor; i++)
                A[i] = floor - i;
        }
        else if (src == 'B')
        {
            topB = floor - 1;
            for (i = 0; i < floor; i++)
                B[i] = floor - i;
        }
        else // 'C'
        {
            topC = floor - 1;
            for (i = 0; i < floor; i++)
                C[i] = floor - i;
        }

        // 打印初始状态
        printf("初始:                ");
        print();

        // 递归求解
        hanoi(floor, src, tmp, dst);
    }

    return 0;
}
