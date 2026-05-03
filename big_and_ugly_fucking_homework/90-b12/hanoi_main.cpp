/* 班级 学号 姓名 */

#include <iostream>
#include <iomanip>
#include <conio.h>     // 允许使用 _getch()
#include <Windows.h>   // 允许使用 RGB（hanoi_const_value 里也会用）
using namespace std;

#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"
#include "hanoi.h"

/* ----------------------------------------------------------------------------------

     本文件功能：
    1、放 main 函数
    2、初始化屏幕（cmd + hdc）
    3、调用菜单函数（hanoi_menu.cpp 中）并返回选项
    4、根据选项调用菜单各项对应的执行函数（hanoi_multi_solutions.cpp 中）

     本文件要求：
    1、不允许定义可读写的全局变量（const及#define不在限制范围内）

   ---------------------------------------------------------------------------------- */

int main()
{
    // === 按老师要求：先确认 cmd 窗口大小 ===
    cout << "请确认当前 cmd 窗口大小为 40 行 * 120 列以上，字体为 新宋体 / 16" << endl;
    cout << "按 C 继续，按 Q 退出..." << endl;

    while (1)
    {
        char ch = _getch();
        if (ch == 'C' || ch == 'c')
            break;
        if (ch == 'Q' || ch == 'q')
            return 0;
    }

    // === 初始化 HDC 图形环境 ===
    // 背景色：HDC_COLOR[0]，前景色先随便用一个盘子的颜色
    hdc_init(HDC_COLOR[0], HDC_COLOR[1], 800, 600);

    // === 主菜单循环 ===
    while (1)
    {
        int menuItem = show_menu();  // 在 hanoi_menu.cpp 中实现

        if (menuItem == 0)
        {
            break;                  // 0 表示退出
        }

        run_menu_item(menuItem);    // 在 hanoi_multi_solutions.cpp 中实现

        // 每个小题运行完之后，给出统一提示
        pause_and_wait("本次演示结束，按任意键返回菜单...");
    }

    // === 释放 HDC 资源 ===
    hdc_release();

    return 0;
}
