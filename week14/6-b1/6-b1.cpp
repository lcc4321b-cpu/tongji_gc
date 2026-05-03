//2550703 卓03 李良玉
#include <iostream>
#include <cstdio>
using namespace std;

#define N 10 

int main()
{
    char str[256], * p;
    int a[N] = { 0 }, * pnum, * pa;
    bool is_num;

    cout << "请输入间隔含有若干正负数字的字符串" << endl;

    if (fgets(&str[0], 256, stdin) == NULL)
    {
        str[0] = '\0';
    }

    p = str;
    pa = a;
    pnum = a;
    is_num = false;

    while (*p != '\0')
    {
        if (*p >= '0' && *p <= '9')
        {
            if (!is_num)
            {
                is_num = true;
                if (pnum < pa + N)
                {
                    *pnum = 0;
                }
            }
            if (pnum < pa + N)
            {
                *pnum = (*pnum) * 10 + (*p - '0');
            }
        }
        else
        {
            if (is_num)
            {
                if (pnum < pa + N)
                {
                    pnum++;
                }
                is_num = false;
            }
        }
        p++;
    }
    // 处理以数字结尾的情况
    if (is_num)
    {
        if (pnum < pa + N)
        {
            pnum++;
        }
    }

    cout << "共有" << static_cast<int>(pnum - pa) << "个整数" << endl;

    // 输出全部解析出的数字
    pa = a;
    if (pa < pnum)
    {
        cout << *pa;
        pa++;
        while (pa < pnum)
        {
            cout << " " << *pa;
            pa++;
        }
    }
    cout << endl;
    return 0;
}
