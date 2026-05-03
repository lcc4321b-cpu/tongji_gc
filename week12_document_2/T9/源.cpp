#define _CRT_SECURE_NO_WARNINGS  //VS需要
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char str1[] = "Tongji ";

	char str3[] = "University"; //缺省长度为11
	cout << strncat(str1, str3, 3) << '*' << endl;

	return 0;
}