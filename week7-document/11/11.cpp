#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n = 0, i, m, k;
    bool prime;
    for (m = 103; m <= 200; m += 2) { //偶数没必要判断
        prime = true;            //对每个数，先认为是素数
        k = int(sqrt(m));
        for (i = 2; i <= k; i++)
            if (m % i == 0) {
                prime = false;
                break;
            }

        if (prime) 
        {
            cout << setw(5) << m;
            n = n + 1;      //计数器，只为了加输出换行
            if (n % 10 == 0)    //每10个数输出一行
            {
                cout << endl;
            }
        }

    } //end of for

    return 0;
}