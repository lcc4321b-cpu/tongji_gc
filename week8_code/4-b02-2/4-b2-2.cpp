//2550703 卓03 李良玉
#include<iostream>
#include <limits>
using namespace std;

int zeller(int year, int month, int day)
{
	month = month + 12 * (month == 1 || month == 2);
	year = year - 1*(month == 13 || month == 14);
	int answer;
	answer = year % 100 + (year % 100) / 4 + (year / 100) / 4 - 2 * (year / 100) + ( 13 * (month + 1) ) / 5 + day - 1;
	answer = ((answer % 7) + 7) % 7;
	return answer;
}

int main()
{
	int year, month, day;
	bool finish;
	finish = 1;
	while (finish)
	{
		cout << "请输入年[1900-2100]、月、日：" << endl;
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

				int std_day;
				std_day = 30 + 1 * long_month - long_year*(month==2);

				cin >> day;
				if (cin.good() == 1 && (day >= 1 && day <= std_day))
				{
					finish = 0;
					break;
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

	switch(zeller(year,month,day))
	{
		case 0:
			cout << "星期日" << endl;
			break;
		case 1:
			cout << "星期一" << endl;
			break;
		case 2:
			cout << "星期二" << endl;
			break;
		case 3:
			cout << "星期三" << endl;
			break;
		case 4:
			cout << "星期四" << endl;
			break;
		case 5:
			cout << "星期五" << endl;
			break;
		case 6:
			cout << "星期六" << endl;
			break;
	}
	return 0;
}