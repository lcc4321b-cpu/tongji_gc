/* 班级 学号 姓名 */

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"
#include "hanoi.h"

/* ----------------------------------------------------------------------------------

     本文件功能：
    1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数
    2、存放允许的静态全局变量（步数、延时、盘面数组）
    3、实现唯一的递归函数 + 若干共用函数（字符/图形/游戏）

     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、允许定义静态全局变量，数量尽量少
    3、静态局部变量数量不限制，但也建议少用

   ----------------------------------------------------------------------------------- */

   /* ===================== 允许的静态全局变量 ===================== */

   // 总步数
static int g_step = 0;

// 延时：-1 表示按键演示，0 表示无延时，>0 表示 Sleep(ms)
static int g_delay_ms = 0;

// 每根柱子的“栈顶”（-1 表示空）
static int g_top[3] = { -1, -1, -1 };

// 3 根柱子的盘子编号，底层下标为 0，递增向上，0 表示无盘
static int g_plate[3][MAX_LAYER] = { 0 };

/* ===================== 盘面数据函数实现 ===================== */

int tower_index_from_char(char ch)
{
    if ('a' <= ch && ch <= 'c') ch = char(ch - 'a' + 'A');
    return ch - 'A';   // 'A'->0, 'B'->1, 'C'->2
}

char tower_char_from_index(int idx)
{
    return char('A' + idx);
}

int get_top(int pegIndex)
{
    return g_top[pegIndex];
}

void set_top(int pegIndex, int newTop)
{
    g_top[pegIndex] = newTop;
}

int get_plate(int pegIndex, int diskIndex)
{
    return g_plate[pegIndex][diskIndex];
}

void set_plate(int pegIndex, int diskIndex, int value)
{
    g_plate[pegIndex][diskIndex] = value;
}

// 初始化：所有盘子堆在 srcIndex 上
void init_towers(int n, int srcIndex)
{
    int p, i;
    g_step = 0;

    for (p = 0; p < 3; p++)
    {
        g_top[p] = -1;
        for (i = 0; i < MAX_LAYER; i++)
        {
            g_plate[p][i] = 0;
        }
    }

    for (i = 0; i < n; i++)
    {
        g_plate[srcIndex][i] = n - i;  // 底层最大
        g_top[srcIndex] = i;
    }
}

/* ===================== 步数 + 提示输出 ===================== */

static void show_step_info(int disk, int fromPeg, int toPeg)
{
    cct_gotoxy(0, Status_Line_Y - 1);
    cout << "步数：" << setw(6) << g_step;

    if (disk > 0)
    {
        cout << "    移动：" << disk << "# "
            << tower_char_from_index(fromPeg)
            << " --> "
            << tower_char_from_index(toPeg)
            << "      ";
    }
    else
    {
        cout << "                                         ";
    }
}

/* ===================== 字符伪图形：画三根柱子 ===================== */

void draw_three_towers_char(int n)
{
    // 利用 MenuItem4 起点 + Underpan 偏移，保证和 PDF 一致
    int baseX_A = MenuItem4_Start_X + Underpan_A_X_OFFSET;
    int baseY = MenuItem4_Start_Y + Underpan_A_Y_OFFSET;

    int baseX_B = baseX_A + Underpan_Distance;
    int baseX_C = baseX_B + Underpan_Distance;

    // 底座
    cct_gotoxy(baseX_A - 4, baseY);
    cout << "========";
    cct_gotoxy(baseX_B - 4, baseY);
    cout << "========";
    cct_gotoxy(baseX_C - 4, baseY);
    cout << "========";

    // 立柱：画 n+1 行
    for (int i = 1; i <= n + 1; i++)
    {
        cct_gotoxy(baseX_A, baseY - i);
        cout << "|";
        cct_gotoxy(baseX_B, baseY - i);
        cout << "|";
        cct_gotoxy(baseX_C, baseY - i);
        cout << "|";
    }

    // A/B/C 标签
    cct_gotoxy(baseX_A, baseY + 1);
    cout << "A";
    cct_gotoxy(baseX_B, baseY + 1);
    cout << "B";
    cct_gotoxy(baseX_C, baseY + 1);
    cout << "C";
}

/* ===================== 字符伪图形：纵向画盘子 ===================== */

void draw_vertical_state_char(int n)
{
    int baseX_A = MenuItem4_Start_X + Underpan_A_X_OFFSET;
    int baseY = MenuItem4_Start_Y + Underpan_A_Y_OFFSET;

    int baseX[3];
    baseX[0] = baseX_A;
    baseX[1] = baseX_A + Underpan_Distance;
    baseX[2] = baseX[1] + Underpan_Distance;

    // 先清盘子区域（大概范围）
    for (int row = baseY - n - 2; row <= baseY + 1; row++)
    {
        if (row < 0) continue;
        cct_gotoxy(MenuItem4_Start_X, row);
        cout << "                                                                                ";
    }

    // 重画立柱
    draw_three_towers_char(n);

    // 再画盘子
    for (int p = 0; p < 3; p++)
    {
        for (int i = 0; i <= g_top[p]; i++)
        {
            int disk = g_plate[p][i];
            if (disk <= 0) continue;

            int fromBottom = i;                 // 0 为底层
            int y = baseY - fromBottom - 1;     // 向上排

            int halfWidth = 1 + disk;           // 决定盘子的宽度
            cct_gotoxy(baseX[p] - halfWidth, y);
            for (int k = 0; k < 2 * halfWidth + 1; k++)
            {
                cout << "*";
            }
        }
    }
}

/* ===================== 横向数组输出（菜单 3/4/8） ===================== */

void draw_horizontal_state(int n, int menuItem)
{
    int startX, startY;
    if (menuItem == 4)
    {
        startX = MenuItem4_Start_X;
        startY = MenuItem4_Start_Y;
    }
    else if (menuItem == 8)
    {
        startX = MenuItem8_Start_X;
        startY = MenuItem8_Start_Y;
    }
    else
    {
        // 菜单 3：简单放在 MenuItem4 上方 2 行
        startX = MenuItem4_Start_X;
        startY = MenuItem4_Start_Y - 2;
    }

    for (int p = 0; p < 3; p++)
    {
        cct_gotoxy(startX, startY + p);
        cout << char('A' + p) << ": ";

        for (int i = 0; i < n; i++)
        {
            int disk = g_plate[p][i];
            if (disk == 0)
                cout << setw(2) << ".";
            else
                cout << setw(2) << disk;
        }
    }
}

/* ===================== HDC 彩色绘制 ===================== */

void draw_vertical_state_hdc(int n)
{
    // 清 HDC 区域
    hdc_cls();

    // 画三个底盘和立柱
    for (int p = 0; p < 3; p++)
    {
        int baseX = HDC_Start_X + p * HDC_Underpan_Distance;
        int baseY = HDC_Start_Y;

        // 底盘：宽度设为 6 * HDC_Base_Width，高度 HDC_Base_High
        hdc_rectangle(baseX,
            baseY,
            HDC_Base_Width * 6,
            HDC_Base_High,
            HDC_COLOR[MAX_LAYER + 1]); // 基座颜色

        // 立柱
        int centerX = baseX + (HDC_Base_Width * 3);
        hdc_rectangle(centerX - HDC_Base_Width / 2,
            HDC_Top_Y,
            HDC_Base_Width,
            baseY - HDC_Top_Y,
            HDC_COLOR[MAX_LAYER + 1]);
    }

    // 画盘子
    for (int p = 0; p < 3; p++)
    {
        int baseX = HDC_Start_X + p * HDC_Underpan_Distance;
        int baseY = HDC_Start_Y;

        for (int i = 0; i <= g_top[p]; i++)
        {
            int disk = g_plate[p][i];
            if (disk <= 0) continue;

            int fromBottom = i;
            int y = baseY - (fromBottom + 1) * HDC_Base_High;

            // 盘子的宽度：基础宽度 * (3 + 2 * disk)，越大越宽
            int halfWidth = (3 + 2 * disk) * HDC_Base_Width / 2;
            int centerX = baseX + (HDC_Base_Width * 3);
            int left = centerX - halfWidth;
            int width = halfWidth * 2;

            int colorIndex = disk;
            if (colorIndex < 0) colorIndex = 0;
            if (colorIndex > MAX_LAYER + 1) colorIndex = MAX_LAYER + 1;

            hdc_rectangle(left,
                y,
                width,
                HDC_Base_High,
                HDC_COLOR[colorIndex]);
        }
    }
}

/* ===================== 共用移动函数（菜单 7/8/9） ===================== */

void move_one_disk_common(
    int fromPeg,
    int toPeg,
    int totalLayers,
    int mode
)
{
    int fromTop = get_top(fromPeg);
    if (fromTop < 0) return;  // 无盘可移

    int disk = get_plate(fromPeg, fromTop);

    // 从源柱移走
    set_plate(fromPeg, fromTop, 0);
    set_top(fromPeg, fromTop - 1);

    // 放到目标柱顶部
    int toTop = get_top(toPeg) + 1;
    set_top(toPeg, toTop);
    set_plate(toPeg, toTop, disk);

    // 步数+提示
    g_step++;
    show_step_info(disk, fromPeg, toPeg);

    // 根据 mode 选择表现形式
    if (mode == 7 || mode == 9)
    {
        draw_vertical_state_char(totalLayers);
        draw_horizontal_state(totalLayers, 3);
    }
    else if (mode == 8)
    {
        draw_vertical_state_hdc(totalLayers);
        draw_horizontal_state(totalLayers, 8);
    }

    // 延时/按键
    if (g_delay_ms < 0)
        _getch();
    else if (g_delay_ms > 0)
        Sleep(g_delay_ms);
}

/* ===================== 唯一的递归函数（菜单 1/2/3/4/8 共用） ===================== */

void hanoi_recursive(
    int n,
    int src,
    int tmp,
    int dst,
    int totalLayers,
    int mode
)
{
    if (n <= 0) return;

    if (n == 1)
    {
        if (mode == 1)
        {
            // 只计数
            g_step++;
        }
        else if (mode == 2)
        {
            g_step++;
            cout << setw(6) << g_step << " : "
                << tower_char_from_index(src)
                << " -> "
                << tower_char_from_index(dst) << endl;
        }
        else if (mode == 3)
        {
            move_one_disk_common(src, dst, totalLayers, 7);
        }
        else if (mode == 4)
        {
            move_one_disk_common(src, dst, totalLayers, 7);
        }
        else if (mode == 8)
        {
            move_one_disk_common(src, dst, totalLayers, 8);
        }
        return;
    }

    hanoi_recursive(n - 1, src, dst, tmp, totalLayers, mode);
    hanoi_recursive(1, src, tmp, dst, totalLayers, mode);
    hanoi_recursive(n - 1, tmp, src, dst, totalLayers, mode);
}

/* ===================== 根据速度档设置 g_delay_ms ===================== */

static void set_delay_by_speed(int speedLevel)
{
    if (speedLevel == 0) g_delay_ms = -1;   // 按键演示
    else if (speedLevel == 1) g_delay_ms = 600;
    else if (speedLevel == 2) g_delay_ms = 250;
    else g_delay_ms = 80;
}

/* ===================== 菜单 1：只计算最少步数 ===================== */

void menu_item_1()
{
    int n;
    read_params(1, &n, NULL, NULL, NULL);

    g_step = 0;
    // src=0(A), tmp=1(B), dst=2(C)
    hanoi_recursive(n, 0, 1, 2, n, 1);

    cct_cls();
    cout << "最少步数为：" << g_step << " 步" << endl;
}

/* ===================== 菜单 2：输出移动序列 ===================== */

void menu_item_2()
{
    int n;
    char src, dst;
    read_params(2, &n, &src, &dst, NULL);

    int s = tower_index_from_char(src);
    int d = tower_index_from_char(dst);
    int t = 3 - s - d;

    g_step = 0;
    cct_cls();
    cout << "移动序列如下：" << endl;
    hanoi_recursive(n, s, t, d, n, 2);
}

/* ===================== 菜单 3：移动 + 横向数组状态 ===================== */

void menu_item_3()
{
    int n;
    char src, dst;
    read_params(3, &n, &src, &dst, NULL);

    int s = tower_index_from_char(src);
    int d = tower_index_from_char(dst);
    int t = 3 - s - d;

    cct_cls();
    init_towers(n, s);
    draw_horizontal_state(n, 3);

    g_step = 0;
    hanoi_recursive(n, s, t, d, n, 3);

    show_status_line("菜单 3 演示结束。");
}

/* ===================== 菜单 4：字符伪图形递归演示 ===================== */

void menu_item_4()
{
    int n;
    char src, dst;
    int speed;
    read_params(4, &n, &src, &dst, &speed);

    int s = tower_index_from_char(src);
    int d = tower_index_from_char(dst);
    int t = 3 - s - d;

    set_delay_by_speed(speed);

    cct_cls();
    init_towers(n, s);

    draw_three_towers_char(n);
    draw_vertical_state_char(n);
    draw_horizontal_state(n, 4);

    g_step = 0;
    hanoi_recursive(n, s, t, d, n, 4);

    show_status_line("字符伪图形递归演示结束。");
}

/* ===================== 菜单 5：只画三柱 + 初始状态 ===================== */

void menu_item_5()
{
    int n;
    char src, dst;
    read_params(5, &n, &src, &dst, NULL);

    int s = tower_index_from_char(src);

    cct_cls();
    init_towers(n, s);
    draw_three_towers_char(n);
    draw_vertical_state_char(n);
    draw_horizontal_state(n, 3);

    show_status_line("已画出初始状态。");
}

/* ===================== 菜单 6：预留扩展 ===================== */

void menu_item_6()
{
    cct_cls();
    cout << "菜单 6：按 PDF 的附加要求自行扩展。" << endl;
}

/* ===================== 菜单 7：字符伪图形 + 自动移动 ===================== */

void menu_item_7()
{
    int n;
    char src, dst;
    int speed;
    read_params(7, &n, &src, &dst, &speed);

    int s = tower_index_from_char(src);
    int d = tower_index_from_char(dst);
    int t = 3 - s - d;

    set_delay_by_speed(speed);

    cct_cls();
    init_towers(n, s);
    draw_three_towers_char(n);
    draw_vertical_state_char(n);

    g_step = 0;
    hanoi_recursive(n, s, t, d, n, 4); // 复用字符伪图形模式

    show_status_line("菜单 7 演示结束。");
}

/* ===================== 菜单 8：HDC 彩色递归演示 ===================== */

void menu_item_8()
{
    int n;
    char src, dst;
    int speed;
    read_params(8, &n, &src, &dst, &speed);

    int s = tower_index_from_char(src);
    int d = tower_index_from_char(dst);
    int t = 3 - s - d;

    set_delay_by_speed(speed);

    cct_cls();
    init_towers(n, s);
    draw_vertical_state_hdc(n);
    draw_horizontal_state(n, 8);

    g_step = 0;
    Sleep(HDC_Init_Delay);
    hanoi_recursive(n, s, t, d, n, 8);

    show_status_line("HDC 彩色递归演示结束。");
}

/* ===================== 菜单 9：汉诺塔游戏（玩家手动移动） ===================== */

void menu_item_9()
{
    int n;
    char src, dst;
    read_params(9, &n, &src, &dst, NULL);

    int s = tower_index_from_char(src);
    int d = tower_index_from_char(dst);

    cct_cls();
    init_towers(n, s);

    draw_three_towers_char(n);
    draw_vertical_state_char(n);
    draw_horizontal_state(n, 3);

    g_step = 0;
    show_step_info(0, s, s);

    while (1)
    {
        // 判断是否完成
        if (get_top(d) == n - 1)
        {
            show_status_line("恭喜，游戏完成！");
            break;
        }

        cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y);
        cout << "请输入一次移动（形如 A C，Q 退出）：      ";

        char fromCh, toCh;
        cin >> fromCh;
        if (fromCh == 'Q' || fromCh == 'q')
        {
            show_status_line("游戏提前结束。");
            return;
        }
        cin >> toCh;

        int fromPeg = tower_index_from_char(fromCh);
        int toPeg = tower_index_from_char(toCh);

        // 合法性检查
        bool ok = true;
        if (fromPeg < 0 || fromPeg > 2 || toPeg < 0 || toPeg > 2 || fromPeg == toPeg)
        {
            ok = false;
        }
        else
        {
            int fromTop = get_top(fromPeg);
            int toTop = get_top(toPeg);
            if (fromTop < 0) ok = false;
            else
            {
                int movingDisk = get_plate(fromPeg, fromTop);
                if (toTop >= 0)
                {
                    int targetDisk = get_plate(toPeg, toTop);
                    if (movingDisk > targetDisk) ok = false;
                }
            }
        }

        if (!ok)
        {
            show_status_line("非法移动，请重新输入。");
            Sleep(600);
            continue;
        }

        g_delay_ms = 0;  // 游戏中不需要自动延时
        move_one_disk_common(fromPeg, toPeg, n, 9);
    }
}
