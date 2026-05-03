#include <iostream>
using namespace std;

int main()
{
    int i = 0, sum = 0;

    while (i < 1000) {
        i++;
        continue;
        sum = sum + i;
    }

    cout << "i=" << i;
    cout << " sum=" << sum << endl;

    return 0;
}
