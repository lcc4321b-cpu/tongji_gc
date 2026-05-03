#define _CRT_SECURE_NO_WARNINGS  //VSÐèÒª
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char str1[30] = "Tongji ";
	char str2[30] = "Tongji ";
	char str3[] = "University";
	cout << strncat(str1, str3, 3) << '*' << endl;
	cout << strncat(str2, str3, 300) << '*' << endl;

	return 0;
}