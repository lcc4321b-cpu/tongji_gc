#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>

#include "hanoi.h"
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"

using namespace std;

/* -------------------- 允许的全局状态（按PDF白名单） -------------------- */
static int g_total_steps = 0;
static int g_cnt[3] = { 0, 0, 0 };
static int g_rod[3][MAX_LAYER] = { 0 };
static int g_delay_ms = 0;

/* -------------------- 基础工具 -------------------- */
static void flush_bad_input()
{
    cin.clear();
    cin.ignore(1024, '\n');
}

static int peg_index(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        c = (char)(c - 'a' + 'A');
    }
    if (c == 'A')
    {
        return 0;
    }
    if (c == 'B')
    {
        return 1;
    }
    if (c == 'C')
    {
        return 2;
    }
    return -1;
}

static char peg_name(int idx)
{
    return (char)('A' + idx);
}

static int aux_peg(int src, int dst)
{
    return 3 - src - dst;
}

static int console_visible_width()
{
    HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int w;

    w = 120;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE)
    {
        return w;
    }

    if (GetConsoleScreenBufferInfo(hOut, &csbi))
    {
        w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    return w;
}

static void clear_line_from(int x, int y)
{
    // 获取当前控制台的宽度（假设有变量 `console_width` 用于存储此宽度）
    int console_width = 80;  // 或者通过其他方法获取当前控制台的宽度

    // 如果指定的 x 位置小于 0，则设为 0，保证不会越界
    if (x < 0)
    {
        x = 0;
    }

    // 如果指定的 x 位置大于控制台宽度，直接返回
    if (x >= console_width)
    {
        return;
    }

    // 使用 cct_gotoxy 将光标移动到指定位置
    cct_gotoxy(x, y);

    // 清除从 x 位置开始到行尾的所有字符
    for (int i = x; i < console_width; i++)
    {
        cout << ' ';  // 输出空格清除字符
    }

    // 重新将光标定位到 x, y 位置
    cct_gotoxy(x, y);
}

/* -------------------- 延时/单步 -------------------- */
static void step_delay(int ms)
{
    if (ms == 0)
    {
        while (1)
        {
            int ch = _getch();
            if (ch == '\r')
            {
                break;
            }
        }
    }
	else if (ms < 0)
    {
        return;
    }
    else
    {
        Sleep(ms);
    }
}

/* -------------------- 输入（共用） -------------------- */
static void input_layer(int* n)
{
    while (1)
    {
        int tn = 0;

        cout << "请输入汉诺塔层数(1-" << MAX_LAYER << "):" << endl;
        if (!(cin >> tn))
        {
            flush_bad_input();
            continue;
        }
        flush_bad_input();

        if (tn < 1 || tn > MAX_LAYER)
        {
            continue;
        }

        *n = tn;
        break;
    }
}

static void input_src(int* src)
{
    while (1)
    {
        char a = 0;

        cout << "请输入起始柱(A-C):" << endl;
        if (!(cin >> a))
        {
            flush_bad_input();
            continue;
        }
        flush_bad_input();

        *src = peg_index(a);
        if (*src < 0 || *src > 2)
        {
            continue;
        }
        break;
    }
}

static void input_dst_not_equal_src(int src, int* dst)
{
    while (1)
    {
        char b = 0;

        cout << "请输入目标柱(A-C):" << endl;
        if (!(cin >> b))
        {
            flush_bad_input();
            continue;
        }
        flush_bad_input();

        *dst = peg_index(b);
        if (*dst < 0 || *dst > 2)
        {
            continue;
        }
        if (*dst == src)
        {
            cout << "目标柱(" << peg_name(*dst) << ")不能与起始柱(" << peg_name(src) << ")相同" << endl;
            continue;
        }
        break;
    }
}

static void input_speed(int menu)
{
    int limit = 0;

    if (menu == 4)
    {
        limit = 200;
        cout << "请输入移动速度(0-200：0-按回车单步演示 1-200:延时1-200ms)" << endl;
    }
    else
    {
        limit = 20;
        cout << "请输入移动速度(0-20：0-按回车单步演示 1-20:延时1-20ms)" << endl;
    }

    while (1)
    {
        int v = 0;

        if (!(cin >> v))
        {
            flush_bad_input();
            continue;
        }
        flush_bad_input();

        if (v < 0 || v > limit)
        {
            continue;
        }

        g_delay_ms = v;
        break;
    }
}

static void hanoi_input(int menu, int* n, int* src, int* dst)
{
    if (menu == 5)
        return;
    if (n != NULL)
    {
        *n = 0;
    }
    if (src != NULL)
    {
        *src = 0;
    }
    if (dst != NULL)
    {
        *dst = 2;
    }

    if (menu == 5)
    {
        return;
    }

    if (n != NULL)
    {
        input_layer(n);
    }

    if (src != NULL)
    {
        input_src(src);
    }

    if (menu != 6)
    {
        if (dst != NULL)
        {
            input_dst_not_equal_src(*src, dst);
        }
    }

    if (menu == 4 || menu == 7 || menu == 8 || menu == 9)
    {
        input_speed(menu);
    }
}

/* -------------------- 盘面栈（底->顶） -------------------- */
static void stacks_reset(int n, int src)
{
    int p = 0;

    while (p < 3)
    {
        int j = 0;

        g_cnt[p] = 0;
        while (j < MAX_LAYER)
        {
            g_rod[p][j] = 0;
            j++;
        }

        p++;
    }

    int disk = n;
    while (disk >= 1)
    {
        g_rod[src][g_cnt[src]] = disk;
        g_cnt[src]++;
        disk--;
    }
}

static int top_disk(int peg)
{
    if (g_cnt[peg] <= 0)
    {
        return 0;
    }
    return g_rod[peg][g_cnt[peg] - 1];
}

static int can_move(int s, int d)
{
    if (g_cnt[s] <= 0)
    {
        return 0;
    }
    if (g_cnt[d] <= 0)
    {
        return 1;
    }
    if (top_disk(s) < top_disk(d))
    {
        return 1;
    }
    return 2;
}

static int pop_disk(int peg)
{
    int disk = 0;

    if (g_cnt[peg] <= 0)
    {
        return 0;
    }

    g_cnt[peg]--;
    disk = g_rod[peg][g_cnt[peg]];
    g_rod[peg][g_cnt[peg]] = 0;

    return disk;
}

static void push_disk(int peg, int disk)
{
    g_rod[peg][g_cnt[peg]] = disk;
    g_cnt[peg]++;
}

static int move_logical(int s, int d)
{
    int disk = 0;

    if (!can_move(s, d))
    {
        return 0;
    }

    disk = pop_disk(s);
    push_disk(d, disk);

    return disk;
}

/* -------------------- 横向输出（菜单3/4/8共用） -------------------- */
static void print_rod_field(int peg_idx, int width)
{
    int printed = 0;

    cout << peg_name(peg_idx) << ":";
    printed += 2;

    int i = 0;
    while (i < g_cnt[peg_idx])
    {
        if (i == 0)
        {
            cout << setw(2) << g_rod[peg_idx][i] << ' ';
            printed += 3;
        }
        else
        {
            cout << g_rod[peg_idx][i] << ' ';
            printed += 2;
        }
        i++;
    }

    while (printed < width)
    {
        cout << ' ';
        printed++;
    }
}

static void print_hori_line(int menu, int step, int disk, int src, int dst)
{
    int use_goto;
    int x;
    int y;

    use_goto = 0;
    x = 0;
    y = 0;

    if (menu == 4)
    {
        use_goto = 1;
        x = MenuItem4_Start_X;
        y = MenuItem4_Start_Y;
    }
    if (menu == 8)
    {
        use_goto = 1;
        x = MenuItem8_Start_X;
        y = MenuItem8_Start_Y;
    }
    if (menu == 9)
    {
        use_goto = 1;
        x = MenuItem9_Start_X;
        y = MenuItem9_Start_Y;
    }

    if (use_goto)
    {
        cct_gotoxy(x, y);

        //clear_line_from(x, y);
    }

    if (step == 0)
    {
        cout << "初始  ";
        print_rod_field(0, 23);
        print_rod_field(1, 23);
        print_rod_field(2, 23);

        if (menu == 1 || menu == 2 || menu == 3)
        {
            cout << endl;
        }

        return;
    }

    if (menu == 1)
    {
        cout << setw(2) << disk << "#: " << peg_name(src) << "-->" << peg_name(dst);
        cout << endl;
        return;
    }

    if (menu == 2)
    {
        cout << "第" << setw(4) << step << "步(";
        cout << setw(2) << disk << "#: " << peg_name(src) << "-->" << peg_name(dst);
        cout << ")";
        cout << endl;
        return;
    }

    if (menu == 3)
    {
        cout << "第" << setw(4) << step << "步(";
        cout << setw(2) << disk << "#: " << peg_name(src) << "-->" << peg_name(dst);
        cout << ")  ";
        print_rod_field(0, 23);
        print_rod_field(1, 23);
        print_rod_field(2, 23);
        cout << endl;
        return;
    }

    cout << "第" << setw(4) << step << "步(";
    cout << setw(2) << disk << "#: " << peg_name(src) << "-->" << peg_name(dst);
    cout << ")  ";
    print_rod_field(0, 23);
    print_rod_field(1, 23);
    print_rod_field(2, 23);
}

/* -------------------- 纵向输出（菜单4/8/9共用） -------------------- */
static void print_disk_cell(int disk)
{
    if (disk <= 0)
    {
        cout << "  ";
    }
    else
    {
        cout << setw(2) << disk;
    }
}

static void show_vertical_view(int menu)
{
    int start_x = 0;
    int start_y = 0;

    if (menu == 4)
    {
        start_x = MenuItem4_Start_X;
        start_y = MenuItem4_Start_Y;
    }
    else if (menu == 8)
    {
        start_x = MenuItem8_Start_X;
        start_y = MenuItem8_Start_Y;
    }
    else if (menu == 9)
    {
        start_x = MenuItem9_Start_X;
        start_y = MenuItem9_Start_Y;
    }
    else
    {
        return;
    }

    int y_letter = start_y + Underpan_A_Y_OFFSET;
    int y_dash = y_letter - 1;

    int xA = start_x + Underpan_A_X_OFFSET;
    int xB = xA + Underpan_Distance;
    int xC = xA + 2 * Underpan_Distance;

    int r = 0;
    while (r < MAX_LAYER)
    {
        int y = y_dash - 1 - r;

        cct_gotoxy(xA, y);
        cout << "  ";
        cct_gotoxy(xB, y);
        cout << "  ";
        cct_gotoxy(xC, y);
        cout << "  ";

        r++;
    }

    int p = 0;
    while (p < 3)
    {
        int level = 0;

        while (level < g_cnt[p])
        {
            int y = y_dash - 1 - level;
            int x = xA + p * Underpan_Distance - 1;

            cct_gotoxy(x, y);
            print_disk_cell(g_rod[p][level]);

            level++;
        }

        p++;
    }

    cct_gotoxy(xA - 2, y_dash);
    int len =  2 * Underpan_Distance + 5;
    int i = 0;
    while (i < len)
    {
        cout << '=';
        i++;
    }

    cct_gotoxy(xA, y_letter);
    cout << 'A';
    cct_gotoxy(xB, y_letter);
    cout << 'B';
    cct_gotoxy(xC, y_letter);
    cout << 'C';
}

/* -------------------- 状态栏（步数） -------------------- */
static void status_print_steps(int menu)
{
    clear_line_from(Status_Line_X, Status_Line_Y);

    if (menu == 6 || menu == 7 || menu == 8 || menu == 9)
    {
        cout << "汉诺塔综合演示  ";
    }

    cout << "总计步数: " << setw(4) << g_total_steps;
}

/* -------------------- HDC 坐标系统 -------------------- */
static int HDC_Underpan_Width()
{
    return 23 * HDC_Base_Width;
}

static int hdc_base_x(int peg)
{
    return HDC_Start_X + peg * (HDC_Underpan_Width() + HDC_Underpan_Distance);
}

static int hdc_base_y()
{
    return HDC_Start_Y;
}

static int hdc_pillar_h()
{
    return (MAX_LAYER + 2) * HDC_Base_High;
}

static int hdc_pillar_x(int peg)
{
    return hdc_base_x(peg) + 11 * HDC_Base_Width;
}

static int hdc_pillar_y()
{
    return hdc_base_y() - hdc_pillar_h();
}

static int hdc_disk_w(int disk)
{
    return (2 * disk + 1) * HDC_Base_Width;
}

static int hdc_disk_x(int peg, int disk)
{
    return hdc_base_x(peg) + (11 - disk) * HDC_Base_Width;
}

static int hdc_level_y(int level_index)
{
    return hdc_base_y() - (level_index + 1) * HDC_Base_High;
}

/* -------------------- HDC 场景绘制（菜单5-9共用） -------------------- */
static void hdc_prepare_canvas()
{
    cct_cls();
    hdc_init(HDC_COLOR[0], HDC_COLOR[MAX_LAYER + 1], 8 * 120, 16 * 40);
    hdc_cls();
}

static void hdc_draw_three_pillars()
{
    int peg = 0;

    while (peg < 3)
    {
        int bx = hdc_base_x(peg);
        int by = hdc_base_y();

        hdc_rectangle(bx, by, HDC_Underpan_Width(), HDC_Base_High, HDC_COLOR[MAX_LAYER + 1]);
        Sleep(HDC_Init_Delay);

        peg++;
    }

    peg = 0;
    while (peg < 3)
    {
        int px = hdc_pillar_x(peg);
        int py = hdc_pillar_y();
        int ph = hdc_pillar_h();

        hdc_rectangle(px, py, HDC_Base_Width, ph, HDC_COLOR[MAX_LAYER + 1]);
        Sleep(HDC_Init_Delay);

        peg++;
    }
}

static void hdc_draw_one_disk(int peg, int disk, int level_index)
{
    int x = hdc_disk_x(peg, disk);
    int y = hdc_level_y(level_index);
    int w = hdc_disk_w(disk);

    hdc_rectangle(x, y, w, HDC_Base_High, HDC_COLOR[disk]);
}

static void hdc_draw_disks_with_delay()
{
    int peg = 0;

    while (peg < 3)
    {
        int level = 0;

        while (level < g_cnt[peg])
        {
            int disk = g_rod[peg][level];

            hdc_draw_one_disk(peg, disk, level);
            Sleep(HDC_Init_Delay);

            level++;
        }

        peg++;
    }
}

/* -------------------- HDC 局部恢复（避免残影/柱子破坏） -------------------- */
static void hdc_draw_intersection(int x, int y, int w, int h, int rx, int ry, int rw, int rh, int color)
{
    int x1 = x;
    int y1 = y;
    int x2 = x + w;
    int y2 = y + h;

    int r1 = rx;
    int s1 = ry;
    int r2 = rx + rw;
    int s2 = ry + rh;

    int ix1 = x1;
    int iy1 = y1;
    int ix2 = x2;
    int iy2 = y2;

    if (ix1 < r1)
    {
        ix1 = r1;
    }
    if (iy1 < s1)
    {
        iy1 = s1;
    }
    if (ix2 > r2)
    {
        ix2 = r2;
    }
    if (iy2 > s2)
    {
        iy2 = s2;
    }

    if (ix2 > ix1 && iy2 > iy1)
    {
        hdc_rectangle(ix1, iy1, ix2 - ix1, iy2 - iy1, color);
    }
}

static void hdc_restore_scene_in_rect(int x, int y, int w, int h)
{
    int peg = 0;

    peg = 0;
    while (peg < 3)
    {
        int bx = hdc_base_x(peg);
        int by = hdc_base_y();
        int bw = HDC_Underpan_Width();
        int bh = HDC_Base_High;

        int px = hdc_pillar_x(peg);
        int py = hdc_pillar_y();
        int pw = HDC_Base_Width;
        int ph = hdc_pillar_h();

        hdc_draw_intersection(x, y, w, h, bx, by, bw, bh, HDC_COLOR[MAX_LAYER + 1]);
        hdc_draw_intersection(x, y, w, h, px, py, pw, ph, HDC_COLOR[MAX_LAYER + 1]);

        peg++;
    }

    peg = 0;
    while (peg < 3)
    {
        int level = 0;

        while (level < g_cnt[peg])
        {
            int disk = g_rod[peg][level];

            int dx = hdc_disk_x(peg, disk);
            int dy = hdc_level_y(level);
            int dw = hdc_disk_w(disk);
            int dh = HDC_Base_High;

            hdc_draw_intersection(x, y, w, h, dx, dy, dw, dh, HDC_COLOR[disk]);

            level++;
        }

        peg++;
    }
}

static void hdc_erase_rect_and_restore(int x, int y, int w, int h)
{
    hdc_rectangle(x, y, w, h, HDC_COLOR[0]);
    hdc_restore_scene_in_rect(x, y, w, h);
}

/* -------------------- HDC 动画（盘子移动：菜单7/8/9共用） -------------------- */
static int hdc_move_up_strip(int disk, int x, int y, int w, int delay_ms)
{
    while (y > HDC_Top_Y)
    {
        int step = HDC_Step_Y;

        if (y - step < HDC_Top_Y)
        {
            step = y - HDC_Top_Y;
        }

        hdc_erase_rect_and_restore(x, y + HDC_Base_High - step, w, step);
        y = y - step;
        hdc_rectangle(x, y, w, step, HDC_COLOR[disk]);

        step_delay(delay_ms);
    }

    return y;
}

static int hdc_move_down_strip(int disk, int x, int y, int w, int dst_y, int delay_ms)
{
    while (y < dst_y)
    {
        int step = HDC_Step_Y;

        if (y + step > dst_y)
        {
            step = dst_y - y;
        }

        hdc_erase_rect_and_restore(x, y, w, step);
        y = y + step;
        hdc_rectangle(x, y + HDC_Base_High - step, w, step, HDC_COLOR[disk]);

        step_delay(delay_ms);
    }

    return y;
}

static int hdc_move_right_strip(int disk, int x, int y, int w, int dst_x, int delay_ms)
{
    while (x < dst_x)
    {
        int step = HDC_Step_X;

        if (x + step > dst_x)
        {
            step = dst_x - x;
        }

        hdc_erase_rect_and_restore(x, y, step, HDC_Base_High);
        x = x + step;
        hdc_rectangle(x + w - step, y, step, HDC_Base_High, HDC_COLOR[disk]);

        step_delay(delay_ms);
    }

    return x;
}

static int hdc_move_left_strip(int disk, int x, int y, int w, int dst_x, int delay_ms)
{
    while (x > dst_x)
    {
        int step = HDC_Step_X;

        if (x - step < dst_x)
        {
            step = x - dst_x;
        }

        hdc_erase_rect_and_restore(x + w - step, y, step, HDC_Base_High);
        x = x - step;
        hdc_rectangle(x, y, step, HDC_Base_High, HDC_COLOR[disk]);

        step_delay(delay_ms);
    }

    return x;
}

static void hdc_animate_disk_move(int src, int dst, int disk, int src_level, int dst_level, int delay_ms)
{
    int w = hdc_disk_w(disk);

    int x = hdc_disk_x(src, disk);
    int y = hdc_level_y(src_level);

    int dst_x = hdc_disk_x(dst, disk);
    int dst_y = hdc_level_y(dst_level);

    y = hdc_move_up_strip(disk, x, y, w, delay_ms);

    if (x < dst_x)
    {
        x = hdc_move_right_strip(disk, x, y, w, dst_x, delay_ms);
    }
    else if (x > dst_x)
    {
        x = hdc_move_left_strip(disk, x, y, w, dst_x, delay_ms);
    }

    (void)x;
    (void)hdc_move_down_strip(disk, dst_x, y, w, dst_y, delay_ms);
}

static int hdc_move_top_disk_stack(int src, int dst, int delay_ms)
{
    int disk = 0;
    int src_level = 0;
    int dst_level = 0;

    if (!can_move(src, dst))
    {
        return 0;
    }

    src_level = g_cnt[src] - 1;
    dst_level = g_cnt[dst];

    disk = pop_disk(src);
    hdc_animate_disk_move(src, dst, disk, src_level, dst_level, delay_ms);
    push_disk(dst, disk);

    return disk;
}

/* -------------------- 单步动作封装（递归/游戏都用它） -------------------- */
static void do_one_move(int src, int dst, int menu)
{
    int disk;
    int used_delay;

    disk = 0;

    g_total_steps++;

    used_delay = g_delay_ms;
    if (menu == 8)
    {
        if (g_total_steps > 7)
        {
            used_delay = -1;
        }
    }

    if (menu == 8 || menu == 9)
    {
        disk = hdc_move_top_disk_stack(src, dst, used_delay);
    }
    else
    {
        disk = move_logical(src, dst);
    }

    if (menu == 1 || menu == 2 || menu == 3)
    {
        print_hori_line(menu, g_total_steps, disk, src, dst);
        return;
    }

    if (menu == 4)
    {
        print_hori_line(menu, g_total_steps, disk, src, dst);
        show_vertical_view(menu);
        status_print_steps(menu);
        step_delay(g_delay_ms);
        return;
    }

    if (menu == 8 || menu == 9)
    {
        print_hori_line(menu, g_total_steps, disk, src, dst);
        show_vertical_view(menu);
        status_print_steps(menu);
        return;
    }
}

/* -------------------- 唯一递归函数（≤15行，菜单1/2/3/4/8共用） -------------------- */
static void hanoi_rec(int n, int src, int aux, int dst, int menu)
{
    if (n <= 0)
    {
        return;
    }
    hanoi_rec(n - 1, src, dst, aux, menu);
    do_one_move(src, dst, menu);
    hanoi_rec(n - 1, aux, src, dst, menu);
}

/* -------------------- 菜单项5-9 -------------------- */
static void run_item_5()
{
    hdc_prepare_canvas();
    hdc_draw_three_pillars();
}

static void run_item_6(int n, int src)
{
    hdc_prepare_canvas();
    hdc_draw_three_pillars();

    stacks_reset(n, src);
    hdc_draw_disks_with_delay();
    g_total_steps = 0;
    status_print_steps(6);

}

static void run_item_7(int n, int src, int dst)
{
    int aux = aux_peg(src, dst);
    int first_dst = dst;

    if ((n % 2) == 0)
    {
        first_dst = aux;
    }

    hdc_prepare_canvas();
    hdc_draw_three_pillars();
    g_total_steps = 0;
    status_print_steps(7);

    stacks_reset(n, src);
    hdc_draw_disks_with_delay();

    (void)hdc_move_top_disk_stack(src, first_dst, g_delay_ms);
    status_print_steps(7);

}

static void run_item_8(int n, int src, int dst)
{
    int aux = aux_peg(src, dst);

    g_total_steps = 0;

    hdc_prepare_canvas();
    hdc_draw_three_pillars();

    stacks_reset(n, src);
    hdc_draw_disks_with_delay();

    print_hori_line(8, 0, 0, 0, 0);
    show_vertical_view(8);
    status_print_steps(8);

    hanoi_rec(n, src, aux, dst, 8);
}

static void clear_prompt_line(int y)
{
    cct_gotoxy(0, y);
    clear_line_from(0,y);
}

static void run_item_9(int n, int src, int dst)
{
    g_total_steps = 0;

    hdc_prepare_canvas();
    hdc_draw_three_pillars();

    stacks_reset(n, src);
    hdc_draw_disks_with_delay();

    print_hori_line(9, 0, 0, 0, 0);
    show_vertical_view(9);
    status_print_steps(9);

    while (g_cnt[dst] < n)
    {
        int s = -1;
        int d = -1;
        char a = 0;
        char b = 0;

        clear_prompt_line(Status_Line_Y + 1);
        clear_prompt_line(Status_Line_Y + 2);

        cct_gotoxy(0, Status_Line_Y + 1);
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";

        
        if (!(cin >> a >> b))
        {
            flush_bad_input();
            continue;
        }
        if (a == 'Q' || a == 'q')
        {
            break;
		}
        flush_bad_input();

        s = peg_index(a);
        d = peg_index(b);

        if (s < 0 || s > 2 || d < 0 || d > 2)
        {
            cct_gotoxy(0, Status_Line_Y + 2);
            cout << "输入必须是 A/B/C(大小写均可)，请重输";
            continue;
        }
        if (s == d)
        {
            cct_gotoxy(0, Status_Line_Y + 2);
            cout << "源柱与目标柱不能相同，请重输";
            continue;
        }
        if (can_move(s, d)==0)
        {
            cct_gotoxy(0, Status_Line_Y + 2);
            cout << "源柱为空";
            continue;
        }
        else if (can_move(s, d)==2)
        {
            cct_gotoxy(0, Status_Line_Y + 2);
            cout << "大盘压小盘，非法移动";
            continue;
		}

        do_one_move(s, d, 9);
    }

    clear_prompt_line(Status_Line_Y + 1);
    clear_prompt_line(Status_Line_Y + 2);
    cct_gotoxy(0, Status_Line_Y + 1);
    cout << "游戏结束";
}

/* -------------------- 对外接口：hanoi_run -------------------- */
int hanoi_run(int menu)
{
    int n = 0;
    int src = 0;
    int dst = 2;

    if (menu == 0)
    {
        return 0;
    }

    hanoi_input(menu, &n, &src, &dst);

    if (menu == 1)
    {
        g_total_steps = 0;
        stacks_reset(n, src);
        hanoi_rec(n, src, aux_peg(src, dst), dst, 1);
        return 0;
    }

    if (menu == 2)
    {
        g_total_steps = 0;
        stacks_reset(n, src);
        hanoi_rec(n, src, aux_peg(src, dst), dst, 2);
        return 0;
    }

    if (menu == 3)
    {
        g_total_steps = 0;
        stacks_reset(n, src);
        print_hori_line(3, 0, 0, 0, 0);
        hanoi_rec(n, src, aux_peg(src, dst), dst, 3);
        return 0;
    }

    if (menu == 4)
    {
        g_total_steps = 0;
        stacks_reset(n, src);

        cct_cls();
        print_hori_line(4, 0, 0, 0, 0);
        show_vertical_view(4);
        status_print_steps(4);

        hanoi_rec(n, src, aux_peg(src, dst), dst, 4);
        return 0;
    }

    if (menu == 5)
    {
        run_item_5();
        return 0;
    }

    if (menu == 6)
    {
        run_item_6(n, src);
        return 0;
    }

    if (menu == 7)
    {
        run_item_7(n, src, dst);
        return 0;
    }

    if (menu == 8)
    {
        run_item_8(n, src, dst);
        return 0;
    }

    if (menu == 9)
    {
        run_item_9(n, src, dst);
        return 0;
    }

    return 0;
}
