//2550703 卓03 李良玉

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "mine_sweeper.h"

using namespace std;

static void ms_graph_get_frame_charset(const char* out[11])
{
    out[0] = "╔";
    out[1] = "╚";
    out[2] = "╗";
    out[3] = "╝";
    out[4] = "═";
    out[5] = "║";
    out[6] = "╦";
    out[7] = "╩";
    out[8] = "╠";
    out[9] = "╣";
    out[10] = "╬";
}//定义框线
int ms_graph_number_color(const int num)
{
    if (num == 1)
    {
        return COLOR_HBLUE;
    }

    if (num == 2)
    {
        return COLOR_HGREEN;
    }

    if (num == 3)
    {
        return COLOR_HRED;
    }

    if (num == 4)
    {
        return COLOR_BLUE;
    }

    if (num == 5)
    {
        return COLOR_RED;
    }

    if (num == 6)
    {
        return COLOR_HCYAN;
    }

    if (num == 7)
    {
        return COLOR_BLACK;
    }

    if (num == 8)
    {
        return COLOR_HBLACK;
    }

    return COLOR_BLACK;
}
static char ms_graph_col_label(const int c)
{
    return (char)('a' + c);
}
static void ms_graph_setup_console_for_board(const int rows, const int cols)
{
    int need_cols;
    int need_lines;

    need_cols = 6 * cols + 10;
    need_lines = 3 * rows + 12;

    if (need_cols < 80)
    {
        need_cols = 80;
    }

    if (need_lines < 30)
    {
        need_lines = 30;
    }

    cct_setconsoleborder(need_cols, need_lines);
    cct_setfontsize("新宋体", 16, 0);
    cct_setcursor(CCT_CURSOR_INVISIBLE);
    cct_setcolor();
    cct_cls();

    cct_enable_mouse();
}
static int ms_graph_append(char* buf, const int buf_size, int pos, const char* s)
{
    int i;

    if (buf == 0)
    {
        return pos;
    }

    if (s == 0)
    {
        return pos;
    }

    i = 0;

    while (s[i] != 0)
    {
        if (pos + 1 >= buf_size)
        {
            break;
        }

        buf[pos] = s[i];
        pos++;
        i++;
    }

    if (pos < buf_size)
    {
        buf[pos] = 0;
    }

    return pos;
}
static void ms_graph_build_border_line(char* out, const int out_size, const char* L, const char* M, const char* J, const char* R, const int cols)
{
    int pos;
    int c;

    pos = 0;
    out[0] = 0;

    pos = ms_graph_append(out, out_size, pos, L);

    c = 0;

    while (c < cols)
    {
        pos = ms_graph_append(out, out_size, pos, M);
        pos = ms_graph_append(out, out_size, pos, M);
        if (c != cols - 1)
        {
            pos = ms_graph_append(out, out_size, pos, J);
        }
        else
        {
            pos = ms_graph_append(out, out_size, pos, R);
        }

        c++;
    }

    out[out_size - 1] = 0;
}
static void ms_graph_build_content_line(char* out, const int out_size, const char* V, const int cols)
{
    int pos;
    int c;

    pos = 0;
    out[0] = 0;


    pos = ms_graph_append(out, out_size, pos, V);
    c = 0;

    while (c < cols)
    {
        pos = ms_graph_append(out, out_size, pos, "    ");
        pos = ms_graph_append(out, out_size, pos, V);
        c++;
    }

    out[out_size - 1] = 0;
}
char ms_col_label_n(const int c)
{
    if (c >= 0 && c <= 8)
    {
        return (char)('1' + c);
    }
    else
    {
        return (char)('a' + c - 9);
    }
}
/*******************************
 * 显示所有地雷（游戏结束时用）
 *******************************/
static void ms_graph_reveal_all_mines(MSGame& g)
{
    for (int r = 0; r < g.rows; ++r)
    {
        for (int c = 0; c < g.cols; ++c)
        {
            if (g.board[r][c] == MS_MINE)
            {
                g.state[r][c] = MS_CELL_OPENED;
            }
        }
    }
}
//画框-ad
static void ms_graph_draw_frame(const MSLayout& lay)
{
    const char* cs[11];
    char top[1024];
    char mid[1024];
    char rowline[1024];

    int r;
    int x;
    int y;
    char label[3];

    ms_graph_get_frame_charset(cs);

    ms_graph_build_border_line(top, 1024, cs[0], cs[4], cs[6], cs[2], lay.cols);
    ms_graph_build_border_line(mid, 1024, cs[8], cs[4], cs[10], cs[9], lay.cols);


    cct_showstr(lay.x0, lay.y0, top,15,0);

    r = 0;

    while (r < lay.rows)
    {
        y = lay.y0 + 1 + 3 * r;

        ms_graph_build_content_line(rowline, 1024, cs[5], lay.cols);
		cct_showstr(lay.x0, y, rowline, 15,0);
        cct_showstr(lay.x0, y+1, rowline,15,0);


        label[0] = ms_row_label(r);
        label[1] = 0;
        label[2] = 0;
        cct_showstr(lay.x0 - 3, y, label);

        if (r != lay.rows - 1)
        {
            cct_showstr(lay.x0, y + 2, mid,15,0);
        }
        else
        {
            ms_graph_build_border_line(mid, 1024, cs[1], cs[4], cs[7], cs[3], lay.cols);
            cct_showstr(lay.x0, y + 2, mid, 15, 0);
        }

        r++;
    }

    x = lay.x0 + 3;
    r = 0;

    while (r < lay.cols)
    {
		label[0] = ms_col_label(r, 1);
		label[1] = ms_col_label(r, 2);
        cct_showstr(x, lay.y0 - 1, label);
        x = x + 6;
        r++;
    }
}
//清理行
static void ms_graph_status_clear_line(const int y)
{
    cct_showstr(0, y, "                            ");
}
static void ms_graph_status_show(const int y, const char* msg)
{
    ms_graph_status_clear_line(y);
    cct_showstr(0, y, msg);
}
static void ms_graph_render_cell(const MSLayout& lay, const MSGame& g, const int r, const int c, const int highlight)
{
    int x;
    int y;

    int bg;
    int fg;

    char s[5];
    int v;

    if (!ms_cell_to_screen_xy(lay, r, c, x, y))
    {
        return;
    }

    s[0] = ' ';
    s[1] = ' ';
    s[2] = ' ';
    s[3] = ' ';
    s[4] = 0 ;

    bg = COLOR_BLACK;
    fg = COLOR_WHITE;

    if (highlight)
    {
        bg = COLOR_HYELLOW;
        fg = COLOR_BLACK;
    }
    else
    {
        if (g.state[r][c] == MS_CELL_COVERED)
        {
            bg = COLOR_YELLOW;
            fg = COLOR_HWHITE;
        }
        else
        {
            if (g.state[r][c] == MS_CELL_FLAGGED)
            {
                bg = COLOR_HRED;
                fg = COLOR_WHITE;
                s[1] = '#';
            }
            else
            {
                bg = COLOR_WHITE;
                v = g.board[r][c];

                if (v == MS_MINE)
                {
                    fg = COLOR_HRED;
                    s[1] = '*';
                }
                else
                {
                    if (v == 0)
                    {
                        fg = COLOR_BLACK;
                        s[1] = ' ';
                    }
                    else
                    {
                        fg = ms_graph_number_color(v);
                        s[1] = (char)('0' + v);
                    }
                }
            }
        }
    }

    cct_showstr(x, y, s, bg, fg, 1);
    cct_showstr(x, y + 1, "    ", bg, fg, 1);
}
void ms_graph_render_all(const MSLayout& lay, const MSGame& g)
{
    int r;
    int c;

    r = 0;

    while (r < lay.rows)
    {
        c = 0;

        while (c < lay.cols)
        {
            ms_graph_render_cell(lay, g, r, c, 0);
            c++;
        }

        r++;
    }
}
static void ms_graph_show_task_title(const int y, const char* title)
{
    ms_graph_status_clear_line(y);
    cct_showstr(0, y, title);
}
static void ms_graph_update_full_status(const int y, const MSGame& g)
{
    long long now_ms;
    long long used_s;
    int remain;

    now_ms = ms_now_tick_ms();

    if (g.start_tick_ms != 0)
    {
        used_s = (now_ms - g.start_tick_ms) / 1000;
    }
    else
    {
        used_s = 0;
    }
    remain = g.mines - g.flag_count;
    ms_graph_status_clear_line(y);
    cct_showstr(0, y, "RemainMines:");
    cct_showint(12, y, remain);
    cct_showstr(18, y, "Time(s):");
    cct_showint(26, y, (int)used_s);
    cct_showstr(34, y, "(SPACE refresh)");
}


/*******************************
 * 扫雷任务 5（显示内部数据）
 *******************************/
void ms_run_graph_task5_show_internal(void)
{
    MSGame g;
    MSLayout lay;

    int difficulty;
    int rows;
    int cols;
    int mines;

    int r;
    int c;

    int x;
    int y;

    int y_hint;

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

    ms_graph_setup_console_for_board(rows, cols);

    lay.x0 = 6;
    lay.y0 = 4;
    lay.rows = rows;
    lay.cols = cols;

    ms_graph_draw_frame(lay);

    r = 0;
    while (r < rows)
    {
        c = 0;
        while (c < cols)
        {
            if (ms_cell_to_screen_xy(lay, r, c, x, y))
            {
                int v;
                int bg;
                int fg;
                char pp[5];

                v = g.board[r][c];

                bg = COLOR_WHITE;   // 浅灰块
                fg = COLOR_BLACK;

                pp[0] = ' ';
                pp[1] = ' ';
                pp[2] = ' ';
                pp[3] = ' ';
                pp[4] = 0;

                if (v == MS_MINE)
                {
                    pp[1] = '*';
                    fg = COLOR_BLACK;
                }
                else if (v != 0)
                {
                    pp[1] = (char)('0' + v);
                    fg = ms_graph_number_color(v);
                }

                // 两行填充成“块状格子”
                cct_showstr(x, y, pp, bg, fg);
                cct_showstr(x, y + 1, "    ", bg, fg);
            }

            c++;
        }
        r++;
    }

    y_hint = lay.y0 + 3 * rows + 5;
    to_be_continued(NULL, 0, y_hint);
}

/*******************************
 * 扫雷任务 6（鼠标位置显示）
 *******************************/
void ms_run_graph_task6_mouse_position(void)
{
    MSGame g;
    MSLayout lay;

    int difficulty;
    int rows;
    int cols;
    int mines;

    int r;

    int hover_r;
    int hover_c;

    int info_y;

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

    ms_graph_setup_console_for_board(rows, cols);


    lay.x0 = 6;
    lay.y0 = 4;
    lay.rows = rows;
    lay.cols = cols;

    ms_graph_draw_frame(lay);
	r = 0;
    while (r < rows)
    {
        int c;
        c = 0;
        int x, y;
        while (c < cols)
        {
            if (ms_cell_to_screen_xy(lay, r, c, x, y))
            {
                int v;
                int bg;
                int fg;
                char pp[5];

                v = g.board[r][c];

                bg = COLOR_WHITE;   // 浅灰块
                fg = COLOR_BLACK;

                pp[0] = ' ';
                pp[1] = ' ';
                pp[2] = ' ';
                pp[3] = ' ';
                pp[4] = 0;

                if (v == MS_MINE)
                {
                    pp[1] = '*';
                    fg = COLOR_BLACK;
                }
                else if (v != 0)
                {
                    pp[1] = (char)('0' + v);
                    fg = ms_graph_number_color(v);
                }

                // 两行填充成“块状格子”
                cct_showstr(x, y, pp, bg, fg);
                cct_showstr(x, y + 1, "    ", bg, fg);
            }

            c++;
        }
        r++;
    }

    hover_r = -1;
    hover_c = -1;

    info_y = lay.y0 + 3 * rows + 4;

    while (1)
    {
        int mx;
        int my;
        int ma;
        int k1;
        int k2;
        int evt;

        int r;
        int c;
        int ok;

        evt = cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

        if (evt == CCT_KEYBOARD_EVENT)
        {
            if (k1 == 27)
            {
                break;
            }
        }
        else
        {
            ok = ms_mouse_to_cell(lay, mx, my, r, c);

            if (ok)
            {
                if (hover_r != r || hover_c != c)
                {
                    if (hover_r >= 0)
                    {
                        hover_r = r;
                        hover_c = c;
                    }
                }
            }
            else
            {
                if (hover_r >= 0)
                {
                    hover_r = -1;
                    hover_c = -1;
                }
            }
            ms_graph_status_clear_line(info_y);

            {
                char msg[64];
                int pos;

                pos = 0;
				pos = ms_graph_append(msg, 64, pos, "[当前位置]");
                cct_showstr(0, 0, "esc退出");

                if (!ok)
                {
                    pos = ms_graph_append(msg, 64, pos, "位置非法");
                }
                else
                {
                    char rowch;
                    char rowbuf[2];
                    int colnum;
                    char colbuf[3];
                    int rp;

                    rowch = ms_row_label(r);
                    rowbuf[0] = rowch;
                    rowbuf[1] = 0;

                    pos = ms_graph_append(msg, 64, pos, rowbuf);
                    pos = ms_graph_append(msg, 64, pos, "行");

                    colnum = c + 1;
                    rp = 0;
                    colbuf[2] = 0;
                    if (colnum <= 26)
                    {
                        colbuf[0] = ms_graph_col_label(c);
                        colbuf[1] = ' ';                  
                    }
                    else
                    {
                        colbuf[0] = '2';
                        colbuf[1] = (char)('6'+colnum-27);

                    }

                    pos = ms_graph_append(msg, 64, pos, colbuf);
                    pos = ms_graph_append(msg, 64, pos, "列    ");
                }

                cct_showstr(0, info_y-1, msg);
            }
        }
    }

    cct_disable_mouse();
}

/*******************************
 * 扫雷任务 7（首点点击后打开）
 *******************************/
void ms_run_graph_task7_open_init_area(void)
{
    MSGame g;
    MSLayout lay;

    int rows;
    int cols;
    int mines;

    int difficulty;

    int hover_r;
    int hover_c;

    int info_y;

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

    ms_graph_setup_console_for_board(rows, cols);

    lay.x0 = 6;
    lay.y0 = 4;
    lay.rows = rows;
    lay.cols = cols;
    int x, y, r, c;

    r = 0;
    ms_graph_draw_frame(lay);
    while (r < rows)
    {
        c = 0;
        while (c < cols)
        {
            if (ms_cell_to_screen_xy(lay, r, c, x, y))
            {
                int bg;
                int fg;
                char pp[5];


                bg = COLOR_YELLOW;   // 浅灰块
                fg = COLOR_BLACK;

                pp[0] = ' ';
                pp[1] = ' ';
                pp[2] = ' ';
                pp[3] = ' ';
                pp[4] = 0;

                // 两行填充成“块状格子”
                cct_showstr(x, y, pp, bg, fg);
                cct_showstr(x, y + 1, "    ", bg, fg);
            }

            c++;
        }
        r++;
    }

    hover_r = -1;
    hover_c = -1;

    info_y = lay.y0 + 3 * rows + 4;
    ms_graph_status_clear_line(info_y + 1);
    while (1)
    {
        int mx;
        int my;
        int ma;
        int k1;
        int k2;
        int evt;

        int r;
        int c;
        int ok;

        evt = cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

        if (evt == CCT_KEYBOARD_EVENT)
        {
            if (k1 == 27)
            {
                break;
            }
        }
        else
        {
            ok = ms_mouse_to_cell(lay, mx, my, r, c);

            if (ok)
            {
                if (hover_r != r || hover_c != c)
                {
                    if (hover_r >= 0)
                    {
                        hover_r = r;
                        hover_c = c;
                    }
                }
            }
            else
            {
                if (hover_r >= 0)
                {
                    hover_r = -1;
                    hover_c = -1;
                }
            }
            ms_graph_status_clear_line(info_y);

            {
                char msg[64];
                int pos;

                pos = 0;
                pos = ms_graph_append(msg, 64, pos, "[当前位置]");
                cct_showstr(0, 0, "esc退出");

                if (!ok)
                {
                    pos = ms_graph_append(msg, 64, pos, "位置非法");
                }
                else
                {
                    char rowbuf[3];
                    int colnum;
                    char colbuf[16];
                    int colpos;
                    int rp;

                    rowbuf[0] = ms_row_label(r);
                    rowbuf[1]=0;

                    pos = ms_graph_append(msg, 64, pos, rowbuf);
                    pos = ms_graph_append(msg, 64, pos, "行");

                    colnum = c + 1;
                    colpos = 0;
                    rp = 0;

                    colbuf[2] = 0;
                    if (colnum <= 26)
                    {
                        colbuf[0] = ms_graph_col_label(c);
                        colbuf[1] = ' ';
                    }
                    else
                    {
                        colbuf[0] = '2';
                        colbuf[1] = (char)('6' + colnum - 27);

                    }

                    pos = ms_graph_append(msg, 64, pos, colbuf);
                    pos = ms_graph_append(msg, 64, pos, "列   ");

                    if (ma == MOUSE_LEFT_BUTTON_CLICK)
                    {
                        ms_generate_board_first_click_zero(g, r, c);
                        g.start_tick_ms = ms_now_tick_ms();

                        ms_open_cell(g, r, c);
                        ms_graph_render_all(lay, g);
      
                        ms_graph_show_task_title(info_y + 2, "Opened. Press ENTER to return.");
                        to_be_continued(NULL, 0, info_y + 3);
                        cct_disable_mouse();
                        return;
                    }
                }

                cct_showstr(0, info_y - 1, msg);
            }
        }
    }

    cct_disable_mouse();

}

 /*******************************
  * 扫雷任务 8（基本游戏循环）
  *******************************/
void ms_run_graph_task8_game_basic(void)
{
    MSGame g;
    MSLayout lay;

    int rows;
    int cols;
    int mines;
    int difficulty;

    int hover_r;
    int hover_c;

    int started;
    int info_y;

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

    started = 0;

    ms_graph_setup_console_for_board(rows, cols);

    lay.x0 = 6;
    lay.y0 = 4;
    lay.rows = rows;
    lay.cols = cols;

    ms_graph_draw_frame(lay);

    /* 初始：全覆盖（由 ms_graph_render_all / ms_graph_render_cell 决定颜色） */
    ms_graph_render_all(lay, g);

    hover_r = -1;
    hover_c = -1;

    info_y = lay.y0 + 3 * rows + 4;

    while (1)
    {
        int mx;
        int my;
        int ma;
        int k1;
        int k2;
        int evt;

        int r;
        int c;
        int ok;

        evt = cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

        if (evt == CCT_KEYBOARD_EVENT)
        {
            if (k1 == 27)
            {
                break;
            }
        }
        else
        {
            ok = ms_mouse_to_cell(lay, mx, my, r, c);

            /* 悬停高亮：最大化复用 ms_graph_render_cell */
            if (ok)
            {
                if (hover_r != r || hover_c != c)
                {
                    if (hover_r >= 0)
                    {
                        ms_graph_render_cell(lay, g, hover_r, hover_c, 0);
                    }

                    ms_graph_render_cell(lay, g, r, c, 1);
                    hover_r = r;
                    hover_c = c;
                }
            }
            else
            {
                if (hover_r >= 0)
                {
                    ms_graph_render_cell(lay, g, hover_r, hover_c, 0);
                    hover_r = -1;
                    hover_c = -1;
                }
            }

            /* 更新状态栏：当前位置 + 剩余雷数 + 时间 */
            {
                char msg[96];
                int pos;

                ms_graph_status_clear_line(info_y + 2);

                pos = 0;
                pos = ms_graph_append(msg, 96, pos, "[当前位置] ");
                cct_showstr(0, 0, "esc退出");

                if (!ok)
                {
                    pos = ms_graph_append(msg, 96, pos, "位置非法   ");
                }
                else
                {
                    char rowbuf[3];
                    int colnum;
                    char colbuf[16];
                    int colpos;
                    int rp;

                    rowbuf[0] = ms_row_label(r);
                    rowbuf[1] = 0;

                    pos = ms_graph_append(msg, 96, pos, rowbuf);
                    pos = ms_graph_append(msg, 96, pos, "行");

                    colnum = c + 1;
                    colpos = 0;
                    rp = 0;

                    colbuf[2] = 0;
                    if (colnum <= 26)
                    {
                        colbuf[0] = ms_graph_col_label(c);
                        colbuf[1] = ' ';
                    }
                    else
                    {
                        colbuf[0] = '2';
                        colbuf[1] = (char)('6' + colnum - 27);

                    }

                   pos = ms_graph_append(msg, 96, pos, colbuf);
                    pos = ms_graph_append(msg, 96, pos, "列   ");
                }
                cct_showstr(0, info_y + 1, msg);

            }
            if (!ok)
            {
                continue;
            }

            if (g.game_over)
            {
                continue;
            }

            /* 右键：标记/取消标记（仅对覆盖格生效；打开格无效） */
            if (ma == MOUSE_RIGHT_BUTTON_CLICK)
            {
                if (g.state[r][c] == MS_CELL_COVERED)
                {
                    g.state[r][c] = MS_CELL_FLAGGED;
                    g.flag_count++;
                }
                else
                {
                    if (g.state[r][c] == MS_CELL_FLAGGED)
                    {
                        g.state[r][c] = MS_CELL_COVERED;
                        if (g.flag_count > 0)
                        {
                            g.flag_count--;
                        }
                    }
                }

                ms_check_win(g);
                ms_graph_render_all(lay, g);
            }

            /* 左键：打开（首击生成棋盘且保证为0） */
            if (ma == MOUSE_LEFT_BUTTON_CLICK)
            {
                if (g.state[r][c] == MS_CELL_FLAGGED)
                {
                    continue;
                }

                if (!started)
                {
                    ms_generate_board_first_click_zero(g, r, c);
                    g.start_tick_ms = ms_now_tick_ms();
                    started = 1;
                }

                ms_open_cell(g, r, c);
                ms_check_win(g);
                ms_graph_render_all(lay, g);
            }

            /* 判断结束：胜/负提示 + 按回车返回 */
            if (g.game_over)
            {
                if (g.win)
                {
                    cct_showstr(0, info_y + 3, "WIN!");
                }
                else
                {
                    cct_showstr(0, info_y + 3, "BOOM!");
                }

                to_be_continued(NULL, 0, info_y + 6);
                break;
            }
        }
    }

    cct_disable_mouse();
}

/*******************************
 * 扫雷任务 9（完整游戏循环）
 *******************************/
void ms_run_graph_task9_game_full(void)
{
    MSGame g;
    MSLayout lay;

    int rows;
    int cols;
    int mines;
    int difficulty;

    int hover_r;
    int hover_c;

    int started;
    int info_y;

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

    started = 0;

    ms_graph_setup_console_for_board(rows, cols);

    lay.x0 = 6;
    lay.y0 = 4;
    lay.rows = rows;
    lay.cols = cols;

    ms_graph_draw_frame(lay);

    /* 初始：全覆盖（由 ms_graph_render_all / ms_graph_render_cell 决定颜色） */
    ms_graph_render_all(lay, g);

    hover_r = -1;
    hover_c = -1;

    info_y = lay.y0 + 3 * rows + 1;

    /* 状态栏 */
    ms_graph_status_clear_line(info_y + 1);
    cct_showstr(0, info_y + 1, "[当前位置] --行--列   [剩余雷数]");

    ms_graph_status_clear_line(info_y + 2);
    cct_showstr(0, info_y + 2, "[时间(s)] 0");

    while (1)
    {
        int mx;
        int my;
        int ma;
        int k1;
        int k2;
        int evt;

        int r;
        int c;
        int ok;

        int show_time;
        long long last_time_s;

        show_time = 0;
        last_time_s = 0;

        evt = cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

        if (evt == CCT_KEYBOARD_EVENT)
        {
            if (k1 == 27)
            {
                break;
            }

            if (k1 == ' ')
            {
                /* 空格：刷新/显示时间 */
                show_time = 1;

                if (!started)
                {
                    last_time_s = 0;
                }
                else
                {
                    last_time_s = (ms_now_tick_ms() - g.start_tick_ms) / 1000;
                }

                cct_showstr(0, info_y + 2, "[时间(s)] ");
                cct_showint(10, info_y + 2, (int)last_time_s);
            }
        }
        else
        {
            ok = ms_mouse_to_cell(lay, mx, my, r, c);

            /* 悬停高亮：最大化复用 ms_graph_render_cell */
            if (ok)
            {
                if (hover_r != r || hover_c != c)
                {
                    if (hover_r >= 0)
                    {
                        ms_graph_render_cell(lay, g, hover_r, hover_c, 0);
                    }

                    ms_graph_render_cell(lay, g, r, c, 1);
                    hover_r = r;
                    hover_c = c;
                }
            }
            else
            {
                if (hover_r >= 0)
                {
                    ms_graph_render_cell(lay, g, hover_r, hover_c, 0);
                    hover_r = -1;
                    hover_c = -1;
                }
            }

            /* 更新状态栏：当前位置 + 剩余雷数 + 时间 */
            {
                int remain;
                long long used_s;
                char msg[96];
                int pos;

                ms_graph_status_clear_line(info_y + 2);

                pos = 0;
                pos = ms_graph_append(msg, 96, pos, "[当前位置] ");
				cct_showstr(0, 0, "时间随鼠标移动自动刷新，或按空格键刷新，esc退出");

                if (!ok)
                {
                    pos = ms_graph_append(msg, 96, pos, "位置非法    ");
                }
                else
                {
                    char rowbuf[3];
                    int colnum;
                    char colbuf[16];
                    int colpos;
                    int rp;

                    rowbuf[0] = ms_row_label(r);
                    rowbuf[1] = 0;

                    pos = ms_graph_append(msg, 96, pos, rowbuf);
                    pos = ms_graph_append(msg, 96, pos, "行");

                    colnum = c + 1;
                    colpos = 0;
                    rp = 0;

                    colbuf[2] = 0;
                    if (colnum <= 26)
                    {
                        colbuf[0] = ms_graph_col_label(c);
                        colbuf[1] = ' ';
                    }
                    else
                    {
                        colbuf[0] = '2';
                        colbuf[1] = (char)('6' + colnum - 27);

                    }

                    pos = ms_graph_append(msg, 96, pos, colbuf);
                    pos = ms_graph_append(msg, 96, pos, "列   ");
                }

                pos = ms_graph_append(msg, 96, pos, "[剩余雷数]     ");

                remain = mines - g.flag_count;
                if (remain < 0)
                {
                    remain = 0;
                }

                cct_showstr(0, info_y + 1, msg);
                cct_showstr(45, info_y + 1, "   ");
                cct_showint(45, info_y + 1, remain);

                if (!started)
                {
                    used_s = 0;
                }
                else
                {
                    used_s = (ms_now_tick_ms() - g.start_tick_ms) / 1000;
                }

                cct_showstr(0, info_y + 2, "[时间(s)]         ");
                cct_showint(10, info_y + 2, (int)used_s);
            }

            if (!ok)
            {
                continue;
            }

            if (g.game_over)
            {
                continue;
            }

            /* 右键：标记/取消标记（仅对覆盖格生效；打开格无效） */
            if (ma == MOUSE_RIGHT_BUTTON_CLICK)
            {
                if (g.state[r][c] == MS_CELL_COVERED)
                {
                    g.state[r][c] = MS_CELL_FLAGGED;
                    g.flag_count++;
                }
                else
                {
                    if (g.state[r][c] == MS_CELL_FLAGGED)
                    {
                        g.state[r][c] = MS_CELL_COVERED;
                        if (g.flag_count > 0)
                        {
                            g.flag_count--;
                        }
                    }
                }

                ms_check_win(g);
                ms_graph_render_all(lay, g);
            }

            /* 左键：打开（首击生成棋盘且保证为0） */
            if (ma == MOUSE_LEFT_BUTTON_CLICK)
            {
                if (g.state[r][c] == MS_CELL_FLAGGED)
                {
                    continue;
                }

                if (!started)
                {
                    ms_generate_board_first_click_zero(g, r, c);
                    g.start_tick_ms = ms_now_tick_ms();
                    started = 1;
                }

                ms_open_cell(g, r, c);
                ms_check_win(g);
                ms_graph_render_all(lay, g);
            }

            /* 判断结束：胜/负提示 + 按回车返回 */
            if (g.game_over)
            {
                long long used_s;

                ms_graph_status_clear_line(info_y + 3);
                ms_graph_status_clear_line(info_y + 4);

                if (!started)
                {
                    used_s = 0;
                }
                else
                {
                    used_s = (ms_now_tick_ms() - g.start_tick_ms) / 1000;
                }

                if (g.win)
                {
                    cct_showstr(0, info_y + 3, "你赢了");
                }
                else
                {
                    cct_showstr(0, info_y + 3, "你输了");
                }

                cct_showstr(0, info_y + 4, "最终用时 ");
                cct_showint(15, info_y + 4, (int)used_s);

                to_be_continued(NULL, 0, info_y + 6);
                break;
            }
        }
    }

    cct_disable_mouse();
}
