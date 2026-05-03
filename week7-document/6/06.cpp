#include <iostream>
using namespace std;

int main()
{
    int i, j, k;
    int count1 = 0, count2 = 0, count3 = 0;

    for (i = 1; i <= 100; i++) {
        ++count1;
        for (j = i; j <= 100; j++) { //注意：初值与上题不同
            ++count2;
            for (k = j; k <= 100; k++) //注意：初值与上题不同
                ++count3;
        }
    }
    cout << "count1=" << count1 << endl;
    cout << "count2=" << count2 << endl;
    cout << "count3=" << count3 << endl;
    return 0;
}
