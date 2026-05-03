//2550703 卓03 李良玉
#include <iostream>
#include <conio.h>
#include "mine_sweeper.h"

using namespace std;

static void ms_menu_draw_fixed(void)
{
	cct_setcolor();
	cct_cls();

	cct_showstr(0, 0, "-----------------------------------------");
	cct_showstr(0, 1, "1. 选择模式，显示内部数组");
	cct_showstr(0, 2, "2. 输入一个位置，显示打开区域");
	cct_showstr(0, 3, "3. 内部数组基础版");
	cct_showstr(0, 4, "4. 内部数组完整版（标记、运行时间）");
	cct_showstr(0, 5, "5. 画出框架，显示内部数据");
	cct_showstr(0, 6, "6. 检测鼠标位置和合法性，以及左键点击");
	cct_showstr(0, 7, "7. 鼠标点击一次，显示打开区域");
	cct_showstr(0, 8, "8. 允许连续游戏，支持右键标记，判断游戏结束");
	cct_showstr(0, 9, "9. 完整游戏，标明雷数，空格、结束显示时间");
	cct_showstr(0, 10, "0. 退出游戏");
	cct_showstr(0, 11, "-----------------------------------------");
	cct_showstr(0, 12, "");
	cct_showstr(0, 13, "[请选择]");
}

static int ms_menu_select(void)
{
	int ch;
	ms_menu_draw_fixed();

	while (1)
	{

		ch = _getch();

		if (ch == 0 || ch == 0xE0)
		{
			(void)_getch();
			continue;
		}

		if (ch >= '0' && ch <= '9')
		{
			return ch - '0';
		}

		if (ch == 27)
		{
			return 0;
		}
	}
}

void ms_run_main_menu(void)
{
	int opt;

	while (1)
	{
		opt = ms_menu_select();

		switch (opt)
		{
		case 1:
			ms_run_base_task1_show_internal();
			break;
		case 2:
			ms_run_base_task2_open_init_area();
			break;
		case 3:
			ms_run_base_task3_play_basic();
			break;
		case 4:
			ms_run_base_task4_play_full();
			break;
		case 5:
			ms_run_graph_task5_show_internal();
			break;
		case 6:
			ms_run_graph_task6_mouse_position();
			break;
		case 7:
			ms_run_graph_task7_open_init_area();
			break;
		case 8:
			ms_run_graph_task8_game_basic();
			break;
		case 9:
			ms_run_graph_task9_game_full();
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}
