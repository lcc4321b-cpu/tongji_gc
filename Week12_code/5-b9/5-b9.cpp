//2550703 卓03 李良玉
#include <iostream>
using namespace std;

// 检查所有行是否符合数独要求
bool check_rows(int a[9][9])
{
    for (int i = 0; i < 9; ++i)
    {
        bool used[10] = { false };
        for (int j = 0; j < 9; ++j) 
        {
            int v = a[i][j];
            if (used[v])
            {
                return false;
            }
            used[v] = true;
        }
    }
    return true;
}

// 检查所有列
bool check_cols(int a[9][9])
{
    for (int j = 0; j < 9; ++j) 
    {
        bool used[10] = { false };
        for (int i = 0; i < 9; ++i) 
        {
            int v = a[i][j];
            if (used[v])
            {
                return false;
            }
            used[v] = true;
        }
    }
    return true;
}

// 检查所有 3x3 小九宫格
bool check_blocks(int a[9][9])
{
    for (int br = 0; br < 3; ++br) 
    {
        for (int bc = 0; bc < 3; ++bc) 
        {
            bool used[10] = { false };
            for (int i = 0; i < 3; ++i) 
            {
                for (int j = 0; j < 3; ++j) 
                {
                    int r = br * 3 + i;
                    int c = bc * 3 + j;
                    int v = a[r][c];
                    if (used[v])
                    {
                        return false;
                    }
                    used[v] = true;
                }
            }
        }
    }
    return true;
}

int main()
{
    int grid[9][9];
    cout << "请输入9*9的矩阵，值为1-9之间" << endl;
    for (int i = 0; i < 9; ++i) 
    {
        for (int j = 0; j < 9; )
        {
            int x;
            if (!(cin >> x)) 
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "请重新输入第1行1列(行列均从1开始计数)的值" << endl;
                continue;
            }
            if (x < 1 || x > 9) 
            {
                cout << "请重新输入第" << i + 1 << "行" << j + 1 << "列(行列均从1开始计数)的值" << endl;
                continue;
            }
            grid[i][j] = x;
            ++j;
        }
    }

    bool ok = true;
    if (!check_rows(grid))
    {
        ok = false;
    }
    if (ok && !check_cols(grid))
    {
        ok = false;
    }
    if (ok && !check_blocks(grid))
    {
        ok = false;
    }

    if (ok) 
    {
        cout << "是数独的解" << endl;
    }
    else 
    {
        cout << "不是数独的解" << endl;
    }

    return 0;
}
