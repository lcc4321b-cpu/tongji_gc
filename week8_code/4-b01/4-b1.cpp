//2550703 卓03 李良玉
#include <iostream>
using namespace std;


void daxie(int num, int flag_of_zero)
{
	/* 不允许对本函数做任何修改 */
	switch (num) {
		case 0:
			if (flag_of_zero)	//此标记什么意思请自行思考
				cout << "零";
			break;
		case 1:
			cout << "壹";
			break;
		case 2:
			cout << "贰";
			break;
		case 3:
			cout << "叁";
			break;
		case 4:
			cout << "肆";
			break;
		case 5:
			cout << "伍";
			break;
		case 6:
			cout << "陆";
			break;
		case 7:
			cout << "柒";
			break;
		case 8:
			cout << "捌";
			break;
		case 9:
			cout << "玖";
			break;
		default:
			cout << "error";
			break;
	}
}


int main()
{
	cout << "请输入[0-100亿)之间的数字:" << endl;

	double ori;
	cin >> ori;

	cout << "大写结果是:" << endl;

	if (ori == 0.0)
	{
		daxie(0, 1);
		cout << "圆整";
		cout << endl;
		return 0;
	}

	ori /= 10;
	int number = int(ori);
	ori -= number;
	ori *= 1000;

	ori += 0.5;
	int nori = (int)ori;

	int n_10, n_9, n_8, n_7, n_6, n_5, n_4, n_3, n_2, n_1, n_01, n_02;
	n_10 = number / 100000000;
	n_9 = number / 10000000 % 10;
	n_8 = number / 1000000 % 10;
	n_7 = number / 100000 % 10;
	n_6 = number / 10000 % 10;
	n_5 = number / 1000 % 10;
	n_4 = number / 100 % 10;
	n_3 = number / 10 % 10;
	n_2 = number % 10;
	n_1 = nori / 100;
	n_01 = nori / 10 % 10;
	n_02 = nori % 10;

	daxie(n_10, 0);
	if (n_10 != 0)
	{
		cout << "拾";
	}
	daxie(n_9, 0);
	if (n_10!=0||n_9!=0)
	{
		cout << "亿";
	}
	daxie(n_8, (n_7 != 0 || n_6 != 0 || n_5 != 0)&&(n_9!=0||n_10!=0));
	if (n_8 != 0)
	{
		cout << "仟";
	}
	daxie(n_7, (n_8 != 0 && (n_6 != 0 || n_5 != 0)));
	if (n_7 != 0)
	{
		cout << "佰";
	}
	daxie(n_6, (n_7 != 0 && n_5 != 0));
	if (n_6 != 0)
	{
		cout << "拾";
	}
	daxie(n_5, 0);
	if (n_5 != 0||n_8!=0||n_7!=0||n_6!=0)
	{
		cout << "万";
	}
	daxie(n_4, (n_3 != 0 || n_2 != 0 || n_1 != 0) && ((n_10!=0||n_9!=0)||(n_8!=0||n_7!=0||n_6!=0||n_5!=0)));
	if (n_4 != 0)
	{
		cout << "仟";
	}
	daxie(n_3, (n_4 != 0 && (n_2 != 0 || n_1 != 0)));
	if (n_3 != 0)
	{
		cout << "佰";
	}
	daxie(n_2, (n_3 != 0 && n_1 != 0));
	if (n_2 != 0)
	{
		cout << "拾";
	}
	daxie(n_1, 0);
	if (n_10!=0||n_9!=0||n_4 != 0 || n_3 != 0 || n_2 != 0 || n_1 != 0 || n_6 != 0 || n_8 != 0 || n_7 != 0 || n_5 != 0)
	{
		cout << "圆";
	}
	if (n_01==0&&n_02==0)
	{
		cout << "整";
		cout << endl;
		return 0;
	}
	daxie(n_01, (n_10 != 0 || n_9 != 0 || n_4 != 0 || n_3 != 0 || n_2 != 0 || n_1 != 0 || n_6 != 0 || n_8 != 0 || n_7 != 0 || n_5 != 0));
	if (n_01 != 0)
	{
		cout << "角";
	}
	if (n_02==0)
	{
		cout << "整";
		cout << endl;
		return 0;
	}
	daxie(n_02, 0);
	if (n_02 != 0)
	{
		cout << "分";
	}
	cout << endl;
	return 0;
}
