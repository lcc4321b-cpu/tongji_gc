//2550703 卓03 李良玉
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

/* -----------------------------------------------------------------------------------
		允许   ：1、按需增加一个或多个函数（包括递归函数），但是所有增加的函数中不允许任何形式的循环
				 2、定义符号常量
				 3、定义const型变量

		不允许 ：1、定义全局变量
				 2、除print_tower之外的其他函数中不允许定义静态局部变量
   ----------------------------------------------------------------------------------- */
void iprint(int num, bool order)
//order: 1=>正；0=>逆
{
	if (order == 0)
	{
		if (num == 0)
		{
			return;
		}
		cout << char(64 + num);
		iprint(num-1, order);
	}
	else
	{
		if (num == 1)
		{
			return;
		}
		else
		{
			iprint(num - 1, order);
			cout << char(64 + num);
		}
	}
	
}

   /***************************************************************************
	 函数名称：
	 功    能：打印字母塔
	 输入参数：
	 返 回 值：
	 说    明：形参按需设置
			   提示：有一个参数order，指定正序/倒序
   ***************************************************************************/
void print_tower(int letter_num, bool order, bool skip_first)
//order: 1=>正；0=>逆
//letter_num: 第几个字母
{
	static int number = 0;
	if (order == 1)
	{
		if (number == letter_num)
		{
			return;
		}
		else
		{
			number += 1;
			cout << std::setfill(' ') << std::right << std::setw(letter_num - number)<<"";
			iprint(number, 0);
			iprint(number, 1);
			cout << endl;
			print_tower(letter_num, order, skip_first);
		}
	}
	else
	{
		if (number == 0)
		{
			return;
		}
		if (skip_first && number == letter_num) 
		{
			number -= 1;
		}
		cout << std::setfill(' ') << std::right << std::setw(letter_num - number) << "";
		iprint(number, 0);
		iprint(number, 1);
		cout << endl;
		number -= 1;
		print_tower(letter_num, order, skip_first);
	}
	

	/* 允许按需定义最多一个静态局部变量（也可以不定义） */

	/* 按需实现，函数中不允许任何形式的循环，函数允许调用其它函数 */

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数中的...允许修改，其余位置不准修改
***************************************************************************/
int main()
{
	char end_ch;

	/* 键盘输入结束字符(仅大写有效，为避免循环出现，不处理输入错误) */
	cout << "请输入结束字符(A~Z)" << endl;
	end_ch = getchar();			//读缓冲区第一个字符
	if (end_ch < 'A' || end_ch > 'Z') {
		cout << "结束字符不是大写字母" << endl;
		return -1;
	}

	/* 正三角字母塔(中间为A) */
	cout << std::setfill('=') << std::setw(end_ch * 2 - 129) << "" << endl; /* 按字母塔最大宽度输出=(不允许用循环) */
	cout << "正三角字母塔(" << end_ch << "->A)" << endl;
	cout << std::setfill('=') << std::setw(end_ch * 2 - 129) << "" << endl; /* 按字母塔最大宽度输出=(不允许用循环) */
	print_tower(int(end_ch - 'A' + 1), 1, false); //正序打印 A~结束字符 
	cout << endl;

	/* 倒三角字母塔(中间为A) */
	cout << std::setfill('=') << std::setw(end_ch * 2 - 129) << "" << endl; /* 按字母塔最大宽度输出=(不允许用循环) */
	cout << "倒三角字母塔(" << end_ch << "->A)" << endl;
	cout << std::setfill('=') << std::setw(end_ch * 2 - 129) << "" << endl; /* 按字母塔最大宽度输出=(不允许用循环) */
	print_tower(int(end_ch - 'A'+1), 0, false); //逆序打印 A~结束字符 
	cout << endl;

	/* 合起来就是漂亮的菱形（中间为A） */
	cout << std::setfill('=') << std::setw(end_ch * 2 - 129) << "" << endl;/* 按字母塔最大宽度输出= */
	cout << "菱形(" << end_ch << "->A)" << endl;
	cout << std::setfill('=') << std::setw(end_ch * 2 - 129) << "" << endl;/* 按字母塔最大宽度输出= */
	print_tower(int(end_ch - 'A' + 1), 1, false);   //打印 A~结束字符的正三角 
	print_tower(int(end_ch - 'A' + 1), 0, true);   //打印 A~结束字符-1的倒三角 
	cout << endl;

	return 0;
}
