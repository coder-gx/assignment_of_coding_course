#include<iostream>
#include<climits>
#include<Windows.h>
#include<conio.h>
#include"cmd_console_tools.h"
#include"90-b2.h"
using namespace std;


/*菜单函数，设置控制台的格式和字体并给出菜单*/
int menu() 
{
	cct_setconsoleborder(120, 30, 120, 9001);
	cct_setfontsize("新宋体", 16, 0);
	cct_setcolor();
	cct_setconsoleborder(120, 30, 120, 9001);//再设置一次，防止之前因为窗口大于缓冲区设置失效
	cout << "---------------------------------------------\n";
	cout << "1.内部数组，随机生成初始5个球\n";
	cout << "2.内部数组，随机生成60%的球，寻找移动路径\n";
	cout << "3.内部数组，完整版\n";
	cout << "4.画出n*n的框架（无分隔线），随机显示5个球\n";
	cout << "5.画出n*n的框架（有分隔线），随机显示5个球\n";
	cout << "6.n*n的框架，60%的球，支持鼠标，完成一次移动\n";
	cout << "7.cmd图形界面完整版\n";
	cout << "---------------------------------------------\n";
	cout << "0.退出\n";
	cout << "---------------------------------------------\n";
	cout << "[请选择:]";
	int n;
	while (1) {
		n = _getche() - '1' + 1;
		if (n >= 0 && n <= 7)
			break;
	}
	return n;
}



int main()
{
	arrays origin;//定义一个自定义arrays类型的origin变量
	while (1) {
		int choice=menu();
		if (choice == 0)
			break;
		cct_cls();
		row_col_input(origin.rows, origin.cols);
		init_array(origin, choice);  //内部数组初始化

		/*内部数组的实现*/
		if (choice == 1||choice==4||choice==5) 
		{
			cout << endl << "初始数组：" << endl;
			print_array(origin, BALL_SHADE);
		}
		else if (choice == 2||choice==3)
			base_version_game(origin, choice);//将2，3结合，组成基础版游戏

		/*图形界面的实现*/
		if (choice>=4){
			if(choice==4||choice==5)
				enter_input();
			cct_cls();
			init_console(origin, choice);//控制台初始化
			if (choice == 4)
				draw_no_line(origin);
			else if (choice == 5 || choice == 6)
				draw_with_line(origin);
			else
				draw_complete(origin);
			if (choice == 6 || choice == 7)//将6，7结合，组成图形界面游戏
				console_version_game(origin, choice);
		}
		end_input();
	}
	return 0;
}
