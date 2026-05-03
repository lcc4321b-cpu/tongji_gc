#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
    int i, j, count = 0;
    for (i = 1; i <= 100; i++) {
        for (j = 1; i <= 100; j++) { //注意：表达式2是i<=100
            ++count;
            if (count % 1000 == 0) {
                cout << "*";
                _getch();
            }
        }
    }

    cout << "count = " << count << endl;
    return 0;
}
//注意：这个程序无法通过按CTRL+C终止，要关窗口