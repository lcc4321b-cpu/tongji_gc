#pragma once

#include <Windows.h> // 为 RGB 宏准备

// 允许的最大圆盘层数
const int MAX_LAYER = 10;

// 状态行位置（和老师给的正常.conf 一致）
const int Status_Line_X = 0;
const int Status_Line_Y = 37;

// --- 菜单 4/8/9 提示信息的起始位置（示例值，可按实际微调） ---
const int MenuItem4_Start_X = 0;
const int MenuItem4_Start_Y = 17;

const int MenuItem8_Start_X = 0;
const int MenuItem8_Start_Y = 34;

const int MenuItem9_Start_X = 0;
const int MenuItem9_Start_Y = 34;

// 盘面在屏幕上的整体布局（字符伪图形）
const int TOWER_TOP_Y = 3;                 // 三根柱子顶端所在的行
const int DISK_HEIGHT = 1;                 // 每个圆盘占用的行数
const int TOWER_DISTANCE_X = 20;           // 三根柱子之间的水平间距
const int TOWER_FIRST_X = 20;              // A 柱的 X 坐标

// 计算三个塔柱的 X 坐标
const int Tower_A_X = TOWER_FIRST_X;
const int Tower_B_X = TOWER_FIRST_X + TOWER_DISTANCE_X;
const int Tower_C_X = TOWER_FIRST_X + 2 * TOWER_DISTANCE_X;

// 文字信息（步数提示等）起始行
const int Info_Line_Y = TOWER_TOP_Y + MAX_LAYER + 2;

// --- 彩色 hdc 伪图形的布局（示例值） ---
const int HDC_BG_COLOR = RGB(12, 12, 12);     // 背景色
const int HDC_SCREEN_WIDTH = 8 * 120;
const int HDC_SCREEN_HIGH = 16 * 30;

// 一个圆盘的像素高度（矩形高度）
const int HDC_DISK_PIXEL_HIGH = 14;
// 塔柱底部离窗口底部的像素偏移
const int HDC_BOTTOM_MARGIN = 40;
// 每个“盘大小单位”对应的像素宽度（控制不同大小盘子的宽度差异）
const int HDC_DISK_PIXEL_UNIT = 6;

// 三根塔柱在 hdc 上的 X 坐标（大致居中）
const int HDC_Tower_A_X = 140;
const int HDC_Tower_B_X = 360;
const int HDC_Tower_C_X = 580;

// 圆盘颜色表：下标 0 表示背景色，不使用；1..MAX_LAYER 为圆盘颜色；最后一个是高亮色
const int Disk_Colors[MAX_LAYER + 2] =
{
    RGB(12,12,12),    // 0 背景色
    RGB(0,55,218),    // 1#
    RGB(19,161,14),   // 2#
    RGB(58,150,221),  // 3#
    RGB(197,15,31),   // 4#
    RGB(136,23,152),  // 5#
    RGB(193,156,0),   // 6#
    RGB(204,204,204), // 7#
    RGB(118,118,118), // 8#
    RGB(59,120,255),  // 9#
    RGB(22,198,12),   // 10#
    RGB(249,241,165)  // 额外高亮色
};
