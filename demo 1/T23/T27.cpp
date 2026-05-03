#include<iostream>
using namespace std;
int main()
{
	int x, y;
	cout << (x = 4 * 3, x = y = 5 * 3) << endl;
	cout << typeid(x = 4 * 3, x = y = 5 * 3).name() << endl;
	return 0;
}