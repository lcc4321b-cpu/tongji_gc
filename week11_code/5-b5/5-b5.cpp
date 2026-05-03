//2550703 卓03 李良玉
#include <iostream>
using namespace std;

int main() 
{
    const int MAX_N = 1000;
    int score[MAX_N];
    int cnt[101];
    int n = 0;
    int x;
    for (int i = 0; i <= 100; ++i)
    {
        cnt[i] = 0;
    }

    cout << "请输入成绩（最多1000个），负数结束输入" << endl;
    while (n < MAX_N && (cin >> x))
    {
        if (x < 0)
        {
            break;  // 负数结束输入，但不计入有效数据
        }
        score[n] = x;
        n++;
        if (x >= 0 && x <= 100)
        {
            cnt[x]++;
        }
    }
    cin.clear();
    cin.ignore(1024, '\n');

    if (n == 0)
    {
        cout << "无有效输入" << endl;
        return 0;
    }

    cout << "输入的数组为:" << endl;

    for (int i = 0; i < n; ++i)
    {
        cout << score[i];
        if ((i + 1) % 10 == 0 || i == n - 1)
        {
            cout << endl;
        }
        else
        {
            cout << " ";
        }
    }

    cout << "分数与名次的对应关系为:" << endl;
    int processed = 0;

    for (int s = 100; s >= 0; --s)
    {
        if (cnt[s] > 0)
        {
            int rank = processed + 1;
            for (int k = 0; k < cnt[s]; ++k)
            {
                cout << s << " " << rank << endl;
            }
            processed += cnt[s];
        }
    }

    return 0;
}
