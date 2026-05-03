#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int a = 12345;
    cout << "0         1         2         3" << endl;
    cout << "0123456789012345678901234567890123456789" << endl;
    /* ×ó¶ÔÆë */
    cout << setiosflags(ios::left) << setw(10) << a << '#' << setw(10) << a + 1 << '*' << endl;
    /* ÓÒ¶ÔÆë */
    cout << setiosflags(ios::right) << setw(10) << a << '#' << setw(10) << a + 1 << '*' << endl;
    /* ×ó¶ÔÆë */
    cout << setiosflags(ios::left) << setw(10) << a << '#' << setw(10) << a + 1 << '*' << endl;
    return 0;
}