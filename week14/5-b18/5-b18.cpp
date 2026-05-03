//2550703 卓03 李良玉
/*2550704 孙湛桐 2551163 陈佳骏 2551599 覃雷伟俊 2551102 王薛皓 2550735 邵梓懿*/
#include <iostream>
using namespace std;

// 判断字符是否属于允许的“其它符号”集合
bool is_other(char c)
{
    const char other[] = "!@#$%^&*-_=+,.?";
    for (int i = 0; other[i] != '\0'; ++i)
    {
        if (other[i] == c)
            return true;
    }
    return false;
}

// 判断是否为可见 ASCII 字符（33~126）
bool is_visible_ascii(unsigned char c)
{
    return (c >= 33 && c <= 126);
}

int main()
{
    char line[512];
    if (!cin.getline(line, 512))
    {
        cout << "错误" << endl;
        return 0;
    }

    int len, up, low, dig, oth;
    if (!(cin >> len >> up >> low >> dig >> oth))
    {
        cout << "错误" << endl;
        return 0;
    }
    cin.ignore(1024, '\n');

    if (len < 12 || len > 16 || up < 2 || up > len || low < 2 || low > len || dig < 2 || dig > len || oth < 2 || oth > len || (up + low + dig + oth) > len)
    {
        cout << "错误" << endl;
        return 0;
    }

    bool ok_all = true;

    for (int t = 0; t < 10; ++t)
    {
        char pwd[256];
        if (!cin.getline(pwd, 256))
        {
            ok_all = false;
            break;
        }

        int actualLen = 0;
        while (pwd[actualLen] != '\0')
            actualLen++;

        if (actualLen != len)
        {
            ok_all = false;
            break;
        }

        int cu = 0, cl = 0, cd = 0, co = 0;
        for (int i = 0; i < actualLen; ++i)
        {
            char uc = pwd[i];
            char c = pwd[i];

            if (!is_visible_ascii(uc))
            {
                ok_all = false;
                break;
            }

            // 分类统计
            if (c >= 'A' && c <= 'Z')
                cu++;
            else if (c >= 'a' && c <= 'z')
                cl++;
            else if (c >= '0' && c <= '9')
                cd++;
            else
            {
                if (!is_other(c))
                {
                    ok_all = false;
                    break;
                }
                co++;
            }
        }

        if (!ok_all)
            break;

        if (cu < up || cl < low || cd < dig || co < oth || cu + cl + cd + co != len)
        {
            ok_all = false;
            break;
        }
    }

    cout << (ok_all ? "正确" : "错误") << endl;
    return 0;
}