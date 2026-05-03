//2550703 卓03 李良玉
#pragma once

/* --- 如果有需要的头文件、命令空间，写于此处 --- */

/* --- 如果有需要的宏定义、只读全局变量等，写于此处 --- */

/* --- 如果有其它全局函数需要声明，写于此处 --- */

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date
{
private:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */

public:
	Date();
	Date(int y, int m, int d);
	Date(int days_from_1900);

	void set(int y, int m = 1, int d = 1);
	void get(int& y, int& m, int& d) const;
	void show() const;
};
