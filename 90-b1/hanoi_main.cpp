/*2152095 计科 龚宣 */

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

     本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#include<iostream>
#include"hanoi.h"
#include"cmd_console_tools.h"

using namespace std;

/***************************************************************************
  函数名称：
  功    能：设置屏幕格式，调用相关功能函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);
	while (1) 
	{
		int choice = menu();//获取菜单选择
		int n;//汉诺塔的层数、
		char src, tmp, dst;//起始柱，中间柱，目标柱

		if (choice == 0)//退出
			break;
		else if (choice == 1||choice==2||choice==3)//基本解/基本解（步数记录）/内部数组显示（横向）
			order_input(&n, &src, &tmp, &dst,0);
		else if (choice == 4)//内部数组显示（横向+纵向）
		{
			order_input(&n, &src, &tmp, &dst, 1);
			cct_cls();
		}
		else if (choice>=5)//带有画图的部分的功能选项
		{
			if (choice == 6 || choice == 7 || choice == 9)
				order_input(&n, &src, &tmp, &dst, 0);
			else if(choice==8)
				order_input(&n, &src, &tmp, &dst, 1);
			cct_cls();
			cct_setcursor(CURSOR_INVISIBLE);
			draw_base();//画基座
		}
		/*初始化和调用汉诺塔函数*/
		if (choice != 5 ) //5项不需要初始化和汉诺塔移动
		{
			cct_setcursor(CURSOR_INVISIBLE);
			init(n, src, dst, choice);//初始化相关变量
			if (choice == 7)  //7项单独考虑，进行一步移动
			{
				if (n % 2 == 0)
					draw_move(src, tmp, 1);
				else
					draw_move(src, dst, 1);
			}
			if(choice!=6&&choice!=7&&choice!=9)//6，7，9不需要汉诺塔移动
				hanoi(n, src, tmp, dst, choice);
			if (choice == 9)
				game_version(n, src, dst);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			
		}
		huiche(choice);//调用读取回车的函数
		cct_cls();  //清屏
	}

	return 0;
}
