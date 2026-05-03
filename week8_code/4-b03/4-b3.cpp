//2550703 卓03 李良玉
#include<iostream>
#include<iomanip>
#include <limits>
using namespace std;


int zeller(int year, int month, int day)
{
	month = month + 12 * (month == 1 || month == 2);
	year = year - 1 * (month == 13 || month == 14);
	int answer;
	answer = year % 100 + (year % 100) / 4 + (year / 100) / 4 - 2 * (year / 100) + (13 * (month + 1)) / 5 + day - 1;
	answer = ((answer % 7) + 7) % 7;
	return answer;
}

int calendar(int year, int month, int week, int std_day)
{
	int day_now;
	cout << endl;
	cout << year << "年" << month << "月" << endl;
	cout << "======================================================" << endl;
	cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六" << endl;
	cout << "======================================================" << endl;
	day_now = 1 - week;
	while (day_now <= std_day)
	{
		if (day_now <= 0)
		{
			cout << "        ";
			day_now += 1;
			continue;
		}
		cout << "  " << setw(2) << day_now << "    ";
		day_now += 1;
		week += 1;
		if (week == 7)
		{
			cout << endl;
			week = 0;
		}
	}
	if (week != 0)
	{
		cout << endl;
	}
	cout << "======================================================" << endl;
	return 0;
}

int main()
{
	int year, month, std_day;
	bool finish;
	finish = 1;
	while (finish)
	{
		cout << "请输入年[1900-2100]、月" << endl;
		cin >> year;
		if (cin.good() == 1 && (year >= 1900 && year <= 2100))
		{
			cin >> month;
			if (cin.good() == 1 && (month >= 1 && month <= 12))
			{
				bool long_year;
				//1=short
				//0=long
				long_year = !(((year % 4 == 0) && (year % 100 != 0)) || (year % 400) == 0);
				int long_month;
				//1=31
				//0=30
				//-1=28/29
				long_month = (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) - (month == 2);

				std_day = 30 + 1 * long_month - long_year * (month == 2);

				finish = 0;
			}
			else if (cin.good() == 0)
			{
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		else if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		if (finish == 1)
		{
			cout << "输入非法，请重新输入" << endl;
		}
	}

	calendar(year, month, zeller(year, month, 1), std_day);

	return 0;
}