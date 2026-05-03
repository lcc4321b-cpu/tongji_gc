//2550703 卓03 李良玉
#pragma once

#include <cmath>
class point
{
private:
	int x;
	int y;
public:
	int getx() const //函数声明后加const，表示不允许在本函数中修改数据成员的值 
	{
		return x;
	}
	int gety() const //函数声明后加const，表示不允许在本函数中修改数据成员的值
	{
		return y;
	}

	void set(int px, int py)
	{
		x = px;
		y = py;
	}

};

class triangle
{
private:
	point p1;
	point p2;
	point p3;
public:
	double area()
	{
		double v;
		double s;

		v = (double)p1.getx() * (double)(p2.gety() - p3.gety());
		v += (double)p2.getx() * (double)(p3.gety() - p1.gety());
		v += (double)p3.getx() * (double)(p1.gety() - p2.gety());

		s = std::fabs(v) / 2.0;

		if (s <= 0.0)
		{
			return -1;
		}
		return s;
	}

	/* 构造函数（已实现，不准动） */
	triangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y)
	{
		/* 给p1/p2/p3三个点分别赋x,y坐标值 */
		p1.set(p1_x, p1_y);
		p2.set(p2_x, p2_y);
		p3.set(p3_x, p3_y);
	}
	/* 可以定义需要的成员函数，数量不限，并以体内方式实现，不允许添加数据成员 */
};
