//2550703 ×¿03 ÀîÁ¼Óñ
#include<iostream>
using namespace std;

int main()
{
	//get input
	double original_number;
	cout << "ÇëÊäÈë[0-100ÒÚ)Ö®¼äµÄÊı×Ö:" << endl;
	cin >> original_number;
	cout << "´óĞ´½á¹ûÊÇ:" << endl;
	if (original_number == 0.0)
	{
		cout << "ÁãÔ²Õû";
	}

	//divide the original number into several pieces
	int hundreds_of_millions, hundreds_of_thousands, yuan, small_charge;
	int huge, small;
	original_number /= 10;
	huge = int(original_number);
	small = int((original_number - huge + 0.0005) * 1000);
	hundreds_of_millions = int(original_number + 0.0005) / 10000000;
	hundreds_of_thousands = int(original_number + 0.0005) / 1000 % 10000;
	int yuan_part_1, yuan_part_2;
	yuan_part_1 = huge % 1000;
	yuan_part_2 = small / 100;
	yuan = yuan_part_1 * 10 + yuan_part_2;
	small_charge = small % 100;

	//get number
	int hundreds_of_millions_1, hundreds_of_millions_2;
	int hundreds_of_thousands_1, hundreds_of_thousands_2, hundreds_of_thousands_3, hundreds_of_thousands_4;
	int yuan_1, yuan_2, yuan_3, yuan_4;
	int small_charge_1, small_charge_2;
	hundreds_of_millions_1 = hundreds_of_millions / 10;
	hundreds_of_millions_2 = hundreds_of_millions % 10;
	hundreds_of_thousands_1 = hundreds_of_thousands / 1000;
	hundreds_of_thousands_2 = hundreds_of_thousands / 100 % 10;
	hundreds_of_thousands_3 = hundreds_of_thousands / 10 % 10;
	hundreds_of_thousands_4 = hundreds_of_thousands % 10;
	yuan_1 = yuan / 1000;
	yuan_2 = yuan / 100 % 10;
	yuan_3 = yuan / 10 % 10;
	yuan_4 = yuan % 10;
	small_charge_1 = small_charge / 10;
	small_charge_2 = small_charge % 10;



	//¸ñÊ½£¿
	//hundreds_of_millions
	switch (hundreds_of_millions_1)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (hundreds_of_millions_1 >= 1)
	{
		cout << "Ê°";
	}

	switch (hundreds_of_millions_2)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (hundreds_of_millions > 0)
	{
		cout << "ÒÚ";
	}

	//hundreds_of_thousands
	switch (hundreds_of_thousands_1)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (hundreds_of_thousands_1 >= 1)
	{
		cout << "Çª";
	}
	else if (hundreds_of_millions >= 1&&(hundreds_of_thousands>0||yuan>0))
	{
		cout << "Áã";
	}

	switch (hundreds_of_thousands_2)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (hundreds_of_thousands_2 >= 1)
	{
		cout << "°Û";
	}
	else if (hundreds_of_thousands_1 >= 1 && (hundreds_of_thousands_3>0||hundreds_of_thousands_4>0))
	{
		cout << "Áã";
	}

	switch (hundreds_of_thousands_3)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (hundreds_of_thousands_3 >= 1)
	{
		cout << "Ê°";
	}
	else if (hundreds_of_thousands_2 >= 1 && (hundreds_of_thousands_4>0))
	{
		cout << "Áã";
	}

	switch (hundreds_of_thousands_4)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (hundreds_of_thousands >= 1)
	{
		cout << "Íò";
	}

	//yuan
	switch (yuan_1)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (yuan_1 >= 1)
	{
		cout << "Çª";
	}
	else if (hundreds_of_thousands_2 >= 1||hundreds_of_thousands_3>=1||hundreds_of_thousands_4>=1)
	{
		cout << "Áã";
	}
	switch (yuan_2)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (yuan_2 >= 1)
	{
		cout << "°Û";
	}
	else if (yuan_1 >= 1&&(yuan_3>0||yuan_4>0))
	{
		cout << "Áã";
	}
	switch (yuan_3)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (yuan_3 >= 1)
	{
		cout << "Ê°";
	}
	else if (yuan_2 >= 1 && (yuan_3>0||yuan_4>0))
	{
		cout << "Áã";
	}
	switch (yuan_4)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	int non_small_charge = 0;
	if (yuan >= 1 || hundreds_of_millions >= 1 || hundreds_of_thousands >= 1)
	{
		cout << "Ô²";
		if (small_charge == 0)
		{
			cout << "Õû";
			non_small_charge = 1;
		}
	}

	//small_charge
	switch (small_charge_1)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (small_charge_1 >= 1)
	{
		cout << "½Ç";
	}
	if ((small_charge_2 == 0) && (small_charge_1 >= 1))
	{
		cout << "Õû";
	}
	else if ((hundreds_of_millions >= 1 || hundreds_of_thousands >= 1 || yuan >= 1) && (small_charge_1 == 0)&&(small_charge_2>0))
	{
		cout << "Áã";
	}
	switch (small_charge_2)
	{
		case 1:
			cout << "Ò¼";
			break;
		case 2:
			cout << "·¡";
			break;
		case 3:
			cout << "Èş";
			break;
		case 4:
			cout << "ËÁ";
			break;
		case 5:
			cout << "Îé";
			break;
		case 6:
			cout << "Â½";
			break;
		case 7:
			cout << "Æâ";
			break;
		case 8:
			cout << "°Æ";
			break;
		case 9:
			cout << "¾Á";
			break;
	}
	if (small_charge_2 >= 1)
	{
		cout << "·Ö";

	}


	cout << "" << endl;
	return 0;
}