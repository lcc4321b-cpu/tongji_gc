#pragma once
/* 班级 学号 姓名 */
#ifndef __HANOI_H__
#define __HANOI_H__

// 这里默认引用“正常版”常量文件。
// 如果老师要求换“胖版/瘦版”，把下面 include 换成对应文件即可：
//   #include "hanoi_const_value_胖版.h"
//   #include "hanoi_const_value_瘦版.h"
#include "hanoi_const_value.h"

// 菜单：输出菜单并返回选择（0~9）
int hanoi_menu();

// 执行：根据菜单项执行功能（1~9），返回 0 表示正常结束，<0 表示异常/中断
int hanoi_run(int menu);

#endif
