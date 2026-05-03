#include <iostream>
#include <iomanip>
using namespace std;

int e[3] = { -1, -1, -1 };
int plate[3][10] = { 0 };
int frequency = 0;

void ppprint()
{
    cout << "A：";
    for (int i = 0; i <= 10; i++) {
        if (!plate[0][i]) {
            cout << setw(20 - 2 * i) << "";
            break;
        }
        else
            cout << plate[0][i] << " ";
    }
    cout << "B：";
    for (int i = 0; i <= 10; i++) {
        if (!plate[1][i]) {
            cout << setw(20 - 2 * i) << "";
            break;
        }
        else
            cout << plate[1][i] << " ";
    }
    cout << "C：";
    for (int i = 0; i <= 10; i++) {
        if (!plate[2][i]) {
            cout << setw(20 - 2 * i) << "";
            break;
        }
        else
            cout << plate[2][i] << " ";
    }
    cout << endl;
}

void mover(char from, char to)
{
    plate[to - 'A'][++e[to - 'A']] = plate[from - 'A'][e[from - 'A']--];
    plate[from - 'A'][e[from - 'A'] + 1] = 0;
}

// 递归保持上次精简后的形式
void hanoi(int n, char src, char tmp, char dst)
{
    if (n == 1) {
        cout << "第" << setw(4) << (++frequency) << " 步"
            << "(" << setw(2) << n << ") : "
            << src << "-->" << dst << " ";
        mover(src, dst);
        ppprint();
        return;
    }

    hanoi(n - 1, src, dst, tmp);

    cout << "第" << setw(4) << (++frequency) << " 步"
        << "(" << setw(2) << n << "): "
        << src << "-->" << dst << " ";
    mover(src, dst);
    ppprint();

    hanoi(n - 1, tmp, src, dst);
}

int main()
{
    int level;
    char from, to;

    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> level;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (1 <= level && level <= 10) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> from;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (('A' <= from && from <= 'C') || ('a' <= from && from <= 'c')) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    if ('a' <= from && from <= 'c') {
        from -= 32;
    }

    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> to;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (to == from || (to - 32 == from)) {
            cout << "目标柱(" << (char)(to == from ? to : to - 32)
                << ")不能与起始柱(" << from << ")相同" << endl;
            continue;
        }

        if (('A' <= to && to <= 'C') || ('a' <= to && to <= 'c')) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    if ('a' <= to && to <= 'c') {
        to -= 32;
    }

    e[from - 'A'] = level - 1;

    for (int i = 0; i < level; i++) {
        plate[from - 'A'][i] = level - i;
    }

    cout << "初始:                ";
    ppprint();

    hanoi(level, from, 'A' + 'B' + 'C' - from - to, to);

    return 0;
}
