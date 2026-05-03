//2550703 卓03 李良玉

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "mine_sweeper.h"
#include "cmd_console_tools.h"

using namespace std;
static void ms_base_reveal_all_mines(MSGame& g)
{
    int r;
    int c;

    r = 0;
    while (r < g.rows)
    {
        c = 0;
        while (c < g.cols)
        {
            if (g.board[r][c] == MS_MINE)
            {
                g.state[r][c] = MS_CELL_OPENED;
            }
            c++;
        }
        r++;
    }
}
static void ms_base_draw_headers(const MSGame& g, const int x0, const int y0)
{
    int c;
    char s[3];

    s[1] = 0;
    s[2] = 0;

    cct_showstr(x0, y0, "  ");

    c = 0;
    while (c < g.cols)
    {
        s[0] = ms_col_label_n(c);
        cct_showstr(x0 + 3 + 2 * c, y0 - 1, s);
        cct_showstr(x0 + 3 + 2 * c, y0, "--");
        c++;
    }
    cct_showstr(x0, y0, "--+");
    cct_showstr(x0 + 2, y0 - 1, "|");
}
static void ms_base_draw_row_label(const int r, const int x0, const int y)
{
    char s[2];

    s[0] = ms_row_label(r);
    s[1] = 0;

    cct_showstr(x0, y, s);
    cct_showstr(x0 + 2, y, "|");
}
static void ms_base_show_cell(const int x, const int y, const char ch, const int bg, const int fg)
{
    cct_showch(x, y, ch, bg, fg, 1);
    cct_showch(x + 1, y, ' ', bg, fg, 1);
}

/*
    show_internal = 1 : 直接显示 g.board（雷用*，0-8显示数字）
    show_internal = 0 : 根据 g.state 显示（X / F / 数字 / 空）
    highlight_open = 1 : 对 opened 的格子做亮色反显（Task2 要求）
*/
//基础输出
static void ms_base_render_board(const MSGame& g, const int show_internal, const int highlight_open)
{
    int x0;
    int y0;
    int r;
    int c;

    int x;
    int y;

    char ch;
    int bg;
    int fg;
    int v;

    x0 = 0;
    y0 = 2;

    ms_base_draw_headers(g, x0, y0);

    r = 0;
    while (r < g.rows)
    {
        y = y0 + 1 + r;
        ms_base_draw_row_label(r, x0, y);

        c = 0;
        while (c < g.cols)
        {
            x = x0 + 3 + 2 * c;

            bg = COLOR_BLACK;
            fg = COLOR_WHITE;
            ch = 'X';

            if (show_internal)
            {
                v = g.board[r][c];
                if (v == MS_MINE)
                {
                    ch = '*';
                    fg = COLOR_HRED;
                }
                else
                {
                    ch = (char)('0' + v);
                    fg = ms_graph_number_color(v);
                    bg = COLOR_HYELLOW;
                }
            }
            else
            {
                if (g.state[r][c] == MS_CELL_COVERED)
                {
                    ch = 'X';
                    fg = COLOR_HWHITE;
                }
                else if (g.state[r][c] == MS_CELL_FLAGGED)
                {
                    ch = 'F';
                    fg = COLOR_HRED;
                }
                else
                {
                    v = g.board[r][c];
                    if (v == MS_MINE)
                    {
                        ch = '*';
                        fg = COLOR_HRED;
                    }
                    else
                    {
                        ch = (char)('0' + v);
                        fg = ms_graph_number_color(v);
                        bg = COLOR_HYELLOW;
                    }

                    if (highlight_open)
                    {
                        bg = COLOR_HYELLOW;
                        fg = COLOR_BLACK;
                    }
                }
            }

            ms_base_show_cell(x, y, ch, bg, fg);

            c++;
        }

        r++;
    }
}

static int ms_base_read_position(MSGame& g, int& r, int& c, int rows, int cols)
{
    cct_showstr(0, rows + 4, "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3表示标记A3为雷，#A3表示取消A3标记）:");
    cct_gotoxy(86, rows + 4);
    if (ms_parse_rc(rows, cols, r, c) == 0)
        return 0;

    return 1;
}
/***************************************************************************
  子题目 1：输入初始位置并显示打开的初始区域（亮色反显）
***************************************************************************/
void ms_run_base_task1_show_internal(void)
{
    MSGame g;
    int difficulty;
    int rows;
    int cols;
    int mines;

    cct_setcolor();
    cct_cls();

    cout << "请输入扫雷游戏的等级（数字），初级/中级/高级（1/2/3）";
    while (1)
    {
        difficulty = _getch() - '0';
        if (difficulty >= 1 && difficulty <= 3)
        {
            break;
        }
    }
    cout << difficulty << endl;

    ms_get_difficulty_config(difficulty, rows, cols, mines);
    ms_reset_game(g, rows, cols, mines);
    ms_generate_board_random(g);

    ms_base_render_board(g, 1, 0);
    cct_showstr(0, 0, "内部数组");
    to_be_continued(NULL, 0, rows + 6);
}
/***************************************************************************
  子题目 2：输入初始位置并显示打开的初始区域（亮色反显）
***************************************************************************/
void ms_run_base_task2_open_init_area(void)
{
    MSGame g;
    int difficulty;
    int rows;
    int cols;
    int mines;

    int r;
    int c;

    cct_setcolor();
    cct_cls();

    cout << "请输入扫雷游戏的等级（数字），初级/中级/高级（1/2/3）";
    while (1)
    {
        difficulty = _getch() - '0';
        if (difficulty >= 1 && difficulty <= 3)
        {
            break;
        }
    }
    cout << difficulty << endl;
    ms_get_difficulty_config(difficulty, rows, cols, mines);
    ms_reset_game(g, rows, cols, mines);

    ms_base_render_board(g, 0, 0);

    while (1)
    {
        if (ms_base_read_position(g, r, c, rows, cols) == 0)
            return;


        ms_generate_board_first_click_zero(g, r, c);
        g.start_tick_ms = ms_now_tick_ms();

        ms_open_cell(g, r, c);

        ms_base_render_board(g, 0, 1);

        cct_showstr(0, rows + 4, "Task2：初始区域已打开（已打开格亮色反显）");
        to_be_continued(NULL, 0, rows + 6);
        return;
    }
}
/***************************************************************************
  子题目 3：内部数组基础版（循环输入坐标）
***************************************************************************/
void ms_run_base_task3_play_basic(void)
{
    MSGame g;
    int difficulty;
    int rows;
    int cols;
    int mines;

    int r;
    int c;

    cct_setcolor();
    cct_cls();

    cout << "请输入扫雷游戏的等级（数字），初级/中级/高级（1/2/3）";
    while (1)
    {
        difficulty = _getch() - '0';
        if (difficulty >= 1 && difficulty <= 3)
        {
            break;
        }
    }
    cout << difficulty << endl;
    ms_get_difficulty_config(difficulty, rows, cols, mines);
    ms_reset_game(g, rows, cols, mines);
    cct_cls();
    ms_base_render_board(g, 0, 0);

    while (1)
    {
        if (ms_base_read_position(g, r, c, rows, cols) == 0)
            return;

        if (!g.first_open_done)
        {
            ms_generate_board_first_click_zero(g, r, c);
            g.start_tick_ms = ms_now_tick_ms();
        }

        ms_open_cell(g, r, c);
        ms_check_win(g);

        if (g.game_over)
        {
            if (!g.win)
            {
                ms_base_reveal_all_mines(g);
            }

            ms_base_render_board(g, 0, 0);

            if (g.win)
            {
                cct_showstr(0, rows + 4, "Task3：WIN!");
            }
            else
            {
                cct_showstr(0, rows + 4, "你输了，游戏结束");
            }

            to_be_continued(NULL, 0, rows + 6);
            return;
        }

        ms_base_render_board(g, 0, 0);
    }
}
/***************************************************************************
  子题目 4：内部数组完整版（支持 & @ #）
  &     : 显示已运行时间（秒）
  @A3   : 标记/取消标记（等价右键）
  #A3   : 取消标记（如果未标记则忽略）
***************************************************************************/
void ms_run_base_task4_play_full(void)
{
    MSGame g;
    int difficulty;
    int rows;
    int cols;
    int mines;

    cct_setcolor();
    cct_cls();

    cout << "请输入扫雷游戏的等级（数字），初级/中级/高级（1/2/3）";
    while (1)
    {
        difficulty = _getch() - '0';
        if (difficulty >= 1 && difficulty <= 3)
        {
            break;
        }
    }
    cout << difficulty << endl;
    ms_get_difficulty_config(difficulty, rows, cols, mines);
    ms_reset_game(g, rows, cols, mines);
    ms_base_render_board(g, 0, 0);

    //获取输入
    while (1)
    {
        int r;
        int c;
        long long now_ms;
        long long used_s;

        int action;
        char first_input;

        r = 0;
        c = 0;
        now_ms = 0;
        used_s = 0;
        action = 0;
        while (1)
        {
            cct_showstr(0, rows + 4, "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3表示标记A3为雷，#A3表示取消A3标记）：         ");
            cct_gotoxy(86, rows + 4);
            first_input = _getch();
            if (first_input == '@')
            {
                cct_showstr(84, rows + 4, "@");

                if (ms_base_read_position(g, r, c, rows, cols) == 0)
                    return;
                ms_toggle_flag(g, r, c);
                ms_base_render_board(g, 0, 0);
                action = 1;
                break;
            }
            else if (first_input == '&')
            {
                cct_showstr(84, rows + 4, "&");
                now_ms = ms_now_tick_ms();

                if (g.start_tick_ms != 0)
                {
                    used_s = (now_ms - g.start_tick_ms) / 1000;
                }
                else
                {
                    used_s = 0;
                }

                cct_showstr(0, rows + 5, "Time(s): ");
                cct_showint(9, rows + 5, (int)used_s);
                action = 3;
                break;
            }
            else if (first_input == '#')
            {
                cct_showstr(84, rows + 4, "#");
                if (ms_base_read_position(g, r, c, rows, cols) == 0)
                    return;
                if (g.state[r][c] == MS_CELL_FLAGGED)
                {
                    g.state[r][c] = MS_CELL_COVERED;
                    g.flag_count--;
                }
                ms_base_render_board(g, 0, 0);
                action = 2;
                break;
            }
            if (first_input >= 'A' && first_input <= (char)('A' + rows - 1))
            {
                r = first_input - 'A';

                cct_showch(86, rows + 4, first_input);

                if (ms_parse_col_after_row(cols, c, 87, rows + 4) == 0)
                {
                    return;
                }

                action = 0;
                break;
            }
        }

        if (!g.first_open_done)
        {
            ms_generate_board_first_click_zero(g, r, c);
            g.start_tick_ms = ms_now_tick_ms();
        }

        ms_open_cell(g, r, c);
        ms_check_win(g);

        if (g.game_over)
        {
            long long end_ms;

            end_ms = ms_now_tick_ms();
            g.end_tick_ms = end_ms;

            if (!g.win)
            {
                ms_base_reveal_all_mines(g);
            }

            ms_base_render_board(g, 0, 0);

            if (g.start_tick_ms != 0)
            {
                used_s = (g.end_tick_ms - g.start_tick_ms) / 1000;
            }
            else
            {
                used_s = 0;
            }

            if (g.win)
            {
                cct_showstr(0, rows + 4, "Task4：WIN!");
            }
            else
            {
                cct_showstr(0, rows + 4, "Task4：BOOM!");
            }

            cct_showstr(0, rows + 5, "Final Time(s): ");
            cct_showint(15, rows + 5, (int)used_s);

            to_be_continued(NULL, 0, rows + 7);
            return;
        }

        ms_base_render_board(g, 0, 0);
    }
}