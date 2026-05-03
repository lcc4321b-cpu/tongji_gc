/* 班级 学号 姓名 */

#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "hanoi.h"
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"

using namespace std;

void wait_any_key()
{
    cout << "\n按任意键返回菜单..." << endl;
    (void)_getch();
}

int main()
{
    cout << "请确认当前cmd窗口的大小为40行*120列以上，字体为新宋体/16，按C继续，Q退出" << endl;

    while (1)
    {
        char ch = _getch();
        if (ch == 'C' || ch == 'c')
            break;
        if (ch == 'Q' || ch == 'q')
            return 0;
    }

    hdc_init(HDC_COLOR[0], RGB(0, 0, 0), 8 * 120, 16 * 40);//?前景色是否有定义？

    while (1)
    {
        cct_cls();
        int menu = hanoi_menu();
        if (menu == 0)
            break;

        if (menu >= 5)
        {
            cct_cls();
            hdc_cls();
        }

        int rc = hanoi_run(menu);
        (void)rc;

        wait_any_key();
    }

    hdc_release();
    return 0;
}
