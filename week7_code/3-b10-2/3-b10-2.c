//2550703 卓03 李良玉
#include <stdio.h>
#include <windows.h> //取系统时间

int main()
{
    LARGE_INTEGER tick, begin, end;

    QueryPerformanceFrequency(&tick);	//获得计数器频率
    QueryPerformanceCounter(&begin);	//获得初始硬件计数器计数

    /* 此处是你的程序开始 */
    int cnt = 0;

    // 依次穷举 9 个不同的数字（仅用基本循环和分支）
    for (int a = 1; a <= 9; ++a)
        for (int b = 1; b <= 9; ++b) if (b != a)
            for (int c = 1; c <= 9; ++c) if (c != a && c != b) {
                int A = 100 * a + 10 * b + c;

                for (int d = 1; d <= 9; ++d) if (d != a && d != b && d != c)
                    for (int e = 1; e <= 9; ++e) if (e != a && e != b && e != c && e != d)
                        for (int f = 1; f <= 9; ++f) if (f != a && f != b && f != c && f != d && f != e) {
                            int B = 100 * d + 10 * e + f;

                            for (int g = 1; g <= 9; ++g) if (g != a && g != b && g != c && g != d && g != e && g != f)
                                for (int h = 1; h <= 9; ++h) if (h != a && h != b && h != c && h != d && h != e && h != f && h != g)
                                    for (int i = 1; i <= 9; ++i) if (i != a && i != b && i != c && i != d && i != e && i != f && i != g && i != h) {
                                        int C = 100 * g + 10 * h + i;

                                        // 只保留 A < B < C 的组合（去掉 3! 个排列中的其它 5 种）
                                        if (A < B && B < C) {
                                            if (A + B + C == 1953) {
                                                cnt = cnt + 1;
                                                printf("No.%3d : %d+%d+%d=1953\n", cnt, A, B, C);
                                            }
                                        }
                                    }
                        }
            }


    /* 此处是你的程序结束 */

    QueryPerformanceCounter(&end);		//获得终止硬件计数器计数

    printf("计数器频率 : %lldHz\n", tick.QuadPart);
    printf("计数器计数 : %lld\n", end.QuadPart - begin.QuadPart);
    printf("%.6f秒\n", (double)(end.QuadPart - begin.QuadPart) / tick.QuadPart);

    return 0;
}