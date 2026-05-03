#include<iostream>
using namespace std;
int main()
{
	int a, b, c;
	a = 1;
	b = 7;
	c = -3;
	cout<< a + (b - 3 / (b + c) % 4) * 5 <<endl;
	cout << typeid(a + (b - 3 / (b + c) % 4) * 5).name() << endl;
	return 0;
}