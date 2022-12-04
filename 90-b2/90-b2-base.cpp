#include<iostream>
#include"cmd_console_tools.h"
#include"90-b2.h"
#include<iomanip>
using namespace std;

/***************************************************************************
  函数名称：
  功    能：打印内部数组
  输入参数：const arrays origin:只读的记录内部数组的自定义结构体类型  
           int choice:打印方式（BALL_SHADE：有球的地方着色，PATH：打印路径，PATH_SHADE:路径覆盖位置着色）
  返 回 值：
  说    明：
***************************************************************************/
void print_array(const arrays origin, int choice)  
{
	int x, y;
	cout << "  |  ";
	for (int i = 0; i < origin.cols; i++)
	{
		cout << i+1 << "  ";
	}
	cout << endl;
	cout << "--|--";
	cct_getxy(x, y);
	cct_showch(x, y, '-', 0, 7, 3 * origin.cols); //打印表框
	cout << endl;
	for (int i = 0; i < origin.rows; i++)
	{
		cout << char('A' + i) << " | ";
		for (int j = 0; j < origin.cols; j++)
		{
			cout << " ";
			if (choice == BALL_SHADE)//有球的地方着色
			{
				if (origin.record[i][j]) {
					cct_setcolor(14, origin.record[i][j]-1);
					cout << origin.record[i][j];
					cct_setcolor();
				}
				else
					cout << '0';
			}
			else if (choice == PATH)//打印路径
			{
				if (origin.path[i][j] == -1)
					cout << "*";
				else
					cout << "0";
			}
			else if(choice==PATH_SHADE)//路径覆盖位置着色
			{
				if (origin.path[i][j] == -1)
					cct_setcolor(14, 11);
				cout << origin.record[i][j];
				cct_setcolor();
			}
			cout << " ";
		}
		cout << endl;
	}
}
/***************************************************************************
  函数名称：
  功    能：输入移动指令
  输入参数：pos &start：起始位置结构体的引用   pos &end：终点位置结构体的引用
		   const arrays origin:只读的记录内部数组的自定义结构体类型 
  返 回 值：
  说    明：
***************************************************************************/
void move_input(pos &start, pos &end,const arrays origin)
{
	char s[50];
	int x, y,target=0;//存储输入坐标,traget控制输入的是起点还是终点
	bool ok;//ok判断输入是否成功
	while (1) {
		cout << "请以字母+数字的形式[例：c2]输入要移动球的";
		cout << (target ? "目的" : "矩阵");
		cout<< "坐标:";
		cct_getxy(x, y);//获取位置
		while (1)
		{
			ok = 0;
			cin >> s;
			if (s[0] >= 'a' && s[0] <= 'a' + origin.rows - 1)//大小写去敏
				s[0] += 'A' - 'a';
			if (strlen(s) == 2 && (s[0] >= 'A' && s[0] <= 'A' + origin.rows - 1) && (s[1] >= '1' && s[1] <= '1' + origin.cols - 1))
			{
				/*target=0，输入起点，要求起点非空；target=1,输入终点，要求终点为空*/
				if (target!=(origin.record[s[0] - 'A'][s[1] - '1']!=0)) {
					if (target == 0) {
						start.row = s[0] - 'A';
						start.col = s[1] - '1';
					}
					else{
						end.row = s[0] - 'A';
						end.col = s[1] - '1';
					}
					target++;
					cout << "输入为" << s[0] << "行" << s[1] << "列"<<endl;
					ok = 1;
					break;
				}
				cout <<( target ? "起始位置非空" : "目标位置为空");
				cout<<",请重新输入.\n";
				break;
			}
			cout << "输入错误，请重新输入\n";
			cct_showch(x, y, ' ', 0, 7, 50);
			cct_gotoxy(x, y);
		}//内部输入错误的while
		if (ok&&target==2)//两个指令都输入成功输入则退出
			break;
	}//外层输入两个正确指令的while
}

/***************************************************************************
  函数名称：
  功    能：打印接下来的三个球
  输入参数：int *next:  存储下一次添加的三个球 int score：此次移动获得的分数
           bool success： 此次移动是否成功
  返 回 值：
  说    明：不得分且此次移动成功才对next数组进行更新
***************************************************************************/
void print_next_three(int* next3,int score,bool success)
{
	srand((unsigned)time(NULL));
	cout << "\n下3个彩球的颜色分别是：";
	for (int i = 0; i < 3; i++)
	{
		if (score == 0&&success==1) {
			next3[i] = rand() % 7 + 1;
		}
		cout << next3[i] << ' ';
	}
	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：打印球移动的路径
  输入参数：arrays origin :记录内部数组的自定义结构体类型 
           pos start：起始位置 pos end：终点位置
  返 回 值：
  说    明：找到路径打印，找不到给出提示
***************************************************************************/
void print_path(arrays origin,pos start,pos end)
{
	if (find_path(origin, start, end)) {
		cout << endl;
		cout << "查找结果数组：\n";
		print_array(origin, PATH);
		cout << endl << endl;
		cout << "移动路径（不同色标识）：\n";
		print_array(origin, PATH_SHADE);
	}
	else
		cout << "无法找到移动路径" << endl;
	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：打印球移动后更新的数组和得分
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
		   int score: 移动这一次的分数 int total_score:累计的总分
  返 回 值：
  说    明：
***************************************************************************/
void print_after_move(const arrays  origin,int score,int total_score)
{
	cout << "\n移动后的数组" << endl;
	print_array(origin, BALL_SHADE);
	cout << endl;
	cout << "本次得分：" << score << " 总得分：" << total_score<<endl<<endl;
}

/***************************************************************************
  函数名称：
  功    能：完成内部数组实现的函数调用
  输入参数：arrays origin :记录内部数组的自定义结构体类型的引用 int choice:功能选项的选择
  返 回 值：
  说    明：将2，3选项相结合，统一到内部数组方式游戏
***************************************************************************/
void base_version_game(arrays origin,int choice)
{
	int total_score = 0,score=0;
	pos start, end;
	bool success = 1;
	int next3[3],remove[8];//下一次出现的3个，消除掉的球（没用，为了满足函数参数要求，与图形界面函数统一）
	while (!game_over(origin)) {
		cout << endl << "当前数组：" << endl;
		print_array(origin, BALL_SHADE);
		print_next_three(next3,score,success);
		move_input(start, end, origin);
		if (choice == 2)
			print_path(origin, start, end);
		else {
			if (find_path(origin, start, end)) {
				score = move(origin, next3, start, end, remove);
				total_score += score;
				print_after_move(origin, score, total_score);
				success = 1;
			}
			else
				cout << "无法找到移动路径" << endl;
			success = 0;
		}
		if (choice == 2)
			break;
	}
	if (choice == 3) {
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << "\n游戏结束!!!" << endl;
		cct_setcolor();
	}
}