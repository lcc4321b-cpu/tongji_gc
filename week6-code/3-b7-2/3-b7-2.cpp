//2550703 卓03 李良玉
#include<iostream>
using namespace std;

int main()
{
	//get number
	double charge;
	int integer, small_charge;
	int fifty, twenty, ten, five, one;
	int little_fifty, little_ten, little_five, little_two, little_one;
	int total;
	cout << "请输入找零值：" << endl;
	cin >> charge;
	integer = int(charge+0.005);
	small_charge = int(((charge - integer) +0.005) * 100);

	//caculate
	fifty = integer / 50;
	twenty = integer % 50 / 20;
	ten = (integer / 10 - 5 * (integer >= 50)) % 2;
	five = integer % 10 / 5;
	one = integer % 5;
	little_fifty = small_charge / 50;
	little_ten = small_charge % 50 / 10;
	little_five = small_charge % 10 / 5;
	little_two = small_charge % 5 / 2;
	little_one = (small_charge-(little_fifty==1)) % 2;
	total = fifty + twenty + ten + five + one + little_fifty + little_five + little_one + little_ten + little_two;
	
	//print
	cout << "共" << total << "张找零，具体如下：" << endl;
	if (fifty >= 1)
	{
		cout << "50元 : "<< fifty <<"张" << endl;
	}
	if (twenty >= 1)
	{
		cout << "20元 : "<< twenty <<"张" << endl;
	}
	if (ten >= 1)
	{
		cout << "10元 : "<< ten <<"张" << endl;
	}
	if (five >= 1)
	{
		cout << "5元  : "<< five <<"张" << endl;
	}
	if (one >= 1)
	{
		cout << "1元  : "<< one <<"张" << endl;
	}
	if (little_fifty >= 1)
	{
		cout << "5角  : "<< little_fifty <<"张" << endl;
	}
	if (little_ten >= 1)
	{
		cout << "1角  : "<< little_ten <<"张" << endl;
	}
	if (little_five >= 1)
	{
		cout << "5分  : "<< little_five <<"张" << endl;
	}
	if (little_two >= 1)
	{
		cout << "2分  : "<< little_two <<"张" << endl;
	}
	if (little_one >= 1)
	{
		cout << "1分  : "<< little_one <<"张" << endl;
	}
	return 0;
}