//2550703 卓03 李良玉
#include <iostream>
#include <string>
using namespace std;

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖"; 
string result;

void append_digit(int num, int flag_zero)
{
    const int bytes_per = 2;

    if (num == 0)
    {
        if (!flag_zero)
        {
            return;
        }
        result.append(chnstr + 0 * bytes_per, bytes_per);
    }
    else
    {
        if (num < 0 || num > 9)
        {
            return;
        }
        result.append(chnstr + num * bytes_per, bytes_per);
    }
}

/* 追加一个大写单位（拾、佰、仟、万、亿、圆、角、分、整 等） */
void append_word(const char* word)
{
    result += word;
}

int main()
{
    cout << "请输入[0-100亿)之间的数字:" << endl;
    double ori;
    cin >> ori;
    cout << "大写结果是:" << endl;

    result.clear();

    if (ori == 0.0)
    {
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

        append_digit(n_4, (n_3 != 0 || n_2 != 0 || n_1 != 0) && ((n_10 != 0 || n_9 != 0) || (n_8 != 0 || n_7 != 0 || n_6 != 0 || n_5 != 0)) );
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
            append_digit( n_01, (n_10 != 0 || n_9 != 0 || n_4 != 0 || n_3 != 0 || n_2 != 0 || n_1 != 0 || n_6 != 0 || n_8 != 0 || n_7 != 0 || n_5 != 0));
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

    // 转换得到的大写结果，只允许用本语句输出
    cout << result << endl;
    return 0;
}
