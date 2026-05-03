//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
using namespace std;

// 2^-1 ~ 2^-112
const int N_POW = 112;
// 十进制小数位数（多留一位，方便进位）
const int N_NUM = N_POW + 1;

void output_rod(const bool is_upper)
{
    if (is_upper) 
    { //上标尺
        cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "----------- 上标尺  1         2         3         4         5         6         7         8         9         A         B         C" << endl;
        cout << "-----------123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else 
    {//下标尺
        cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "-----------123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" << endl;
        cout << "----------- 下标尺  1         2         3         4         5         6         7         8         9         A         B         C" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

/*
  输出一行十进制小数：
  如果 prompt 为空串，则输出形如：2^-1 : 0.5
  如果 prompt 非空，则先输出 prompt（例如 "计算值 : 0."），再输出小数部分
  说明：d[0] 存放幂次（-1, -2, ...），d[1..N_NUM] 存放十进制小数的每一位
*/
void output(const char prompt[], const int d[])
{
    if (prompt[0] == '\0')
    {
        // 幂次标签，例如 2^-1 :
        cout << "2^" << setw(4) << d[0] << " : 0.";
    }
    else
    {
        cout << prompt;
    }
    // 去掉右侧多余的 0，只保留至少一位
    int last = N_NUM;
    while (last > 1 && d[last] == 0) 
    {
        --last;
    }

    for (int i = 1; i <= last; ++i) 
    {
        cout << d[i];
    }
    cout << endl;
}

/*
  已知 d_cur 表示 2^-i 的十进制小数，计算 d_next 表示 2^-(i+1)
  思路：十进制小数除以 2 的竖式除法，从高位到低位处理即可
  d_cur[0] 存放幂次 -i，d_next[0] 存放幂次 -(i+1)
*/
void calc_next(const int d_cur[], int d_next[])
{
    // 幂次减 1
    d_next[0] = d_cur[0] - 1;

    int carry = 0; // 余数（上一位除以 2 后的余数，0 或 1）
    for (int i = 1; i <= N_NUM; ++i) 
    {
        int value = carry * 10 + d_cur[i]; // 当前要除以 2 的数
        d_next[i] = value / 2;
        carry = value % 2;
    }
}

/*
  根据幂次表，计算某个二进制小数的十进制值
  pure_decimal: 形如 ".10101" 的二进制纯小数（只用到前 112 位）
  out         : 结果的小数部分十进制数字，out[0] 可不用（prompt 非空时会忽略）
  power_table : 幂次表，power_table[i] 表示 2^-i 的十进制小数
*/
void calc_num(const char pure_decimal[], int out[], int power_table[][N_NUM + 1])
{
    for (int j = 0; j <= N_NUM; ++j)
    {
        out[j] = 0;
    }
    int bit_pos = 0; // 小数点后的第几位（1 开始）

    for (int k = 0; pure_decimal[k] != '\0'; ++k) 
    {
        char ch = pure_decimal[k];
        if (ch == '.') 
        {
            continue;
        }
        if (ch == '0' || ch == '1') 
        {
            ++bit_pos;
            if (bit_pos > N_POW) 
            {
                break;
            }
            if (ch == '1') 
            {
                // out += power_table[bit_pos]
                int carry = 0;
                for (int j = N_NUM; j >= 1; --j) 
                {
                    int sum = out[j] + power_table[bit_pos][j] + carry;
                    out[j] = sum % 10;
                    carry = sum / 10;
                }
                // 整数部分永远是 0，不会产生最终进位
            }
        }
    }
}

void input_pure_decimal(char pure_decimal[])
{
    char buf[256];
    cout << "请输入一个二进制纯小数，小数点开头，小数点后不超过112位(例：.101101)" << endl;
    while (true)
    {
        cin.getline(buf,1024);
        int nn = strlen(buf);
        if (nn == 0)
        {
            cout << "不是以.开头，请重输" << endl;
            continue;
        }
        // 检查格式 
        if (buf[0] != '.')
        {
            cout << "不是以.开头，请重输" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        int len = 0;
        while (buf[len] != '\0')
        {
            ++len;
        }
        if (len <= 1)
        {
            cout << "输入数据为空，请重输" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        bool ok = true;
        for (int i = 1; i < len; ++i)
        {
            if (buf[i] != '0' && buf[i] != '1')
            {
                ok = false;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "输入的不是0/1，请重输" << endl;
                break;
            }
        }
        if (ok == false)
        {
            continue;
        }

        for (int i = 1; i < len; ++i)
        {
            if (buf[i] == '1')
            {
                ok = false;
            }
        }

        if (ok) 
        {
            cout << "输入为全0，请重输" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // 复制到 pure_decimal，最多 112 位
        pure_decimal[0] = '.';
        int copy_bits = len - 1;
        if (copy_bits > N_POW)
        {
            copy_bits = N_POW;
        }
        for (int i = 0; i < copy_bits; ++i) 
        {
            pure_decimal[i + 1] = buf[i + 1];
        }
        pure_decimal[copy_bits + 1] = '\0';
        break;
    }
}

int main()
{
    // 幂次表：power_table[i] 表示 2^-i 的十进制小数
    static int power_table[N_POW + 1][N_NUM + 1] = { 0 };

    // 初始化幂次：第 0 行不用
    for (int i = 1; i <= N_POW; ++i)
    {
        power_table[i][0] = -i; // 幂次 -1 ~ -112
    }

    // 2^-1 = 0.5
    power_table[1][1] = 5;

    // 循环计算 2^-2 ~ 2^-112   
    for (int i = 1; i < N_POW; ++i) 
    {
        calc_next(power_table[i], power_table[i + 1]);
    }

    // 输出 2^-1 ~ 2^-112
    output_rod(true);
    for (int i = 1; i <= N_POW; ++i) 
    {
        output("", power_table[i]);
    }
    output_rod(false);
    cout << endl;


    // 输入一个二进制纯小数
    char pure_decimal[N_NUM + 2] = { 0 }; // '.' + 112 位 + '\0'
    input_pure_decimal(pure_decimal);

    // 计算其十进制形式
    int result[N_NUM + 1] = { 0 };
    calc_num(pure_decimal, result, power_table);

    // 输出结果：0.xxx
    cout << endl;
    output_rod(true);
    int num_pure_decimal[114];
    num_pure_decimal[0] = 0;
    for (int i = 1; i <= 113; ++i)
    {
        if (pure_decimal[i] == '1')
        {
            num_pure_decimal[i] = 1;
        }
        else
        {
            num_pure_decimal[i] = 0;
        }
    }
    output("输入数据 : ", num_pure_decimal);
    output("计算值 : 0.", result);
    output_rod(false);
    cout << endl;
    return 0;
}
