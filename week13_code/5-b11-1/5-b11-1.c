//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖";
char result[256];

/* 清空 result */
void clear_result(void)
{
    result[0] = '\0';
}

/* 追加一个大写数字（0~9），需要零则 flag_zero 传 1，否则传 0 */
void append_digit(int num, int flag_zero)
{
    const int bytes_per = 2;
    int len = (int)strlen(result);

    if (num == 0)
    {
        if (!flag_zero)
        {
            return;
        }
        for (int i = 0; i < bytes_per; ++i)
        {
            result[len + i] = chnstr[i];
        }
        result[len + bytes_per] = '\0';
    }
    else
    {
        if (num < 0 || num > 9)
        {
            return;
        }
        int start = num * bytes_per;
        for (int i = 0; i < bytes_per; ++i)
        {
            result[len + i] = chnstr[start + i];
        }
        result[len + bytes_per] = '\0';
    }
}

/* 追加一个大写单位（拾、佰、仟、万、亿、圆、角、分、整 等） */
void append_word(const char* word)
{
    int len = (int)strlen(result);
    int i = 0;
    while (word[i] != '\0')
    {
        result[len + i] = word[i];
        ++i;
    }
    result[len + i] = '\0';
}

int main()
{
    double ori;

    printf("请输入[0-100亿)之间的数字:\n");
    scanf("%lf", &ori);
    printf("大写结果是:\n");

    clear_result();

    if (ori == 0.0)
    {
        /* 0 的特殊情况：零圆整 */
        append_digit(0, 1);
        append_word("圆");
        append_word("整");
    }
    else
    {
        ori /= 10;
        int number = (int)ori;
        ori -= number;
        ori *= 1000;
        ori += 0.5;
        int nori = (int)ori;

        int n_10, n_9, n_8, n_7, n_6, n_5, n_4, n_3, n_2, n_1, n_01, n_02;
        n_10 = number / 100000000;
        n_9 = number / 10000000 % 10;
        n_8 = number / 1000000 % 10;
        n_7 = number / 100000 % 10;
        n_6 = number / 10000 % 10;
        n_5 = number / 1000 % 10;
        n_4 = number / 100 % 10;
        n_3 = number / 10 % 10;
        n_2 = number % 10;
        n_1 = nori / 100;
        n_01 = nori / 10 % 10;
        n_02 = nori % 10;

        append_digit(n_10, 0);
        if (n_10 != 0)
        {
            append_word("拾");
        }

        append_digit(n_9, 0);
        if (n_10 != 0 || n_9 != 0)
        {
            append_word("亿");
        }

        append_digit(n_8, (n_7 != 0 || n_6 != 0 || n_5 != 0) && (n_9 != 0 || n_10 != 0));
        if (n_8 != 0)
        {
            append_word("仟");
        }

        append_digit(n_7, (n_8 != 0 && (n_6 != 0 || n_5 != 0)));
        if (n_7 != 0)
        {
            append_word("佰");
        }

        append_digit(n_6, (n_7 != 0 && n_5 != 0));
        if (n_6 != 0)
        {
            append_word("拾");
        }

        append_digit(n_5, 0);
        if (n_5 != 0 || n_8 != 0 || n_7 != 0 || n_6 != 0)
        {
            append_word("万");
        }

        append_digit(n_4, (n_3 != 0 || n_2 != 0 || n_1 != 0) && ((n_10 != 0 || n_9 != 0) || (n_8 != 0 || n_7 != 0 || n_6 != 0 || n_5 != 0)));
        if (n_4 != 0)
        {
            append_word("仟");
        }

        append_digit(n_3, (n_4 != 0 && (n_2 != 0 || n_1 != 0)));
        if (n_3 != 0)
        {
            append_word("佰");
        }

        append_digit(n_2, (n_3 != 0 && n_1 != 0));
        if (n_2 != 0)
        {
            append_word("拾");
        }

        append_digit(n_1, 0);
        if (n_10 != 0 || n_9 != 0 || n_4 != 0 || n_3 != 0 || n_2 != 0 || n_1 != 0 || n_6 != 0 || n_8 != 0 || n_7 != 0 || n_5 != 0)
        {
            append_word("圆");
        }

        if (n_01 == 0 && n_02 == 0)
        {
            append_word("整");
        }
        else
        {
            append_digit( n_01, (n_10 != 0 || n_9 != 0 || n_4 != 0 || n_3 != 0 || n_2 != 0 || n_1 != 0 || n_6 != 0 || n_8 != 0 || n_7 != 0 || n_5 != 0) );
            if (n_01 != 0)
            {
                append_word("角");
            }

            if (n_02 == 0)
            {
                append_word("整");
            }
            else
            {
                append_digit(n_02, 0);
                if (n_02 != 0)
                {
                    append_word("分");
                }
            }
        }
    }

    /* 大写结果只允许用本语句一次性输出 */
    printf("%s\n", result);
    return 0;
}
