//2550703 卓03 李良玉
#include <iostream>
#include <conio.h>
#include "7-b6.h"
using namespace std;

static int is_leap_year(int y)
{
	if ((y % 400) == 0)
	{
		return 1;
	}
	if ((y % 100) == 0)
	{
		return 0;
	}
	if ((y % 4) == 0)
	{
		return 1;
	}
	return 0;
}

static int days_in_month(int y, int m)
{
	int dm = 31;

	switch (m)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		dm = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		dm = 30;
		break;
	case 2:
		dm = 28;
		if (is_leap_year(y))
		{
			dm = 29;
		}
		break;
	default:
		dm = 31;
		break;
	}

	return dm;
}

static int normalize_year_value(int y)
{
	if (y < 1900)
	{
		return 2000;
	}
	if (y > 2099)
	{
		return 2000;
	}
	return y;
}

static int normalize_month_value(int m)
{
	if (m < 1)
	{
		return 1;
	}
	if (m > 12)
	{
		return 1;
	}
	return m;
}

static int normalize_day_value(int y, int m, int d)
{
	int dm;

	dm = days_in_month(y, m);
	if (d < 1)
	{
		return 1;
	}
	if (d > dm)
	{
		return 1;
	}
	return d;
}

static void day_index_to_ymd(int day_index, int& y, int& m, int& d)
{
	int offset;
	int diy;
	int dim;

	y = 1900;
	m = 1;
	d = 1;

	offset = day_index - 1;

	while (1)
	{
		diy = 365;
		if (is_leap_year(y))
		{
			diy = 366;
		}

		if (offset >= diy)
		{
			offset -= diy;
			++y;
		}
		else
		{
			break;
		}
	}

	while (1)
	{
		dim = days_in_month(y, m);
		if (offset >= dim)
		{
			offset -= dim;
			++m;
		}
		else
		{
			break;
		}
	}

	d = offset + 1;
}

/* 给出 Date 类的所有成员函数的体外实现 */
/***************************************************************************
  函数名称：Date::Date
  功    能：无参构造，默认为2000.1.1
  输入参数：无
  返 回 值：无
  说    明：
***************************************************************************/
Date::Date()
{
	year = 2000;
	month = 1;
	day = 1;
}

/***************************************************************************
  函数名称：Date::Date
  功    能：三参构造（按年->月->日顺序处理非法：年非法->2000；月非法->1；日非法->1）
  输入参数：y,m,d
  返 回 值：无
  说    明：
***************************************************************************/
Date::Date(int y, int m, int d)
{
	int ny;
	int nm;
	int nd;

	ny = normalize_year_value(y);
	nm = normalize_month_value(m);
	nd = normalize_day_value(ny, nm, d);

	year = ny;
	month = nm;
	day = nd;
}

/***************************************************************************
  函数名称：Date::Date
  功    能：一参构造，参数表示从1900.1.1开始的天数（1->1900.1.1），越界则夹到边界
  输入参数：days_from_1900
  返 回 值：无
  说    明：合法范围[1, 73049]，对应[1900.1.1, 2099.12.31]
***************************************************************************/
Date::Date(int days_from_1900)
{
	int idx;

	idx = days_from_1900;
	if (idx < 1)
	{
		idx = 1;
	}
	if (idx > 73049)
	{
		idx = 73049;
	}

	day_index_to_ymd(idx, year, month, day);
}

/***************************************************************************
  函数名称：Date::set
  功    能：设置日期，m/d缺省为1；y/m/d为0表示该项不变；非法按年->月->日顺序处理
  输入参数：y,m,d
  返 回 值：无
  说    明：如果day为0表示保持原day，但若因年/月变化导致day非法，则置为1
***************************************************************************/
void Date::set(int y, int m, int d)
{
	int ny;
	int nm;
	int nd;
	int keep_day;

	ny = year;
	nm = month;
	nd = day;

	if (y != 0)
	{
		ny = normalize_year_value(y);
	}

	if (m != 0)
	{
		nm = normalize_month_value(m);
	}

	keep_day = 0;
	if (d == 0)
	{
		keep_day = 1;
	}
	else
	{
		nd = d;
	}

	if (!keep_day)
	{
		nd = normalize_day_value(ny, nm, nd);
	}
	else
	{
		nd = normalize_day_value(ny, nm, nd);
	}

	year = ny;
	month = nm;
	day = nd;
}

/***************************************************************************
  函数名称：Date::get
  功    能：获取年月日
  输入参数：引用y,m,d
  返 回 值：无
  说    明：
***************************************************************************/
void Date::get(int& y, int& m, int& d) const
{
	y = year;
	m = month;
	d = day;
}

/***************************************************************************
  函数名称：Date::show
  功    能：按“year.month.day”输出并换行
  输入参数：无
  返 回 值：无
  说    明：不补0
***************************************************************************/
void Date::show() const
{
	cout << year << "." << month << "." << day << endl;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
