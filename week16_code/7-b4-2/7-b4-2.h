//2550703 卓03 李良玉
#pragma once

#include <cmath>
class triangle;  //类的提前声明，思考一下，放在这里的目的是为什么

/* point类的定义及实现，已给出部分内容，按要求补充完成 */
class point
{
private:
	int x;
	int y;

	friend class triangle;

public:
	/* 仅允许在此添加一个成员函数【仅限1个】,要求体内实现 */
	void set(int px, int py)
	{
		x = px;
		y = py;
	}

	/* 除上面允许的那个成员函数外，不再允许添加任何的数据成员和成员函数，但可以根据需要添加其它内容 */
};

/* triangle类的定义及实现，已给出部分内容，按要求补充完成 */
class triangle
{
private:
	point p1;
	point p2;
	point p3;
	//除上面的三个private数据成员外，不再允许添加任何类型的数据成员
public:
	/* 构造函数（已实现，不准动） */
	triangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y)
	{
		/* 给p1/p2/p3三个点分别赋x,y坐标值 */
		p1.set(p1_x, p1_y);
		p2.set(p2_x, p2_y);
		p3.set(p3_x, p3_y);
	}

	/* 根据需要补充相应的语句后完成area函数(形参为空，不准改)，
	   要求：如果三点能构成三角形，则返回面积，否则返回 -1 */
	double area()
	{
		double v;
		double s;

		v = (double)p1.x * (double)(p2.y - p3.y);
		v += (double)p2.x * (double)(p3.y - p1.y);
		v += (double)p3.x * (double)(p1.y - p2.y);

		s = std::fabs(v) / 2.0;

		if (s <= 0.0)
		{
			return -1;
		}
		return s;
	}

	/* 可以定义需要的成员函数，数量不限，并以体内方式实现，不允许添加数据成员 */
};
