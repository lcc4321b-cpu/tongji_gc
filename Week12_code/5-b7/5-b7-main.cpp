//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "5-b7.h"
using namespace std;
#define MAX_DISKS 10

// g_delay_ms = -1 表示“按回车单步演示”模式
static int  g_delay_ms = 0;   // 每步移动后的延时（毫秒）
static bool g_show_internal = false;

const int TOWER_TOP_Y = 2;                    // 塔的显示起始行（顶部）
const int LABEL_Y = TOWER_TOP_Y + MAX_DISKS;
const int INFO_Y = LABEL_Y + 2;
const int INTERNAL_Y = INFO_Y - 1;

// 三个全局 int 变量，表示 A/B/C 三根柱子的栈顶下标（-1 表示空）
int g_topA = -1;
int g_topB = -1;
int g_topC = -1;

// 三个全局一维数组，表示三根柱子上的圆盘编号（0 表示无盘），0 为底层
int g_plateA[MAX_DISKS] = { 0 };
int g_plateB[MAX_DISKS] = { 0 };
int g_plateC[MAX_DISKS] = { 0 };

// 通过柱子编号 peg(0:A 1:B 2:C) 取得对应的栈顶值
int get_top(int peg)
{
    if (peg == 0)
    {
        return g_topA;
    }
    if (peg == 1)
    {
        return g_topB;
    }
    return g_topC;
}

// 设置指定柱子的栈顶值
void set_top(int peg, int value)
{
    if (peg == 0) g_topA = value;
    else if (peg == 1) g_topB = value;
    else g_topC = value;
}

// 取得指定柱子指定层的圆盘编号
int get_plate(int peg, int index)
{
    if (peg == 0) return g_plateA[index];
    if (peg == 1) return g_plateB[index];
    return g_plateC[index];
}

// 设置指定柱子指定层的圆盘编号
void set_plate(int peg, int index, int value)
{
    if (peg == 0) g_plateA[index] = value;
    else if (peg == 1) g_plateB[index] = value;
    else g_plateC[index] = value;
}

// 读取移动速度 0-5 并返回
int read_speed()
{
    int speed;
    while (1)
    {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> speed;
        if (cin.good() == 1 && speed >= 0 && speed <= 5)
        {
            cin.clear();
            cin.ignore(1024, '\n');
            return speed;
        }
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "输入错误，请输入 0-5 之间的整数。" << endl;
    }
}

// 是否显示内部数组（1/0）
bool read_show_internal()
{
    int flag;
    while (1)
    {
        cout << "请输入是否显示内部数组值(0-不显示 1-显示)" << endl;
        cin >> flag;
        if (cin.good() == 1 && (flag == 0 || flag == 1))
        {
            cin.clear();
            cin.ignore(1024, '\n');
            return flag == 1;
        }
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "输入错误，请输入 0 或 1。" << endl;
    }
}

// 整体绘制三个塔（只在开始时调用一次）
void draw_towers_all(int maxDisks, int tower[], int plate[][MAX_DISKS], const int xPos[])
{
    for (int row = 0; row < maxDisks; row++)
    {
        int diskIndex = maxDisks - 1 - row;   // 0 为底层
        int y = TOWER_TOP_Y + row;
        for (int p = 0; p < 3; p++)
        {
            int value = 0;
            int top = get_top(p);
            if (diskIndex >= 0 && diskIndex <= top)
            {
                value = get_plate(p, diskIndex);
            }
            cct_gotoxy(xPos[p], y);
            if (value == 0)
            {
                cout << "  ";
            }
            else
            {
                cout << setw(2) << value;     // 只用数字显示盘号/层号
            }
        }
    }
}

// 更新单个塔上某一层的显示（只改动一个位置）
void update_tower_cell(int peg, int index, int maxDisks, int value,  const int xPos[])
{
    if (index < 0 || index >= maxDisks)
    {
        return;
    }
    int row = maxDisks - 1 - index;
    int y = TOWER_TOP_Y + row;
    int x = xPos[peg];
    cct_gotoxy(x, y);
    if (value == 0)
    {
        cout << "  ";
    }
    else
    {
        cout << setw(2) << value;
    }
}

// 在塔的下方打印 A/B/C 标签
void draw_labels(const int xPos[])
{
    cct_gotoxy(xPos[0] - 2, LABEL_Y);
    cout << "=====================================" << endl;
    cct_gotoxy(xPos[0] + 1, LABEL_Y + 1);
    cout << "A";
    cct_gotoxy(xPos[1] + 1, LABEL_Y + 1);
    cout << "B";
    cct_gotoxy(xPos[2] + 1, LABEL_Y + 1);
    cout << "C";
}

// 绘制内部数组的完整内容
// 内部数组形式：三根柱子的全局一维数组（从底到顶）
void draw_internal_all(int maxDisks, int tower[], int plate[][MAX_DISKS])
{

    cct_gotoxy(0, INTERNAL_Y);

    cct_gotoxy(0, INTERNAL_Y + 1);

    // 三个一维数组 A/B/C，从底到顶
    for (int p = 0; p < 3; p++)
    {
        int y = INTERNAL_Y + 2 + p;
        cct_gotoxy(0, y);
        cout << char('A' + p) << ":";
        for (int i = 0; i < maxDisks; i++)
        {
            int x = 4 + i * 3;
            cct_gotoxy(x, y);
            int value = get_plate(p, i);
            if (value == 0)
            {
                cout << "  ";
            }
            else
            {
                cout << setw(2) << value;
            }
        }
    }
}

// 更新内部数组中单个元素的显示
void update_internal_cell(int peg, int index, int maxDisks, int plate[][MAX_DISKS])
{
    if (index < 0 || index >= maxDisks)
    {
        return;
    }
    int y = INTERNAL_Y + 2 + peg;
    int x = 4 + index * 3;
    cct_gotoxy(x, y);
    int value = get_plate(peg, index);
    if (value == 0)
    {
        cout << "  ";
    }
    else
    {
        cout << setw(2) << value;
    }
}

// 显示当前步的信息
void show_step_info(int stepNumber, int disk, int fromPeg, int toPeg)
{
    cct_gotoxy(0, INFO_Y);
    cout << "第" << setw(4) << stepNumber << "步";
    if (disk > 0)
    {
        cout << "(" << disk << "#";
    }
    cout << ": " << char('A' + fromPeg) << "-->"
        << char('A' + toPeg) << ")          ";
}

// 移动一块盘子，并只更新改变的部分
void move_one_disk(int fromPeg, int toPeg, int maxDisks, int tower[], int plate[][MAX_DISKS], int step[], const int xPos[])
{
    int fromTop = get_top(fromPeg);
    if (fromTop < 0)
    {
        return;
    }
    int disk = get_plate(fromPeg, fromTop);

    // 更新内部数组数据
    set_plate(fromPeg, fromTop, 0);
    set_top(fromPeg, fromTop - 1);

    int toTop = get_top(toPeg) + 1;
    set_top(toPeg, toTop);
    set_plate(toPeg, toTop, disk);

    // 更新显示
    update_tower_cell(fromPeg, fromTop, maxDisks, 0, xPos);
    update_tower_cell(toPeg, toTop, maxDisks, disk, xPos);

    if (g_show_internal)
    {
        update_internal_cell(fromPeg, fromTop, maxDisks, plate);
        update_internal_cell(toPeg, toTop, maxDisks, plate);
    }

    // 更新步数与提示信息
    step[0]++;
    show_step_info(step[0], disk, fromPeg, toPeg);

    // 延时 / 单步控制
    if (g_delay_ms < 0)
    {
        cin.get();    // 等待一次回车
    }
    else if (g_delay_ms > 0)
    {
        Sleep(g_delay_ms);
    }
}

// 递归实现汉诺塔
void hanoi(int n, int fromPeg, int viaPeg, int toPeg, int maxDisks, int tower[], int plate[][MAX_DISKS], int step[], const int xPos[])
{
    if (n <= 0)
    {
        return;
    }
    if (n == 1)
    {
        move_one_disk(fromPeg, toPeg, maxDisks, tower, plate, step, xPos);
    }
    else
    {
        hanoi(n - 1, fromPeg, toPeg, viaPeg, maxDisks, tower, plate, step, xPos);
        move_one_disk(fromPeg, toPeg, maxDisks, tower, plate, step, xPos);
        hanoi(n - 1, viaPeg, fromPeg, toPeg, maxDisks, tower, plate, step, xPos);
    }
}

int main()
{
    int n = 0;
    int floor;                    // 实际盘子层数
    char src = 0, dst = 0;        // 起始柱和目标柱（A、B、C）
    bool finish = 1;

    // 输入汉诺塔层数（1-10），格式同 5-b6
    while (finish)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> floor;
        if (cin.good() == 1 && (floor >= 1 && floor <= 10))
        {
            finish = 0;
            n = floor;
        }
        cin.clear();
        cin.ignore(1024, '\n');
    }

    // 读取起始柱（A-C，大小写均可）
    while (1)
    {
        cout << "请输入起始柱 (A-C)" << endl;
        char ch;
        cin >> ch;
        if (cin.good() == 1)
        {
            if ('a' <= ch && ch <= 'c')
            {
                ch = char(ch - 'a' + 'A');
            }
            if (ch == 'A' || ch == 'B' || ch == 'C')
            {
                src = ch;
                cin.clear();
                cin.ignore(1024, '\n');
                break;
            }
        }
        // 清空到行尾
        cin.clear();
        cin.ignore(1024, '\n');
    }

    // 读取目标柱（A-C，且不得与起始柱相同）
    while (1)
    {
        cout << "请输入目标柱 (A-C)" << endl;
        char ch2;
        cin >> ch2;
        if (cin.good() == 1)
        {
            if ('a' <= ch2 && ch2 <= 'c')
            {
                ch2 = char(ch2 - 'a' + 'A');
            }
            if (ch2 == 'A' || ch2 == 'B' || ch2 == 'C')
            {
                if (ch2 != src)
                {
                    dst = ch2;
                    cin.clear();
                    cin.ignore(1024, '\n');
                    break;
                }
                cout << "目标柱(" << src << ")不能与起始柱(" << src << ")相同" << endl;
            }
        }
        // 清空到行尾
        cin.clear();
        cin.ignore(1024, '\n');
    }

    // 读取移动速度并转换为延时 / 单步模式
    int speed = read_speed();
    switch (speed)
    {
        case 0: g_delay_ms = -1;    
            break; // 单步演示
        case 1: g_delay_ms = 1000;  
            break;
        case 2: g_delay_ms = 500;   
            break;
        case 3: g_delay_ms = 200;   
            break;
        case 4: g_delay_ms = 50;    
            break;
        case 5: g_delay_ms = 0;     
            break;
        default:g_delay_ms = 200;   
            break;
    }

    // 是否显示内部数组
    g_show_internal = read_show_internal();

    // 计算中间柱（自动求出支撑柱）
    char tmp = char('A' + 'B' + 'C' - src - dst);

    // 将 A/B/C 转换为 0/1/2 下标
    int srcIndex = src - 'A';
    int dstIndex = dst - 'A';
    int tmpIndex = tmp - 'A';

    int tower[3];
    int plate[3][MAX_DISKS];
    int step[1];

    // 初始化模拟“指针”的数组（这里只是占位，不再保存真实盘子数据）
    for (int p = 0; p < 3; p++)
    {
        tower[p] = p; // 0,1,2 分别代表 A,B,C
        for (int i = 0; i < MAX_DISKS; i++)
        {
            plate[p][i] = 0; // 不再使用真实数据
        }
    }

    // 初始化全局三根柱：栈顶为 -1，数组元素为 0
    for (int p = 0; p < 3; p++)
    {
        set_top(p, -1);
        for (int i = 0; i < MAX_DISKS; i++)
        {
            set_plate(p, i, 0);
        }
    }

    step[0] = 0;

    // 初始化起始柱：从底到顶依次为 n, n-1, ..., 1
    set_top(srcIndex, n - 1);
    for (int i = 0; i < n; i++)
    {
        set_plate(srcIndex, i, n - i);
    }

    // 每一列的 X 坐标（尽量分散一点）
    int xPos[3];
    xPos[0] = 10;
    xPos[1] = 25;
    xPos[2] = 40;

    // 清屏并绘制初始界面
    cct_cls();
    cct_gotoxy(0, 0);
    cout << "从 " << src << "移动到 " << dst << "，共 " << n << " 层，延时设置为 " << speed << "，";
    if (!g_show_internal)
    {
        cout << "不";
    }
    cout << "显示内部数组值" << endl;
    draw_towers_all(MAX_DISKS, tower, plate, xPos);
    draw_labels(xPos);

    if (g_show_internal)
    {
        draw_internal_all(MAX_DISKS, tower, plate);
    }

    // 初始提示信息（步数为 0，仅提示当前位置）
    show_step_info(0, 0, srcIndex, srcIndex);

    // 递归求解并逐步显示移动过程
    hanoi(n, srcIndex, tmpIndex, dstIndex,
        MAX_DISKS, tower, plate, step, xPos);

    cct_gotoxy(0, INFO_Y + 4);

    return 0;
}
