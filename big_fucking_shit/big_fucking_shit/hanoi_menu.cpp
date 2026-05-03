//2550703 卓03 李良玉
#include <iostream>
#include <limits>

#include "hanoi.h"
#include <conio.h>

using namespace std;

void flush_bad_input()
{
    cin.clear();
    cin.ignore(1024, '\n');
}

int hanoi_menu()
{
    int menu = -1;
	char opt = 0;
    while (1)
    {
        cout << "--------------------------------------------------" << endl;
        cout << "1. 基本解" << endl;
        cout << "2. 基本解(步数记录)" << endl;
        cout << "3. 内部数组显示(横向)" << endl;
        cout << "4. 内部数组显示(纵向+横向)" << endl;
        cout << "5. 图形解-预备-画三个圆柱" << endl;
        cout << "6. 图形解-预备-在起始柱上画n个盘子" << endl;
        cout << "7. 图形解-预备-第一次移动" << endl;
        cout << "8. 图形解-自动移动版本" << endl;
        cout << "9. 图形解-游戏版" << endl;
        cout << "0. 退出" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "[请选择:] ";

        
        while (1)
        {
            opt = _getch();
            if (opt >= '0' && opt <= '9')
            {
                cout << opt << endl;
                break;
			}
        }
        menu = int(opt-'0');
        cout << endl;
        cout << endl;

        return menu;
    }
}
