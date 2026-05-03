// 25500703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int year, month, days, day;
    int week;
    int good;  

    while (1)
    {
        printf("请输入年份(2000-2030)和月份(1-12) : ");
        int rc = scanf("%d", &year);     
        good = (rc == 1);
        if (good == 1 && (year >= 2000 && year <= 2030))
        {
            rc = scanf("%d", &month);  
            good = (rc == 1);
            if (good == 1 && (month >= 1 && month <= 12))
            {
                break;
            }
            else if (good == 0)
            {

                clearerr(stdin);
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) 
                {

                }
            }
        }
        else if (good == 0)
        {
            clearerr(stdin);
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {

            }
        }
        printf("输入非法，请重新输入\n");
    }

    while (1)
    {
        printf("请输入%d年%d月1日的星期(0-6表示星期日-星期六) : ", year, month);
        int rc = scanf("%d", &week);   
        good = (rc == 1);
        if (good == 1 && (week >= 0 && week <= 6))
        {
            break;
        }
        else if (good == 0)
        {
            printf("输入非法，请重新输入\n");
            clearerr(stdin);
            int ch = getchar(); 
        }
        printf("输入非法，请重新输入\n");
    }

    // print
    printf("%d年%d月的月历为:\n", year, month);
    printf("星期日  星期一  星期二  星期三  星期四  星期五  星期六\n");

    if ((month == 1) || (month == 3) || (month == 5) || (month == 7) ||
        (month == 8) || (month == 10) || (month == 12))
    {
        days = 31;
    }
    else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
    {
        days = 30;
    }
    else
    {
        days = 28 + ((year % 4) == 0);  
    }

    day = 1 - week;
    int now_week = 0;
    while (day <= days)
    {
        if (day <= 0)
        {
            printf("        ");   // 8 个空格
            day += 1;
            now_week += 1;
            continue;
        }
        printf("  %2d    ", day); 
        week += 1;
        now_week += 1;
        day += 1;
        if (now_week == 7)
        {
            printf("\n");
            now_week = 0;
        }
    }
    printf("\n");
    return 0;
}
