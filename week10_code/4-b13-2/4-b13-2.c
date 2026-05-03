//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int frequency = 0;
/* ----具体要求----
   1、不允许添加其它头文件
   2、允许定义一个全局变量、不允许定义静态局部变量
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
   ***************************************************************************/
void hanoi(int n, char src, char tmp, char dst)
{
    if (n <= 0)
    {
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    frequency += 1;
    printf("%5d:%3d# %c-->%c\n",frequency, n, src, dst);
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
    int finish = 1;

    // 读取汉诺塔层数
    while (finish)
    {
        printf("请输入汉诺塔的层数(1-16)\n");
        if (scanf("%d", &floor) == 1 && (floor >= 1 && floor <= 16))
        {
            finish = 0;
            n = floor;
        }

        // 清空到行尾，对应 cin.clear()+cin.ignore()
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }

    // 读取起始柱（A-C，大小写均可）
    while (1)
    {
        printf("请输入起始柱 (A-C)\n");
        char ch;

        if (scanf(" %c", &ch) == 1)      // 前面的空格跳过前导空白
        {
            if ('a' <= ch && ch <= 'c')
            {
                ch = ch - 'a' + 'A';
            }
            if (ch == 'A' || ch == 'B' || ch == 'C')
            {
                src = ch;

                // 清空到行尾
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }
        }

        // 清空到行尾
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // 读取目标柱（A-C，且不得与起始柱相同）
    while (1)
    {
        printf("请输入目标柱 (A-C)\n");
        char ch_2;

        if (scanf(" %c", &ch_2) == 1)
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

                    // 清空到行尾
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                // 按原逻辑打印提示（两个都是 src）
                printf("目标柱(%c)不能与起始柱(%c)相同\n", src, src);
            }
        }

        // 清空到行尾
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // 计算中间柱
    char tmp = 'A' + 'B' + 'C' - src - dst;

    printf("移动步骤为:\n");
    hanoi(n, src, tmp, dst);

    return 0;
}
