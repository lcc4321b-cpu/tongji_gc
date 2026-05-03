//2550703 卓03 李良玉
#include "7-b2.h"
#include "cmd_console_tools.h"
#include <cstdio>
#include <cstring>

static int is_gb2312_first_byte(unsigned char ch)
{
	if (ch >= 0xA1 && ch <= 0xFE)
	{
		return 1;
	}
	return 0;
}

static int calc_disp_cols_gb2312(const char* s)
{
	int cols;
	const unsigned char* p;

	cols = 0;
	p = (const unsigned char*)s;

	while (*p != 0)
	{
		if (is_gb2312_first_byte(*p) != 0)
		{
			if (*(p + 1) != 0)
			{
				cols += 2;
				p += 2;
			}
			else
			{
				cols += 1;
				p += 1;
			}
		}
		else
		{
			cols += 1;
			p += 1;
		}
	}

	return cols;
}

static void fit_text_gb2312(const char* src, int width_cols, char* out, int out_cap)
{
	int col;
	const unsigned char* p;

	if (out_cap <= 0)
	{
		return;
	}

	if (width_cols < 0)
	{
		width_cols = 0;
	}

	if (width_cols >= out_cap)
	{
		width_cols = out_cap - 1;
	}

	col = 0;
	p = (const unsigned char*)src;

	while (col < width_cols)
	{
		if (*p == 0)
		{
			break;
		}

		if (is_gb2312_first_byte(*p) != 0)
		{
			if (col + 1 >= width_cols)
			{
				break;
			}

			if (*(p + 1) == 0)
			{
				break;
			}

			out[col] = (char)p[0];
			out[col + 1] = (char)p[1];
			col += 2;
			p += 2;
		}
		else
		{
			out[col] = (char)p[0];
			col += 1;
			p += 1;
		}
	}

	while (col < width_cols)
	{
		out[col] = ' ';
		col += 1;
	}

	out[width_cols] = '\0';
}

static int safe_take_gb2312(const char* s, int max_cols)
{
	int i;
	const unsigned char* p;

	i = 0;
	p = (const unsigned char*)s;

	while (i < max_cols)
	{
		if (p[i] == 0)
		{
			break;
		}

		if (is_gb2312_first_byte(p[i]) != 0)
		{
			if (p[i + 1] == 0)
			{
				break;
			}

			if (is_gb2312_first_byte(p[i + 1]) != 0)
			{
				if (i + 2 > max_cols)
				{
					break;
				}

				i += 2;
			}
			else
			{
				i += 1;
			}
		}
		else
		{
			i += 1;
		}
	}

	return i;
}

static void copy_no_pad_gb2312(const char* src, int max_cols, char* out, int out_cap, int* taken_cols)
{
	int take;

	if (taken_cols != NULL)
	{
		*taken_cols = 0;
	}

	if (out_cap <= 0)
	{
		return;
	}

	if (max_cols < 0)
	{
		max_cols = 0;
	}

	take = safe_take_gb2312(src, max_cols);

	if (take > out_cap - 1)
	{
		take = out_cap - 1;
	}

	if (take > 0)
	{
		memcpy(out, src, (size_t)take);
	}

	out[take] = '\0';

	if (taken_cols != NULL)
	{
		*taken_cols = take;
	}
}

static int calc_wrap_lines(const char* row, int row_cols, int start_x, int buffer_cols)
{
	int off;
	int line;
	int cap;
	int take;

	off = 0;
	line = 0;

	while (off < row_cols)
	{
		if (line == 0)
		{
			cap = buffer_cols - start_x;
		}
		else
		{
			cap = buffer_cols;
		}

		if (cap < 0)
		{
			cap = 0;
		}

		/* 关键：强制偶数列，彻底消灭“半个汉字 + 多一个空格” */
		if (cap % 2 != 0)
		{
			cap -= 1;
		}

		if (cap <= 0)
		{
			/* 没空间就至少推进一行，避免死循环 */
			line += 1;
			continue;
		}

		take = safe_take_gb2312(row + off, cap);

		if (take <= 0)
		{
			/* 理论上不会发生（cap 是偶数），兜底推进 */
			take = 1;
			if (take > cap)
			{
				take = cap;
			}
		}

		off += take;
		line += 1;
	}

	if (line <= 0)
	{
		line = 1;
	}

	return line;
}

static int draw_row_wrapped_full(
	const struct PopMenu* para,
	int base_x,
	int base_y,
	const char* row,
	int row_cols,
	int bg,
	int fg
)
{
	int win_cols;
	int win_lines;
	int buffer_cols;
	int buffer_lines;

	int off;
	int line;
	int cap;
	int take;

	char buf[4096];

	cct_getconsoleborder(win_cols, win_lines, buffer_cols, buffer_lines);
	(void)win_cols;
	(void)win_lines;
	(void)buffer_lines;

	off = 0;
	line = 0;

	while (off < row_cols)
	{
		int x;
		int y;

		if (line == 0)
		{
			cap = buffer_cols - base_x;
			x = base_x;
		}
		else
		{
			cap = buffer_cols;
			x = 0;
		}

		if (cap < 0)
		{
			cap = 0;
		}

		if (cap % 2 != 0)
		{
			cap -= 1;
		}

		if (cap <= 0)
		{
			line += 1;
			continue;
		}

		copy_no_pad_gb2312(row + off, cap, buf, (int)sizeof(buf), &take);

		y = base_y + line;

		if (take > 0)
		{
			cct_showstr(x, y, buf, bg, fg, 1, take);
		}

		/* 清尾，避免滚屏/重绘残留导致“显示不乱”不满足 */
		if (take < cap)
		{
			cct_showstr(x + take, y, "", bg, fg, 1, cap - take);
		}

		off += take;
		line += 1;
	}

	return line;
}

static void draw_row_wrapped_slice(
	const struct PopMenu* para,
	int base_x,
	int base_y,
	const char* row,
	int row_cols,
	int slice_start,
	int slice_cols,
	int bg,
	int fg
)
{
	int win_cols;
	int win_lines;
	int buffer_cols;
	int buffer_lines;

	int off;
	int line;
	int cap;
	int take;

	int seg_start;
	int seg_end;

	cct_getconsoleborder(win_cols, win_lines, buffer_cols, buffer_lines);
	(void)win_cols;
	(void)win_lines;
	(void)buffer_lines;

	off = 0;
	line = 0;
	seg_start = 0;

	while (off < row_cols)
	{
		int x;
		int y;

		if (line == 0)
		{
			cap = buffer_cols - base_x;
			x = base_x;
		}
		else
		{
			cap = buffer_cols;
			x = 0;
		}

		if (cap < 0)
		{
			cap = 0;
		}

		if (cap % 2 != 0)
		{
			cap -= 1;
		}

		if (cap <= 0)
		{
			line += 1;
			continue;
		}

		take = safe_take_gb2312(row + off, cap);
		if (take <= 0)
		{
			take = 1;
			if (take > cap)
			{
				take = cap;
			}
		}

		seg_end = seg_start + take;

		/* slice 与本段交集 */
		{
			int inter_s;
			int inter_e;

			inter_s = slice_start;
			if (inter_s < seg_start)
			{
				inter_s = seg_start;
			}

			inter_e = slice_start + slice_cols;
			if (inter_e > seg_end)
			{
				inter_e = seg_end;
			}

			if (inter_e > inter_s)
			{
				int within;
				int need;
				char buf[4096];

				within = inter_s - seg_start;
				need = inter_e - inter_s;

				copy_no_pad_gb2312(row + inter_s, need, buf, (int)sizeof(buf), NULL);

				y = base_y + line;
				cct_showstr(x + within, y, buf, bg, fg, 1, need);
			}
		}

		off += take;
		seg_start = seg_end;
		line += 1;
	}
}

static void append_bytes(char* out, int cap, int* k, const char* s)
{
	int i;

	i = 0;

	while (s[i] != '\0')
	{
		if (*k >= cap - 1)
		{
			break;
		}

		out[*k] = s[i];
		*k += 1;
		i += 1;
	}

	out[*k] = '\0';
}

static void append_repeat(char* out, int cap, int* k, const char* gb2, int repeat)
{
	int i;

	i = 0;
	while (i < repeat)
	{
		append_bytes(out, cap, k, gb2);
		i += 1;
	}
}

static void build_top_row_with_title(const struct PopMenu* para, int width_cols, char* out, int cap, int* out_cols)
{
	int k;
	int left_pad;
	int title_cols;
	int title_cols_padded;

	char tbuf[512];
	char showbuf[2048];

	k = 0;
	out[0] = '\0';

	append_bytes(out, cap, &k, "┏");
	append_repeat(out, cap, &k, "━", width_cols / 2);
	append_bytes(out, cap, &k, "┓");

	if (para->title != NULL)
	{
		if (para->title[0] != '\0')
		{
			build_title_spaced(para->title, tbuf, (int)sizeof(tbuf));

			title_cols = calc_disp_cols_gb2312(tbuf);
			title_cols_padded = title_cols;

			if (title_cols_padded % 2 != 0)
			{
				title_cols_padded += 1;
			}

			if (title_cols_padded > width_cols)
			{
				title_cols_padded = width_cols;
			}

			if (title_cols_padded > 0)
			{
				fit_text_gb2312(tbuf, title_cols_padded, showbuf, (int)sizeof(showbuf));

				left_pad = (width_cols - title_cols_padded) / 2;

				if (left_pad < 0)
				{
					left_pad = 0;
				}

				if (left_pad % 2 != 0)
				{
					left_pad -= 1;
					if (left_pad < 0)
					{
						left_pad = 0;
					}
				}

				/* 2 列起始是左角“┏”占 2 列 */
				if (2 + left_pad + title_cols_padded <= k)
				{
					memcpy(out + 2 + left_pad, showbuf, (size_t)title_cols_padded);
				}
			}
		}
	}

	if (out_cols != NULL)
	{
		*out_cols = k;
	}
}

static void build_bottom_row(int width_cols, char* out, int cap, int* out_cols)
{
	int k;

	k = 0;
	out[0] = '\0';

	append_bytes(out, cap, &k, "┗");
	append_repeat(out, cap, &k, "━", width_cols / 2);
	append_bytes(out, cap, &k, "┛");

	if (out_cols != NULL)
	{
		*out_cols = k;
	}
}

static void build_item_row(int width_cols, const char* item_buf, char* out, int cap, int* out_cols)
{
	int k;

	k = 0;
	out[0] = '\0';

	append_bytes(out, cap, &k, "┃");

	if (k + width_cols < cap - 1)
	{
		memcpy(out + k, item_buf, (size_t)width_cols);
		k += width_cols;
		out[k] = '\0';
	}

	append_bytes(out, cap, &k, "┃");

	if (out_cols != NULL)
	{
		*out_cols = k;
	}
}


static int count_menu_items(const char menu[][MAX_ITEM_LEN])
{
	int n;

	n = 0;
	while (menu[n][0] != '\0')
	{
		n += 1;
	}

	return n;
}

static void build_title_spaced(const char* title, char* out, int cap)
{
	int i;
	int k;

	if (cap <= 0)
	{
		return;
	}

	out[0] = '\0';

	if (title == NULL)
	{
		return;
	}

	k = 0;

	if (k < cap - 1)
	{
		out[k] = ' ';
		k += 1;
	}

	i = 0;
	while (title[i] != '\0' && k < cap - 2)
	{
		out[k] = title[i];
		k += 1;
		i += 1;
	}

	if (k < cap - 1)
	{
		out[k] = ' ';
		k += 1;
	}

	out[k] = '\0';
}

static void draw_top_bottom_line(const struct PopMenu* para, int y, int width_cols, int is_top)
{
	int xL;
	int xH;
	int xR;

	xL = para->start_x;
	xH = para->start_x + 2;
	xR = para->start_x + 2 + width_cols;

	if (is_top != 0)
	{
		cct_showstr(xL, y, "┏", para->bg_color, para->fg_color, 1, 2);
		cct_showstr(xH, y, "━", para->bg_color, para->fg_color, width_cols / 2, width_cols);
		cct_showstr(xR, y, "┓", para->bg_color, para->fg_color, 1, 2);
	}
	else
	{
		cct_showstr(xL, y, "┗", para->bg_color, para->fg_color, 1, 2);
		cct_showstr(xH, y, "━", para->bg_color, para->fg_color, width_cols / 2, width_cols);
		cct_showstr(xR, y, "┛", para->bg_color, para->fg_color, 1, 2);
	}
}

static void draw_title_on_top(const struct PopMenu* para, int width_cols)
{
	char tbuf[512];
	char showbuf[2048];

	int title_cols;
	int title_cols_padded;
	int left_pad;
	int xT;

	if (para->title == NULL)
	{
		return;
	}

	if (para->title[0] == '\0')
	{
		return;
	}

	build_title_spaced(para->title, tbuf, (int)sizeof(tbuf));

	title_cols = calc_disp_cols_gb2312(tbuf);
	title_cols_padded = title_cols;

	if (title_cols_padded % 2 != 0)
	{
		title_cols_padded += 1;
	}

	if (title_cols_padded > width_cols)
	{
		title_cols_padded = width_cols;
	}

	if (title_cols_padded <= 0)
	{
		return;
	}

	fit_text_gb2312(tbuf, title_cols_padded, showbuf, (int)sizeof(showbuf));

	left_pad = (width_cols - title_cols_padded) / 2;

	if (left_pad < 0)
	{
		left_pad = 0;
	}

	/* 保证2列对齐，避免单字节H/S贴线 */
	if (left_pad % 2 != 0)
	{
		left_pad -= 1;
		if (left_pad < 0)
		{
			left_pad = 0;
		}
	}

	xT = para->start_x + 2 + left_pad;
	cct_showstr(xT, para->start_y, showbuf, para->bg_color, para->fg_color, 1, title_cols_padded);
}

static void draw_one_item_row(
	const char menu[][MAX_ITEM_LEN],
	const struct PopMenu* para,
	int y,
	int width_cols,
	int item_count,
	int item_index,
	int is_selected
)
{
	int xL;
	int xC;
	int xR;

	char item_buf[2048];

	xL = para->start_x;
	xC = para->start_x + 2;
	xR = para->start_x + 2 + width_cols;

	cct_showstr(xL, y, "┃", para->bg_color, para->fg_color, 1, 2);

	if (item_index >= 0 && item_index < item_count)
	{
		fit_text_gb2312(menu[item_index], width_cols, item_buf, (int)sizeof(item_buf));
	}
	else
	{
		fit_text_gb2312("", width_cols, item_buf, (int)sizeof(item_buf));
	}

	if (is_selected != 0)
	{
		cct_showstr(xC, y, item_buf, para->fg_color, para->bg_color, 1, width_cols);
	}
	else
	{
		cct_showstr(xC, y, item_buf, para->bg_color, para->fg_color, 1, width_cols);
	}

	cct_showstr(xR, y, "┃", para->bg_color, para->fg_color, 1, 2);
}
static int draw_menu_all_wrapped(
	const char menu[][MAX_ITEM_LEN],
	const struct PopMenu* para,
	int width_cols,
	int show_high,
	int item_count,
	int top_index,
	int cur_index,
	int buffer_cols
)
{
	int y;
	int r;

	char row[4096];
	int row_cols;

	char item_buf[2048];

	y = para->start_y;

	build_top_row_with_title(para, width_cols, row, (int)sizeof(row), &row_cols);
	y += draw_row_wrapped_full(para, para->start_x, y, row, row_cols, para->bg_color, para->fg_color);

	r = 0;
	while (r < show_high)
	{
		int idx;
		int is_sel;

		idx = top_index + r;
		is_sel = 0;

		if (idx == cur_index)
		{
			is_sel = 1;
		}

		if (idx >= 0 && idx < item_count)
		{
			fit_text_gb2312(menu[idx], width_cols, item_buf, (int)sizeof(item_buf));
		}
		else
		{
			fit_text_gb2312("", width_cols, item_buf, (int)sizeof(item_buf));
		}

		build_item_row(width_cols, item_buf, row, (int)sizeof(row), &row_cols);

		/* 先整行正常画 */
		y += draw_row_wrapped_full(para, para->start_x, y, row, row_cols, para->bg_color, para->fg_color);

		/* 再覆盖高亮内容区：从第 2 列开始，长度 width_cols */
		if (is_sel != 0)
		{
			draw_row_wrapped_slice(
				para,
				para->start_x,
				y - calc_wrap_lines(row, row_cols, para->start_x, buffer_cols),
				row,
				row_cols,
				2,
				width_cols,
				para->fg_color,
				para->bg_color
			);
		}

		r += 1;
	}

	build_bottom_row(width_cols, row, (int)sizeof(row), &row_cols);
	y += draw_row_wrapped_full(para, para->start_x, y, row, row_cols, para->bg_color, para->fg_color);

	return y - para->start_y;
}

static void draw_menu_all(
	const char menu[][MAX_ITEM_LEN],
	const struct PopMenu* para,
	int width_cols,
	int show_high,
	int item_count,
	int top_index,
	int cur_index,
	int wrap_mode,
	int buffer_cols
)
{
	if (wrap_mode != 0)
	{
		draw_menu_all_wrapped(menu, para, width_cols, show_high, item_count, top_index, cur_index, buffer_cols);
		return;
	}

	/* ===== 原来的正常绘制逻辑（不折返） ===== */
	{
		int r;
		int y_bottom;

		draw_top_bottom_line(para, para->start_y, width_cols, 1);
		draw_title_on_top(para, width_cols);

		r = 0;
		while (r < show_high)
		{
			draw_one_item_row(
				menu,
				para,
				para->start_y + 1 + r,
				width_cols,
				item_count,
				top_index + r,
				(top_index + r == cur_index) ? 1 : 0
			);
			r += 1;
		}

		y_bottom = para->start_y + 1 + show_high;
		draw_top_bottom_line(para, y_bottom, width_cols, 0);
	}
}

int pop_menu(const char menu[][MAX_ITEM_LEN], const struct PopMenu* original_para)
{
	struct PopMenu para;

	int item_count;
	int width_cols;
	int show_high;

	int win_cols;
	int win_lines;
	int buffer_cols;
	int buffer_lines;

	int total_cols;

	int cur_index;
	int top_index;

	int keycode1;
	int keycode2;
	int m_action;
	int mx;
	int my;
	int event_type;

	int need_redraw;
	int done;
	int ret;

	if (menu == NULL)
	{
		return 0;
	}

	if (original_para == NULL)
	{
		return 0;
	}

	para = *original_para;

	if (para.start_x < 0)
	{
		para.start_x = 0;
	}

	if (para.start_y < 0)
	{
		para.start_y = 0;
	}

	if (para.start_x % 2 != 0)
	{
		if (para.start_x > 0)
		{
			para.start_x -= 1;
		}
	}

	if (para.width < 2)
	{
		para.width = 2;
	}

	if (para.width % 2 != 0)
	{
		para.width += 1;
	}

	if (para.high < 0)
	{
		para.high = 0;
	}

	item_count = count_menu_items(menu);

	/* 高度调整：空菜单 show_high=0（只画上下边框），否则按para.high并不超过item_count */
	if (item_count <= 0)
	{
		show_high = 0;
		cur_index = -1;
	}
	else
	{
		if (para.high <= 0)
		{
			show_high = 1;
		}
		else
		{
			show_high = para.high;
		}

		if (show_high > item_count)
		{
			show_high = item_count;
		}

		cur_index = 0;
	}

	top_index = 0;

	/* 宽度至少覆盖标题(含两侧空格)，且保持偶数 */
	width_cols = para.width;
	{
		char tbuf[512];
		int tcols;

		tcols = 0;

		if (para.title != NULL && para.title[0] != '\0')
		{
			build_title_spaced(para.title, tbuf, (int)sizeof(tbuf));
			tcols = calc_disp_cols_gb2312(tbuf);
			if (tcols % 2 != 0)
			{
				tcols += 1;
			}
		}

		if (width_cols < tcols)
		{
			width_cols = tcols;
		}

		if (width_cols % 2 != 0)
		{
			width_cols += 1;
		}
	}

	/* 测试8关键：如果当前行剩余宽度不够，整体“搬到下一行起始位置(0列)” */
	cct_getconsoleborder(win_cols, win_lines, buffer_cols, buffer_lines);
	(void)win_cols;
	(void)win_lines;
	(void)buffer_lines;

	total_cols = width_cols + 4;

	int wrap_mode;

	wrap_mode = 0;

	if (buffer_cols > 0)
	{
		if (para.start_x + total_cols > buffer_cols)
		{
			wrap_mode = 1;
		}
	}



	ret = 0;
	done = 0;
	need_redraw = 1;

	cct_enable_mouse();

	while (done == 0)
	{
		if (need_redraw != 0)
		{
			draw_menu_all(menu, &para, width_cols, show_high, item_count, top_index, cur_index, wrap_mode, buffer_cols);
			fflush(stdout);
			need_redraw = 0;
		}

		event_type = cct_read_keyboard_and_mouse(mx, my, m_action, keycode1, keycode2);

		if (event_type == CCT_KEYBOARD_EVENT)
		{
			if (keycode1 == 27)
			{
				ret = 0;
				done = 1;
			}
			else if (keycode1 == 13)
			{
				if (cur_index >= 0 && cur_index < item_count)
				{
					ret = cur_index + 1;
				}
				else
				{
					ret = 0;
				}
				done = 1;
			}
			else if (keycode1 == 0xE0)
			{
				if (item_count > 0)
				{
					if (keycode2 == KB_ARROW_UP)
					{
						cur_index -= 1;
						if (cur_index < 0)
						{
							cur_index = item_count - 1;
						}
						need_redraw = 1;
					}
					else if (keycode2 == KB_ARROW_DOWN)
					{
						cur_index += 1;
						if (cur_index >= item_count)
						{
							cur_index = 0;
						}
						need_redraw = 1;
					}
				}
			}
		}
		else if (event_type == CCT_MOUSE_EVENT)
		{
			if (m_action == MOUSE_RIGHT_BUTTON_CLICK || m_action == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK)
			{
				ret = 0;
				done = 1;
			}
			else if (m_action == MOUSE_WHEEL_MOVED_UP)
			{
				if (item_count > 0)
				{
					cur_index -= 1;
					if (cur_index < 0)
					{
						cur_index = item_count - 1;
					}
					need_redraw = 1;
				}
			}
			else if (m_action == MOUSE_WHEEL_MOVED_DOWN)
			{
				if (item_count > 0)
				{
					cur_index += 1;
					if (cur_index >= item_count)
					{
						cur_index = 0;
					}
					need_redraw = 1;
				}
			}
			else
			{
				int box_y_items;
				int idx_in_view;
				int new_index;

				box_y_items = para.start_y + 1;

				if (show_high > 0)
				{
					if (my >= box_y_items && my < box_y_items + show_high)
					{
						idx_in_view = my - box_y_items;
						new_index = top_index + idx_in_view;

						if (new_index >= 0 && new_index < item_count)
						{
							if (new_index != cur_index)
							{
								cur_index = new_index;
								need_redraw = 1;
							}

							if (m_action == MOUSE_LEFT_BUTTON_CLICK || m_action == MOUSE_LEFT_BUTTON_DOUBLE_CLICK)
							{
								ret = cur_index + 1;
								done = 1;
							}
						}
					}
				}
			}
		}

		if (done == 0 && item_count > 0 && show_high > 0)
		{
			int new_top;

			new_top = top_index;

			if (cur_index < new_top)
			{
				new_top = cur_index;
			}

			if (cur_index >= new_top + show_high)
			{
				new_top = cur_index - show_high + 1;
			}

			if (new_top < 0)
			{
				new_top = 0;
			}

			if (new_top > item_count - show_high)
			{
				new_top = item_count - show_high;
			}

			if (new_top != top_index)
			{
				top_index = new_top;
				need_redraw = 1;
			}
		}
	}

	cct_disable_mouse();

	return ret;
}
