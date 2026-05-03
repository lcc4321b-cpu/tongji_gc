//25500703 卓03 李良玉
#include<iostream>
#include<iomanip>
using namespace std;


int main()
{
	int year, month, days, day;
	int week;
	while (1)
	{
		cout << "请输入年份(2000-2030)和月份(1-12) : ";
		cin >> year;
		if (cin.good()==1 && (year>=2000&&year<=2030))
		{
			cin >> month;
			if (cin.good() == 1 && (month >= 1 && month <= 12))
			{
				break;
			}
			else if (cin.good() == 0)
			{
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		else if(cin.good() == 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		cout << "输入非法，请重新输入"<<endl;
	}

	while (1)
	{
		cout << "请输入"<<year<<"年"<<month<<"月1日的星期(0-6表示星期日-星期六) : ";
		cin >> week ;
		if (cin.good() == 1 && (week >= 0 && week <= 6) )
		{
			break;
		}
		else if (cin.good() == 0)
		{
			cout << "输入非法，请重新输入" << endl;
			cin.clear();
			cin.ignore();
		}
		cout << "输入非法，请重新输入" << endl;
	}


	//print
	cout << year << "年" << month << "月的月历为:" << endl;
	cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六" << endl;
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		days = 31;
	}
	else if ( (month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		days = 30;
	}
	else
	{
		days = 28 + ((year % 4) == 0);
	}

	day = 1-week;
	while (day <= days)
	{
		if (day <= 0)
		{
			cout << "        ";
			day += 1;
			continue;
		}
		cout << "  " << setw(2) << day << "    ";
		day += 1;
		week += 1;
		if (week == 7)
		{
			cout << endl;
			week = 0;
		}
	}
	cout << endl;
	return 0;
}