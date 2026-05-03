//2550703 卓03 李良玉
#include"cmd_console_tools.h"

#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H

#define MS_MAX_ROWS 30
#define MS_MAX_COLS 30
#define MS_MAX_CELLS (MS_MAX_ROWS * MS_MAX_COLS)

#define MS_MINE -1

 // 游戏状态
#define MS_CELL_COVERED 0
#define MS_CELL_OPENED 1
#define MS_CELL_FLAGGED 2

// 游戏结构
typedef struct MSGame
{
    int rows;
    int cols;
    int mines;
    int board[MS_MAX_ROWS][MS_MAX_COLS];
    int state[MS_MAX_ROWS][MS_MAX_COLS]; // 当前格子的状态
    int opened_count;
    int flag_count;
    int first_open_done;
    long long start_tick_ms;
    long long end_tick_ms;
    int game_over;
    int win;
} MSGame;

// 布局结构
typedef struct MSLayout
{
    int x0;
    int y0;
    int rows;
    int cols;
} MSLayout;

// 函数声明
char  ms_col_label_n(int c);
int ms_parse_col_after_row(const int cols, int& c, const int x, const int y);
void to_be_continued(const char* msg, const int, const int);
void ms_reset_game(MSGame& g, const int rows, const int cols, const int mines);
void ms_get_difficulty_config(const int difficulty, int& rows, int& cols, int& mines);
int ms_in_bounds(const MSGame& g, const int r, const int c);
void ms_generate_board_random(MSGame& g);
void ms_generate_board_first_click_zero(MSGame& g, const int safe_r, const int safe_c);
void ms_expand_from_zero(MSGame& g, const int r, const int c);
int ms_open_cell(MSGame& g, const int r, const int c);
void ms_toggle_flag(MSGame& g, const int r, const int c);
int ms_check_win(MSGame& g);
char ms_row_label(const int r);
char ms_col_label(const int c,int i);
int ms_parse_rc(const int rows, const int cols, int& r, int& c);
long long ms_now_tick_ms(void);
int ms_cell_to_screen_xy(const MSLayout& lay, const int r, const int c, int& x, int& y);
int ms_mouse_to_cell(const MSLayout& lay, const int mx, const int my, int& r, int& c);
void ms_graph_setup_console_for_board(const int rows, const int cols);
int ms_graph_number_color(const int);
// 特殊输入处理
int ms_parse_special_input(const char* input, MSGame& g);
int ms_input_position(MSGame& g);
void ms_graph_render_all(const MSLayout& lay, const MSGame& g);
// 任务执行
void ms_run_base_task1_show_internal(void);
void ms_run_base_task2_open_init_area(void);
void ms_run_base_task3_play_basic(void);
void ms_run_base_task4_play_full(void);
void ms_run_graph_task5_show_internal(void);
void ms_run_graph_task6_mouse_position(void);
void ms_run_graph_task7_open_init_area(void);
void ms_run_graph_task8_game_basic(void);
void ms_run_graph_task9_game_full(void);
void ms_run_main_menu(void);
#endif // MINE_SWEEPER_H
