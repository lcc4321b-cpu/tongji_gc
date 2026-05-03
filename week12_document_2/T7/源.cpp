#define _CRT_SECURE_NO_WARNINGS  //VS需要
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char str1[] = "Tongji ";
	char str2[] = "University";
	cout << strcat(str1, str2) << '#' << endl; //加#的目的?

	return 0;
}