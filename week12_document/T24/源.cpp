#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    char a[10], b[20];

    fgets(a, 10, stdin);
    fgets(b, 20, stdin);

    cout << a << endl;
    cout << b << endl;

    /* Êä³ö1 */
    int i;
    for (i = 0; a[i] != '\0'; i++)
        cout << int(a[i]) << ' ';
    cout << endl;

    /* Êä³ö2 */
    for (i = 0; b[i] != '\0'; i++)
        cout << int(b[i]) << ' ';
    cout << endl;

    return 0;
}