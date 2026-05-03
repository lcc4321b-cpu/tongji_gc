//2550703 卓03 李良玉
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    const int ROW = 10;
    const int COL = 26;
    const int MINES = 50;

    char board[ROW][COL];

    // 1. 全部初始化为 '0'
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            board[i][j] = '0';
        }
    }

    // 2. 随机放置 50 颗雷
    srand((unsigned)time(NULL));   

    int placed = 0;
    while (placed < MINES)
    {
        int r = rand() % ROW;   // 0 ~ 9
        int c = rand() % COL;   // 0 ~ 25

        if (board[r][c] == '*')
        {
            // 已经有雷了，重新随机
            continue;
        }

        board[r][c] = '*';
        ++placed;
    }

    // 3. 对每个非雷格子计算其周围 8 个位置中雷的个数
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (board[i][j] == '*')
            {
                continue;
            }

            int cnt = 0;
            for (int di = -1; di <= 1; ++di)
            {
                for (int dj = -1; dj <= 1; ++dj)
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
            board[i][j] = (char)('0' + cnt);   // 存 '0'~'8'
        }
    }

    // 4. 按要求输出：
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
