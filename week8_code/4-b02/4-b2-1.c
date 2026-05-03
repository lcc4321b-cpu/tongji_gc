//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int zeller(int year, int month, int day)
{
	month = month + 12 * (month == 1 || month == 2);
	year = year - 1 * (month == 13 || month == 14);
	int answer;
	answer = year % 100 + (year % 100) / 4 + (year / 100) / 4 - 2 * (year / 100) + (13 * (month + 1)) / 5 + day - 1;
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
		printf("请输入年[1900-2100]、月、日：\n");
		if (scanf("%d", &year) == 1 && (year >= 1900 && year <= 2100))
		{
			if (scanf("%d", &month) == 1 && (month >= 1 && month <= 12))
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
				std_day = 30 + 1 * long_month - long_year * (month == 2);

				if (scanf("%d", &day) == 1 && (day >= 1 && day <= std_day))
				{
					finish = 0;
					break;
				}
				else
				{
					int ch;
					while ((ch = getchar()) != '\n' && ch != EOF) {}
				}

			}
			else
			{
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}
			}
		}
		else
		{
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {}
		}
		if (finish == 1)
		{
			printf("输入非法，请重新输入\n");
		}
	}

	switch (zeller(year, month, day))
	{
		case 0:
			printf("星期日\n");
			break;
		case 1:
			printf("星期一\n");
			break;
		case 2:
			printf("星期二\n");
			break;
		case 3:
			printf("星期三\n");
			break;
		case 4:
			printf("星期四\n");
			break;
		case 5:
			printf("星期五\n");
			break;
		case 6:
			printf("星期六\n");
			break;
	}
	return 0;
}
