#pragma once

/* 将所有const常量定义的头文件包含进来（老师给的正常/胖/瘦版之一） */
#include "hanoi_const_value.h"

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
    1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multi_solutions.cpp 能相互访问函数的函数声明
    2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量可以写在这里
    3、不允许在本文件定义可读写的全局变量

   ------------------------------------------------------------------------------------------------------ */

#include <iostream>
using namespace std;

/* ===================== 菜单 & 主控相关 ===================== */

// 显示主菜单，返回用户选择的菜单号（0 表示退出）
int show_menu();

// 在状态栏输出一行提示（自动清尾部）
void show_status_line(const char text[]);

// 输出提示并等待任意键
void pause_and_wait(const char text[]);

// 根据菜单号调用对应的小题（在 hanoi_multi_solutions.cpp 中实现）
void run_menu_item(int menuItem);


/* ===================== 通用输入函数 ===================== */

// 读一个范围 [minVal, maxVal] 内的整数
int read_int_in_range(int minVal, int maxVal);

/*
   共用输入函数：菜单 1/2/3/4/6/7/8 共用
   menuItem：当前菜单号（只做逻辑区分）
   哪个参数需要就传指针，不需要就传 NULL
*/
void read_params(
    int menuItem,
    int* n,
    char* src,
    char* dst,
    int* speedLevel
);


/* ===================== 盘面数据相关 ===================== */

// 初始化盘面：n 个盘全部堆在 srcIndex（0=A,1=B,2=C）上
void init_towers(int n, int srcIndex);

// 塔编号字符 <-> 下标
int  tower_index_from_char(char ch);
char tower_char_from_index(int idx);

// 当前塔顶的下标（-1 表示空）
int  get_top(int pegIndex);
void set_top(int pegIndex, int newTop);

// 获取 / 设置某柱某层的盘号（0 表示无盘）
int  get_plate(int pegIndex, int diskIndex);
void set_plate(int pegIndex, int diskIndex, int value);


/* ===================== 字符伪图形绘制相关 ===================== */

// 画三根柱子（菜单 5/6/7/8/9 共用）
void draw_three_towers_char(int n);

// 根据当前全局数组，在字符界面纵向画出盘子（菜单 4/7/9）
void draw_vertical_state_char(int n);

// 横向输出 A/B/C 三行数组状态（菜单 3/4/8）
void draw_horizontal_state(int n, int menuItem);


/* ===================== HDC 彩色伪图形相关 ===================== */

// 根据当前全局数组，在 HDC 界面画出盘子（菜单 8）
void draw_vertical_state_hdc(int n);


/* ===================== 盘子移动相关（菜单 7/8/9 共用） ===================== */
/*
   mode：
     7：字符伪图形自动演示
     8：HDC 彩色演示
     9：游戏模式
*/
void move_one_disk_common(
    int fromPeg,
    int toPeg,
    int totalLayers,
    int mode
);


/* ===================== 唯一的递归函数（菜单 1/2/3/4/8 共用） ===================== */

void hanoi_recursive(
    int n,
    int src,
    int tmp,
    int dst,
    int totalLayers,
    int mode
);


/* ===================== 各菜单项入口函数（在 multi_solutions 中实现） ===================== */

void menu_item_1();
void menu_item_2();
void menu_item_3();
void menu_item_4();
void menu_item_5();
void menu_item_6();
void menu_item_7();
void menu_item_8();
void menu_item_9();
