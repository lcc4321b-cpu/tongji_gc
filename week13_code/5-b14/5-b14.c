//2550703 卓03 李良玉
/* 互验名单：2551163 陈佳骏  2551102 王薛皓  2550704 孙湛桐  2550735 邵梓懿  2551599覃雷伟俊  2552845 孙赞*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    #define ROW 10
    #define COL 26
    char board[ROW][COL];

    int i, j;

    /* 1. 读取 10x26 个字符，过滤空格和换行：*/
    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {
            char ch;
            scanf(" %c", &ch) != 1;
            board[i][j] = ch;
        }
    }

    /* 2. 统计星号个数 */
    int star_count = 0;
    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {
            if (board[i][j] == '*')
            {
                ++star_count;
            }
        }
    }

    if (star_count != 50)
    {
        printf("错误1\n");
        return 0;
    }

    /* 3. 在 * 个数正确的前提下，重新计算每个非 * 位置的周围雷数，检查是否一致 */
    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < COL; ++j)
        {
            if (board[i][j] == '*')
            {
                continue;
            }

            int cnt = 0;
            int di, dj;

            for (di = -1; di <= 1; ++di)
            {
                for (dj = -1; dj <= 1; ++dj)
                {
                    if (di == 0 && dj == 0)
                    {
                        continue;
                    }

                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < ROW && nj >= 0 && nj < COL)
                    {
                        if (board[ni][nj] == '*')
                        {
                            ++cnt;
                        }
                    }
                }
            }

            char should_be = (char)('0' + cnt);
            if (board[i][j] != should_be)
            {
                printf("错误2\n");
                return 0;
            }
        }
    }

    /* 4. 所有检查通过 */
    printf("正确\n");
    return 0;
}
