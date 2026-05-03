//2550703 卓03 李良玉
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "mine_sweeper.h"
using namespace std;

//解析输入&@
int ms_parse_col_after_row(const int cols, int& c, const int x, const int y)
{
	char cc;

	while (1)
	{
		cc = (char)_getch();

		if (cc == 'Q' || cc == 'q')
		{
			return 0;
		}

		if (cc >= '1' && cc <= '9')
		{
			int tmp;

			tmp = cc - '1';
			if (tmp < cols)
			{
				c = tmp;
				cct_showch(x, y, cc);
				return 1;
			}
			continue;
		}

		if (cols > 9)
		{
			char maxc;

			maxc = (char)('a' + cols - 10);
			if (cc >= 'a' && cc <= maxc)
			{
				c = 9 + (cc - 'a');
				cct_showch(x, y, cc);
				return 1;
			}
		}
	}
}


/***************************************************************************
  函数名称：to_be_continued
  功    能：显示提示并等待回车继续（忽略非回车按键）
***************************************************************************/
void to_be_continued(const char* prompt, const int X = 0, const int Y = 22)
{
	int ch;

	if (prompt != NULL)
	{
		cct_showstr(X, Y, prompt);
	}

	cct_showstr(X, Y + 1, "按回车键继续...");
	while (1)
	{
		ch = _getch();
		if (ch == '\r')
		{
			break;
		}
	}
}
/***************************************************************************
  函数名称：ms_now_tick_ms
  功    能：返回当前 tick（毫秒）
***************************************************************************/
long long ms_now_tick_ms(void)
{
	return (long long)GetTickCount64();
}
/***************************************************************************
  函数名称：ms_get_difficulty_config
  功    能：难度配置（1/2/3）
***************************************************************************/
void ms_get_difficulty_config(const int difficulty, int& rows, int& cols, int& mines)
{
	if (difficulty == 1)
	{
		rows = 9;
		cols = 9;
		mines = 10;
		return;
	}

	if (difficulty == 2)
	{
		rows = 16;
		cols = 16;
		mines = 40;
		return;
	}

	rows = 16;
	cols = 30;
	mines = 99;
}
/***************************************************************************
  函数名称：ms_in_bounds
  检测函数，检查指定行列是否在游戏范围内，返回 1（在范围内）或 0（不在范围内）
***************************************************************************/
int ms_in_bounds(const MSGame& g, const int r, const int c)
{
	if (r < 0)
	{
		return 0;
	}
	if (c < 0)
	{
		return 0;
	}
	if (r >= g.rows)
	{
		return 0;
	}
	if (c >= g.cols)
	{
		return 0;
	}
	return 1;
}
/***************************************************************************
  函数名称：ms_reset_game
  功    能：初始化游戏结构（不生成雷）
***************************************************************************/
void ms_reset_game(MSGame& g, const int rows, const int cols, const int mines)
{
	int r;
	int c;

	g.rows = rows;
	g.cols = cols;
	g.mines = mines;

	g.opened_count = 0;
	g.flag_count = 0;

	g.first_open_done = 0;

	g.start_tick_ms = 0;
	g.end_tick_ms = 0;

	g.game_over = 0;
	g.win = 0;

	r = 0;
	while (r < MS_MAX_ROWS)
	{
		c = 0;
		while (c < MS_MAX_COLS)
		{
			g.board[r][c] = 0;
			g.state[r][c] = MS_CELL_COVERED;
			c++;
		}
		r++;
	}
}
/***************************************************************************
  内部工具：统计邻雷数
***************************************************************************/
static int ms_count_adj_mines(const MSGame& g, const int r, const int c)
{
	int dr;
	int dc;
	int rr;
	int cc;
	int cnt;

	cnt = 0;

	dr = -1;
	while (dr <= 1)
	{
		dc = -1;
		while (dc <= 1)
		{
			if (dr != 0 || dc != 0)
			{
				rr = r + dr;
				cc = c + dc;

				if (rr >= 0 && rr < g.rows && cc >= 0 && cc < g.cols)
				{
					if (g.board[rr][cc] == MS_MINE)
					{
						cnt++;
					}
				}
			}
			dc++;
		}
		dr++;
	}

	return cnt;
}
/***************************************************************************
  函数名称：ms_generate_board_random
  功    能：随机生成雷区（不保证首点安全）
***************************************************************************/
void ms_generate_board_random(MSGame& g)
{
	int r;
	int c;
	int placed;
	int rr;
	int cc;

	r = 0;
	while (r < g.rows)
	{
		c = 0;
		while (c < g.cols)
		{
			g.board[r][c] = 0;
			c++;
		}
		r++;
	}

	srand((unsigned int)time(NULL));

	placed = 0;
	while (placed < g.mines)
	{
		rr = rand() % g.rows;
		cc = rand() % g.cols;

		if (g.board[rr][cc] != MS_MINE)
		{
			g.board[rr][cc] = MS_MINE;
			placed++;
		}
	}

	r = 0;
	while (r < g.rows)
	{
		c = 0;
		while (c < g.cols)
		{
			if (g.board[r][c] != MS_MINE)
			{
				g.board[r][c] = ms_count_adj_mines(g, r, c);
			}
			c++;
		}
		r++;
	}
}

/***************************************************************************
  函数名称：ms_generate_board_first_click_zero
  功    能：首点为 0（首点及周围 8 格无雷）
***************************************************************************/
void ms_generate_board_first_click_zero(MSGame& g, const int safe_r, const int safe_c)
{
	int r;
	int c;
	int placed;
	int rr;
	int cc;
	int dr;
	int dc;
	int ok;
	int forbid_r;
	int forbid_c;

	r = 0;
	while (r < g.rows)
	{
		c = 0;
		while (c < g.cols)
		{
			g.board[r][c] = 0;
			c++;
		}
		r++;
	}

	srand((unsigned int)time(NULL));

	placed = 0;
	while (placed < g.mines)
	{
		rr = rand() % g.rows;
		cc = rand() % g.cols;

		ok = 1;

		dr = -1;
		while (dr <= 1)
		{
			dc = -1;
			while (dc <= 1)
			{
				forbid_r = safe_r + dr;
				forbid_c = safe_c + dc;

				if (rr == forbid_r && cc == forbid_c)
				{
					ok = 0;
				}
				dc++;
			}
			dr++;
		}

		if (!ok)
		{
			continue;
		}

		if (g.board[rr][cc] == MS_MINE)
		{
			continue;
		}

		g.board[rr][cc] = MS_MINE;
		placed++;
	}

	r = 0;
	while (r < g.rows)
	{
		c = 0;
		while (c < g.cols)
		{
			if (g.board[r][c] != MS_MINE)
			{
				g.board[r][c] = ms_count_adj_mines(g, r, c);
			}
			c++;
		}
		r++;
	}
}

/***************************************************************************
  函数名称：ms_expand_from_zero
  功    能：从 0 区域展开（BFS 队列）
***************************************************************************/
void ms_expand_from_zero(MSGame& g, const int r, const int c);
static int ms_count_adj_state(const MSGame& g, const int r, const int c, const int st)
{
	int dr;
	int dc;
	int nr;
	int nc;
	int cnt;

	cnt = 0;

	dr = -1;
	while (dr <= 1)
	{
		dc = -1;
		while (dc <= 1)
		{
			if (!(dr == 0 && dc == 0))
			{
				nr = r + dr;
				nc = c + dc;

				if (ms_in_bounds(g, nr, nc))
				{
					if (g.state[nr][nc] == st)
					{
						cnt++;
					}
				}
			}

			dc++;
		}
		dr++;
	}

	return cnt;
}
static int ms_try_open_covered_cell(MSGame& g, const int r, const int c)
{
	if (!ms_in_bounds(g, r, c))
	{
		return 0;
	}

	if (g.state[r][c] != MS_CELL_COVERED)
	{
		return 0;
	}

	if (g.board[r][c] == MS_MINE)
	{
		g.state[r][c] = MS_CELL_OPENED;
		g.game_over = 1;
		g.win = 0;
		return 1;
	}

	g.state[r][c] = MS_CELL_OPENED;
	g.opened_count++;

	if (g.board[r][c] == 0)
	{
		ms_expand_from_zero(g, r, c);
	}

	return 1;
}
static void ms_auto_open_safe_by_flags(MSGame& g)
{
	int changed;

	if (g.game_over)
	{
		return;
	}

	do
	{
		int r;
		int c;

		changed = 0;

		r = 0;
		while (r < g.rows)
		{
			c = 0;
			while (c < g.cols)
			{
				if (g.state[r][c] == MS_CELL_OPENED)
				{
					int v;
					int flags;

					v = g.board[r][c];

					if (v > 0 && v <= 8)
					{
						flags = ms_count_adj_state(g, r, c, MS_CELL_FLAGGED);

						if (flags == v)
						{
							int dr;
							int dc;
							int nr;
							int nc;

							dr = -1;
							while (dr <= 1)
							{
								dc = -1;
								while (dc <= 1)
								{
									if (!(dr == 0 && dc == 0))
									{
										nr = r + dr;
										nc = c + dc;

										if (ms_in_bounds(g, nr, nc))
										{
											if (g.state[nr][nc] == MS_CELL_COVERED)
											{
												if (ms_try_open_covered_cell(g, nr, nc))
												{
													changed = 1;

													if (g.game_over)
													{
														return;
													}
												}
											}
										}
									}

									dc++;
								}
								dr++;
							}
						}
					}
				}

				c++;
			}

			r++;
		}

	} while (changed);
}
void ms_expand_from_zero(MSGame& g, const int r, const int c)
{
	int qr[MS_MAX_CELLS];
	int qc[MS_MAX_CELLS];
	int head;
	int tail;

	int cr;
	int cc;
	int k;
	int nr;
	int nc;

	const int dr8[8] = { -1,-1,-1, 0,0, 1,1,1 };
	const int dc8[8] = { -1, 0, 1,-1,1,-1,0,1 };

	head = 0;
	tail = 0;

	qr[tail] = r;
	qc[tail] = c;
	tail++;

	while (head < tail)
	{
		cr = qr[head];
		cc = qc[head];
		head++;

		k = 0;
		while (k < 8)
		{
			nr = cr + dr8[k];
			nc = cc + dc8[k];

			if (ms_in_bounds(g, nr, nc))
			{
				if (g.state[nr][nc] == MS_CELL_COVERED)
				{
					if (g.board[nr][nc] != MS_MINE)
					{
						g.state[nr][nc] = MS_CELL_OPENED;
						g.opened_count++;

						if (g.board[nr][nc] == 0)
						{
							qr[tail] = nr;
							qc[tail] = nc;
							tail++;
						}
					}
				}
			}

			k++;
		}
	}
}

/***************************************************************************
  函数名称：ms_open_cell
  功    能：打开一个格子（命中雷则 game_over）
***************************************************************************/
int ms_open_cell(MSGame& g, const int r, const int c)
{
	if (!ms_in_bounds(g, r, c))
	{
		return 0;
	}

	if (g.state[r][c] == MS_CELL_OPENED)
	{
		return 0;
	}

	if (g.state[r][c] == MS_CELL_FLAGGED)
	{
		return 0;
	}

	if (!g.first_open_done)
	{
		g.first_open_done = 1;
	}

	if (g.board[r][c] == MS_MINE)
	{
		g.state[r][c] = MS_CELL_OPENED;
		g.game_over = 1;
		g.win = 0;
		return 1;
	}

	g.state[r][c] = MS_CELL_OPENED;
	g.opened_count++;

	if (g.board[r][c] == 0)
	{
		ms_expand_from_zero(g, r, c);
		ms_auto_open_safe_by_flags(g);
	}

	return 1;
}

/***************************************************************************
  函数名称：ms_toggle_flag
***************************************************************************/
void ms_toggle_flag(MSGame& g, const int r, const int c)
{
	if (!ms_in_bounds(g, r, c))
	{
		return;
	}

	if (g.state[r][c] == MS_CELL_OPENED)
	{
		return;
	}

	if (g.state[r][c] == MS_CELL_COVERED)
	{
		g.state[r][c] = MS_CELL_FLAGGED;
		g.flag_count++;
		ms_auto_open_safe_by_flags(g);
		return;
	}

	if (g.state[r][c] == MS_CELL_FLAGGED)
	{
		g.state[r][c] = MS_CELL_COVERED;
		g.flag_count--;
		ms_auto_open_safe_by_flags(g);
		return;
	}
}

/***************************************************************************
  函数名称：ms_check_win
  功    能：打开所有非雷格则胜利
***************************************************************************/
int ms_check_win(MSGame& g)
{
	int need_open;

	need_open = g.rows * g.cols - g.mines;
	if (g.opened_count >= need_open)
	{
		g.win = 1;
		g.game_over = 1;
		return 1;
	}
	return 0;
}

/***************************************************************************
  函数名称：ms_row_label / ms_col_label
***************************************************************************/
char ms_row_label(const int r)
{
	return (char)('A' + r);
}

char ms_col_label(const int c, int i =0)
{
	if (c>=26)
	{
		if (i == 1)
		{
			return (char)('2');

		}
		else
		{
			return  (char)('6' + c - 26);
		}
	}
	else
	{
		if (c>=0&&c<=25)
		{
			if (i == 1)
			{
				return (char)('a' + c);
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

/***************************************************************************
  函数名称：ms_parse_rc
  功    能：解析 A1 / Gf（行必须大写）
***************************************************************************/
int ms_parse_rc(int rows, int cols, int& r, int& c)
{
	char rr;
	char cc;

	/* Row: must be uppercase A.. */
	while (1)
	{
		rr = (char)_getch();
		if (rr == 'Q' || rr == 'q')
		{
			return 0;
		}
		if (rr >= 'A' && rr <= (char)('A' + rows - 1))
		{
			r = rr - 'A';
			cout << rr;
			break;
		}
	}

	/* Col: 1-9, then a.. */
	while (1)
	{
		cc = (char)_getch();
		if (cc == 'Q' || cc == 'q')
		{
			return 0;
		}
		if (cc >= '1' && cc <= '9')
		{
			c = cc - '1';
			if (c < cols)
			{
				cout << cc;
				break;
			}
			continue;
		}
		if (cc >= 'a' && cc <= (char)('a' + cols - 10))
		{
			c = 9 + (cc - 'a');
			cout << cc;
			break;
		}
	}

	return 1;
}

/***************************************************************************
  函数名称：ms_cell_to_screen_xy
  功    能：格子(r,c) -> 显示坐标(x,y)（格子内容起始点）
***************************************************************************/
int ms_cell_to_screen_xy(const MSLayout& lay, const int r, const int c, int& x, int& y)
{
	if (r < 0 || c < 0)
	{
		return 0;
	}
	if (r >= lay.rows || c >= lay.cols)
	{
		return 0;
	}

	x = lay.x0 + 2 + 6 * c;
	y = lay.y0 + 1 + 3 * r;
	return 1;
}

/***************************************************************************
  函数名称：ms_mouse_to_cell
  功    能：鼠标坐标(mx,my) -> 格子(r,c)，返回1有效0无效
  说明：配合中文双线框架：每格宽6，高4（内容行在奇数 y）
***************************************************************************/
int ms_mouse_to_cell(const MSLayout& lay, const int mx, const int my, int& r, int& c)
{
	int dx;
	int dy;

	dx = mx - lay.x0;
	dy = my - lay.y0;

	if (dx < 0 || dy < 0)
	{
		return 0;
	}

	// 与 ms_graph_draw_frame() 对齐：
	if (dy > 3 * lay.rows)
	{
		return 0;
	}
	if (dx > 6 * lay.cols)
	{
		return 0;
	}

	// 落在网格线上判非法
	if ((dy % 3) == 0)
	{
		return 0;
	}
	if ((dx % 6) == 0)
	{
		return 0;
	}

	r = dy / 3;
	c = dx / 6;

	if (r < 0 || r >= lay.rows)
	{
		return 0;
	}
	if (c < 0 || c >= lay.cols)
	{
		return 0;
	}

	return 1;
}
