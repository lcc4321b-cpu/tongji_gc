//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
using namespace std;
int tower[3] = { -1, -1, -1 };
int plate[3][10] = { 0 };
int frequency = 0;

void move(char s, char d)
{
    plate[d - 'A'][++tower[d - 'A']] = plate[s - 'A'][tower[s - 'A']--];
    plate[s - 'A'][tower[s - 'A'] + 1] = 0;
}

void print()
{
    cout << "A:";
    for (int i = 0; i <= 10; i++)
    {
        if (!plate[0][i])
        {
            cout << setw(20 - 2 * i) << "";
            break;
        }
        else
            cout << setw(2) << plate[0][i] << "";
    }
    cout << "B:";
    for (int i = 0; i <= 10; i++) 
    {
        if (!plate[1][i]) 
        {
            cout << setw(20 - 2 * i) << "";
            break;
        }
        else
            cout <<setw(2)<<plate[1][i] << "";
    }
    cout << "C:";
    for (int i = 0; i <= 10; i++) 
    {
        if (!plate[2][i]) {
            cout << setw(20 - 2 * i) << "";
            break;
        }
        else
            cout << setw(2) << plate[2][i] << "";
    }
    cout << endl;
}

void hanoi(int n, char src, char tmp, char dst)
{
    if (n == 1)
    {
        cout << "第" << setw(4) << (++frequency) << " 步" << "(" << setw(2) << n << ") : " << src << "-->" << dst << " ";
        move(src, dst);
        print();
        return;
    }
    if (n == 2)
    {
        cout << "第" << setw(4) << (++frequency) << " 步" << "(" << setw(2) << n - 1 << "): " << src << "-->" << tmp << " ";
        move(src, tmp);
        print();
        cout << "第" << setw(4) << (++frequency) << " 步" << "(" << setw(2) << n << "): " << src << "-->" << dst << " ";
        move(src, dst);
        print();
        cout << "第" << setw(4) << (++frequency) << " 步" << "(" << setw(2) << n - 1 << "): " << tmp << "-->" << dst << " ";
        move(tmp, dst);
        print();
        return;
    }
    else
    {
        hanoi(n - 1, src, dst, tmp);
        cout << "第" << setw(4) << (++frequency) << " 步" << "(" << setw(2) << n << "): " << src << "-->" << dst << " ";
        move(src, dst);
        print();
        hanoi(n - 1, tmp, src, dst);
        return;
    }
}

int main()
{
    int n = 0;
    char src = 0, dst = 0;
    int floor;
    bool finish = 1;
    while (finish)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> floor;
        if (cin.good() == 1 && (floor >= 1 && floor <= 10))
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

    tower[src - 'A'] = floor - 1;

    for (int i = 0; i < floor; i++) 
    {
        plate[src - 'A'][i] = floor - i;
    }
    cout << "初始:                ";
    print();

    hanoi(floor, src, tmp, dst);


    return 0;
}