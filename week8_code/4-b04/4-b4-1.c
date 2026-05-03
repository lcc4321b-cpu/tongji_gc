//2550703 卓03 李良玉
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <tchar.h>

const int MAX_X = 69;	//定义*组成的边框的宽度
const int MAX_Y = 17;	//定义*组成的边框的高度


/***************************************************************************
  函数名称：
  功    能：完成与system("cls")一样的功能，但效率高
  输入参数：
  返 回 值：
  说    明：清除整个屏幕缓冲区，不仅仅是可见窗口区域(使用当前颜色)
***************************************************************************/
void cls(const HANDLE hout)
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo; /* to get buffer info */
	DWORD num;

	/* 取当前缓冲区信息 */
	GetConsoleScreenBufferInfo(hout, &binfo);
	/* 填充字符 */
	FillConsoleOutputCharacter(hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	/* 填充属性 */
	FillConsoleOutputAttribute(hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);

	/* 光标回到(0,0) */
	SetConsoleCursorPosition(hout, coord);
	return;
}

/***************************************************************************
  函数名称：gotoxy
  功    能：将光标移动到指定位置
  输入参数：HANDLE hout ：输出设备句柄
			int X       ：指定位置的x坐标
			int Y       ：指定位置的y坐标
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  函数名称：showch
  功    能：在指定位置处打印一个指定的字符
  输入参数：HANDLE hout ：输出设备句柄
			int X       ：指定位置的x坐标
			int Y       ：指定位置的y坐标
			char ch     ：要打印的字符
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}

/***************************************************************************
  函数名称：init_border
  功    能：显示初始的边框及随机字符
  输入参数：HANDLE hout：输出设备句柄
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void init_border(const HANDLE hout)
{
	gotoxy(hout, 0, 0);	//光标移回左上角(0,0)
	printf("***********************************************************************\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("***********************************************************************\n");

	/* 随机显示20个大写字母，字母的值、XY坐标都随机显示
	   rand()函数的功能：随机生成一个在 0-32767 之间的整数
	   思考：在什么情况下，下面这个循环执行生成后，你看到的实际字母个数不足20个？ */
	int i;
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	return;
}

// 几何中心（内部坐标：X∈[1..MAX_X], Y∈[1..MAX_Y]）
int centerX() { return (MAX_X + 1) / 2; }
int centerY() { return (MAX_Y + 1) / 2; }

// 单轴移动：返回新 X（或新 Y）
int nextPos(int cur, int delta, int maxv, int wrap)
{
	int v = cur + delta;
	if (wrap) {
		if (v < 1) v = maxv;
		if (v > maxv) v = 1;
	}
	else {
		if (v < 1 || v > maxv) v = cur;
	}
	return v;
}

//空格替换
void try_erase_here(const HANDLE hout, int x, int y)
{
	showch(hout, x, y, ' ');
	gotoxy(hout, x, y);
}

// 删除当前位置字符（若无字母也无副作用）
void delete_here(const HANDLE hout, int x, int y)
{
	showch(hout, x, y, ' ');
}

// 一局游戏：mode=0 用 IJKL；mode=1 用方向键；wrap=0 不环绕，1 环绕
void play_once(const HANDLE hout, int mode, int wrap)
{
	cls(hout);
	init_border(hout);

	int x = centerX();
	int y = centerY();
	gotoxy(hout, x, y);

	while (1) {
		int c = _getch();
		if (c == ' ')
		{
			try_erase_here(hout, x, y);
			continue;
		}
		if (mode == 0) { // IJKL
			if (c == 'i' || c == 'I') y = nextPos(y, -1, MAX_Y, wrap);
			else if (c == 'k' || c == 'K') y = nextPos(y, +1, MAX_Y, wrap);
			else if (c == 'j' || c == 'J') x = nextPos(x, -1, MAX_X, wrap);
			else if (c == 'l' || c == 'L') x = nextPos(x, +1, MAX_X, wrap);
			else if (c == 'q' || c == 'Q') break;
			else if (c == 0 || c == 224) { // 扩展键：Delete
				int b = _getch();
				if (b == 83) delete_here(hout, x, y);
			}
			else if (c == 127) {
				delete_here(hout, x, y);
			}
		}
		else { // 方向键
			if (c == 0 || c == 224) {
				int b = _getch();
				if (b == 72) y = nextPos(y, -1, MAX_Y, wrap); // ↑
				else if (b == 80) y = nextPos(y, +1, MAX_Y, wrap); // ↓
				else if (b == 75) x = nextPos(x, -1, MAX_X, wrap); // ←
				else if (b == 77) x = nextPos(x, +1, MAX_X, wrap); // →
				else if (b == 83) delete_here(hout, x, y);        // Del
			}
			else if (c == 'q' || c == 'Q') {
				break;
			}
			else if (c == 127) {
				delete_here(hout, x, y);
			}
		}
		gotoxy(hout, x, y);
	}

	// 下方第 5 行提示（18+5=23）
	gotoxy(hout, 0, 23);
	printf("游戏结束，按回车键返回菜单.");
	while (1) {
		int k = _getch();
		if (k == '\r' || k == '\n') break; // 只接受回车
	}
}

// 菜单（0~4，单键选择，无需回车）
int menu(const HANDLE hout)
{
	cls(hout);

	printf("1.用I、J、K、L键控制上下左右(大小写均可，按左箭头光标不允许下移，边界停止)\n");
	printf("2.用I、J、K、L键控制上下左右(大小写均可，按左箭头光标不允许下移，边界回绕)\n");
	printf("3.用箭头键控制上下左右（按大写HPKM不允许移动光标，边界停止）\n");
	printf("4.用箭头键控制上下左右（按大写HPKM不允许移动光标，边界回绕）	\n");
	printf("0. 退出\n");
	printf("[请选择 0-4]");
	while (1) {
		int c = _getch();
		if (c >= '0' && c <= '4') return c - '0';
	}
}

int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

	/* 生成伪随机数的种子，只需在程序开始时执行一次即可 */
	srand((unsigned int)(time(0)));


	// —— 正式进入菜单循环（满足 0-4 项）
	while (1) {
		int sel = menu(hout);
		if (sel == 0) { cls(hout); return 0; }
		else if (sel == 1) play_once(hout, /*IJKL*/0, /*wrap*/0);
		else if (sel == 2) play_once(hout, /*IJKL*/0, /*wrap*/1);
		else if (sel == 3) play_once(hout, /*ARROW*/1, /*wrap*/0);
		else if (sel == 4) play_once(hout, /*ARROW*/1, /*wrap*/1);
	}

	return 0;
}
