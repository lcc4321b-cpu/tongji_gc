//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
using namespace std;

/* ----具体要求----
   1、不允许添加其它头文件
   2、不允许定义全局变量、仅允许hanoi中定义一个静态局部变量
   3、不允许添加其它函数
   4、main函数处理输入，允许循环
   --------------------------------------------------------------------- */

   /***************************************************************************
     函数名称：
     功    能：打印n层汉诺塔的移动顺序
     输入参数：int n：层数
               char src：起始柱
               char tmp：中间柱
               char dst：目标柱
     返 回 值：
     说    明：1、函数名、形参、返回类型均不准动
               2、本函数不允许出现任何形式的循环
               3、允许定义一个静态局部变量
   ***************************************************************************/
void hanoi(int n, char src, char tmp, char dst)
{
    static int frequency = 0;
    if (n <= 0)
    {
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    frequency += 1;
    cout << setw(5)<<frequency<<":" << setw(3) << n << "# " << src << "-->" << dst << endl;
    hanoi(n - 1, tmp, src, dst);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：1、完成输入、调用递归函数
            2、处理输入错误时，允许使用循环
            3、为了统一检查，不再允许添加其它函数（输入起始/目标柱的代码不要求统一函数处理，均直接放在main中）
***************************************************************************/
int main()
{
    int n = 0;
    char src = 0, dst = 0;
    int floor;
    bool finish = 1;
    while (finish)
    {
        cout << "请输入汉诺塔的层数(1-16)" << endl;
        cin >> floor;
        if (cin.good() == 1 && (floor >= 1 && floor <= 16))
        {
            finish = 0;
            n = floor;
        }
        cin.clear();
        cin.ignore(1024, '\n');

    }
    // 读取起始柱（A-C，大小写均可）
    while (1)
    {
        cout << "请输入起始柱 (A-C)" << endl;
        char ch;                    // 取首字符
        cin >> ch;
        if (cin.good() == 1)
        {
            if ('a' <= ch && ch <= 'c')
            {
                ch = ch - 'a' + 'A';
            }
            if (ch == 'A' || ch == 'B' || ch == 'C')
            {
                src = ch;
                cin.clear();
                cin.ignore(1024, '\n');
                break;
            }
        }
        // 清空到行尾
        cin.clear();
        cin.ignore(1024, '\n');
    }

    // 读取目标柱（A-C，且不得与起始柱相同）
    while (1)
    {
        cout << "请输入目标柱 (A-C)\n";
        char ch_2;
        cin >> ch_2;
        if (cin.good() == 1)
        {
            if ('a' <= ch_2 && ch_2 <= 'c')
            {
                ch_2 = ch_2 - 'a' + 'A';
            }
            if (ch_2 == 'A' || ch_2 == 'B' || ch_2 == 'C')
            {
                if (ch_2 != src)
                {
                    dst = ch_2;
                    cin.clear();
                    cin.ignore(1024, '\n');
                    break;
                }
                cout << "目标柱(" << src << ")不能与起始柱(" << src << ")相同" << endl;
            }
        }
        // 清空到行尾
        cin.clear();
        cin.ignore(1024, '\n');
    }

    // 计算中间柱
    char tmp = 'A' + 'B' + 'C' - src - dst;

    cout << "移动步骤为:" << endl;
    hanoi(n, src, tmp, dst);

    return 0;
}
