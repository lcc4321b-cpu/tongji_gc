/* 班级 学号 姓名 */

#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

#include "cmd_console_tools.h"
#include "hanoi.h"

/* ----------------------------------------------------------------------------------

     本文件功能：
    1、放被 hanoi_main.cpp 调用的菜单函数，显示各菜单项，读入正确的选项后返回
    2、实现若干通用输入函数（读盘数/读柱子/读速度）

     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、不允许定义静态全局变量
    3、静态局部变量数量不限制，但建议少用

   ----------------------------------------------------------------------------------- */

   /***************************************************************************
     函数名称：show_status_line
     功    能：在状态栏位置输出提示信息，并清空后续位置
   ***************************************************************************/
void show_status_line(const char text[])
{
    cct_gotoxy(Status_Line_X, Status_Line_Y);
    cout << text;
    // 简单清尾
    cout << "                                        ";
}

/***************************************************************************
  函数名称：pause_and_wait
  功    能：显示提示并等待任意键
***************************************************************************/
void pause_and_wait(const char text[])
{
    show_status_line(text);
    _getch();
    show_status_line(" ");
}

/***************************************************************************
  函数名称：read_int_in_range
  功    能：读一个范围内的整数，输入非法会提示重输
***************************************************************************/
int read_int_in_range(int minVal, int maxVal)
{
    int value;
    while (1)
    {
        cin >> value;
        if (cin.good() == 1 && value >= minVal && value <= maxVal)
        {
            cin.clear();
            cin.ignore(1024, '\n');
            return value;
        }

        cin.clear();
        cin.ignore(1024, '\n');
        show_status_line("输入非法，请重新输入：");
    }
}

/***************************************************************************
  函数名称：show_menu
  功    能：显示主菜单并返回选择
***************************************************************************/
int show_menu()
{
    cct_cls();

    cct_gotoxy(0, 0);
    cout << "================= 汉诺塔综合演示 =================" << endl;
    cout << " 1. 只计算并输出最少步数" << endl;
    cout << " 2. 输出移动序列（如 A->C）" << endl;
    cout << " 3. 移动序列 + 横向数组状态" << endl;
    cout << " 4. 字符伪图形递归演示" << endl;
    cout << " 5. 只画三根柱子 + 初始状态" << endl;
    cout << " 6. 其它扩展功能（按 PDF 要求自定）" << endl;
    cout << " 7. 字符伪图形 + 自动移动" << endl;
    cout << " 8. HDC 彩色递归演示" << endl;
    cout << " 9. 汉诺塔游戏（玩家手动移动）" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " 0. 退出" << endl;
    cout << "=================================================" << endl;

    show_status_line("请输入菜单号（0-9）：");
    int choice = read_int_in_range(0, 9);
    return choice;
}

/* -------------------------- 共用输入函数 -------------------------- */

static int read_layer_number()
{
    show_status_line("请输入圆盘层数（1-10）：");
    int n = read_int_in_range(1, MAX_LAYER);
    return n;
}

static char read_peg_char(const char prompt[])
{
    while (1)
    {
        show_status_line(prompt);
        char ch;
        cin >> ch;
        if ('a' <= ch && ch <= 'c') ch = char(ch - 'a' + 'A');

        if (ch == 'A' || ch == 'B' || ch == 'C')
        {
            cin.clear();
            cin.ignore(1024, '\n');
            return ch;
        }
        cin.clear();
        cin.ignore(1024, '\n');
    }
}

/***************************************************************************
  函数名称：read_params
  功    能：菜单 1/2/3/4/6/7/8 共用输入函数
***************************************************************************/
void read_params(
    int menuItem,
    int* n,
    char* src,
    char* dst,
    int* speedLevel
)
{
    // 盘数
    if (n != NULL)
    {
        *n = read_layer_number();
    }

    // 起始柱
    if (src != NULL)
    {
        *src = read_peg_char("请输入起始柱（A-C）：");
    }

    // 目标柱（和起始柱不同）
    if (dst != NULL)
    {
        while (1)
        {
            char d = read_peg_char("请输入目标柱（A-C，且不同于起始柱）：");
            if (src == NULL || d != *src)
            {
                *dst = d;
                break;
            }
        }
    }

    // 速度（0=按键，1=慢，2=中，3=快），只对部分菜单有用
    if (speedLevel != NULL)
    {
        show_status_line("请选择速度：0=按键，1=慢，2=中，3=快：");
        *speedLevel = read_int_in_range(0, 3);
    }
}

/***************************************************************************
  函数名称：run_menu_item
  功    能：根据菜单号分发调用
***************************************************************************/
void run_menu_item(int menuItem)
{
    switch (menuItem)
    {
        case 1: menu_item_1(); break;
        case 2: menu_item_2(); break;
        case 3: menu_item_3(); break;
        case 4: menu_item_4(); break;
        case 5: menu_item_5(); break;
        case 6: menu_item_6(); break;
        case 7: menu_item_7(); break;
        case 8: menu_item_8(); break;
        case 9: menu_item_9(); break;
        default: break;
    }
}
