#include<iostream>
#include<conio.h>
#include"cmd_console_tools.h"
#include<Windows.h>
#include"90-b2.h"
#include<iomanip>

using namespace std;
/*[7*7]情况下的控制台长宽*/
const int console_cols = 35;
const int console_cols_complete = 70;
const int console_rows_no_line = 13;
const int console_rows_with_line = 19;
const int console_rows_complete = 23;
/*字体长度设置*/
const int console_fonthigh = 36;
const int console_fonthigh_complete = 24;
/*相关表框的位置设置*/
const int tipy = 21;
const int boardx=40;
const int scorey = 1;
const int next3y = 5;
const int recordy = 9;

/***************************************************************************
  函数名称：
  功    能: 输入回车
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void enter_input()
{
	cout << "\n按回车键显示图形...";
	while (1)
	{
		int huiche = _getch();
		if (huiche == '\r')
			break;
	}
}

/***************************************************************************
  函数名称：
  功    能：打印球移动的路径
  输入参数：arrays origin :记录内部数组的自定义结构体类型
		   pos start：起始位置 pos end：终点位置
  返 回 值：
  说    明：找到路径打印，找不到给出提示
***************************************************************************/
void init_console(arrays origin,int choice)
{
	int rows, cols,font;
	if (choice == 4)
	{
		cols = console_cols;
		rows = console_rows_no_line+origin.rows-7;
		font = console_fonthigh;
	}
	else if (choice == 5||choice==6)
	{
		cols = console_cols;
		rows = console_rows_with_line+2*(origin.rows-7);
		font = console_fonthigh;
	}
	else if(choice==7)
	{
		cols = console_cols_complete;
		rows = console_rows_complete;
		font=console_fonthigh_complete;
	}
	cct_setconsoleborder(cols, rows);
	cct_setfontsize("新宋体", font, 0);
	cout << "屏幕：" << rows << "行" << cols << "列";
	if (choice == 6 || choice == 7)
		cout << "(右键退出)";
	cout<< endl;
	
}

/***************************************************************************
  函数名称：
  功    能：画出没有分隔线的框架和初始的5个球
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
  返 回 值：
  说    明：
***************************************************************************/ 
void draw_no_line(const arrays origin)
{
	cct_setcolor(15, 0);
	int x, y;
	cout << "┏";
	cct_getxy(x, y);
	cct_showstr(x, y, "━", COLOR_HWHITE, COLOR_BLACK, origin.cols);
	cout << "┓" << endl;            //画上表框
	for (int i = 0; i < origin.rows; i++)
	{
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃";
		for (int j = 0; j < origin.cols; j++)
		{
			if (origin.record[i][j] == 0)
				cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
			else {
				cct_setcolor(COLOR_HWHITE, origin.record[i][j]+6);
			}
			cout << "●";
		}
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "┃" << endl;
	}
	cout << "┗";
	cct_getxy(x, y);
	cct_showstr(x, y, "━", COLOR_HWHITE, COLOR_BLACK,  origin.cols);
	cout << "┛" << endl;            //画下表框
	cct_setcolor();         //颜色修正
}

/***************************************************************************
  函数名称：
  功    能：画出有分隔线的框架和初始的60%的球
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
  返 回 值：
  说    明：
***************************************************************************/
void draw_with_line(const arrays origin)
{
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┏";
	for (int i = 0; i < origin.cols - 1; i++)
	{
		cout << "━┳";
	}
	cout << "━┓" << endl;            //画上表框
	for (int i = 0; i < 2*origin.rows-1; i++)
	{
		if (i % 2 == 0)
			cout << "┃";
		else 
			cout << "┣";
		for (int j = 0; j < origin.cols; j++)
		{
			if (i % 2 == 0) {
				if (origin.record[i / 2][j] != 0)
					cct_setcolor(COLOR_HWHITE, origin.record[i / 2][j] + 6);//注意颜色是数值+6
				else
					cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
				cout << "●";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "┃";
			}
			else {
				if (j < origin.cols - 1)
					cout << "━╋";
				else
					cout << "━┫";
			}
		}
		cout << endl;	
	}
	cout << "┗";
	for (int i = 0; i < origin.cols - 1; i++)
		cout << "━┻";
	cout << "━┛" << endl;           //画下表框
	cct_setcolor();         //颜色修正
}

/***************************************************************************
  函数名称：
  功    能：画出完整游戏版的基本图形
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
  返 回 值：
  说    明：draw_next3放在了游戏总体实现的那个函数中，便于数值交换
***************************************************************************/
void draw_complete(const arrays origin)
{
	int remove[8] = { 0 };//仅初始化用
	draw_with_line(origin);
	draw_score(0);
	draw_record(origin, remove);
}
	
/***************************************************************************
  函数名称：
  功    能：画出得到的总分框
  输入参数：int double：总分
  返 回 值：
  说    明：
***************************************************************************/
void draw_score(int score)
{
	cct_gotoxy(boardx, scorey);
	cct_setcolor(COLOR_HWHITE, 0);
	cout << "┏";
	for (int i = 0; i < 5; i++)
		cout << "━";
	cout << "┓";
	cct_gotoxy(boardx, scorey + 1);
	cout << "┃得分：" <<setw(4)<<setiosflags(ios::left)<<score << "┃";;
	cout<<resetiosflags(ios::left);//消去左对齐
	cct_gotoxy(boardx, scorey + 2);
	cout << "┗";
	for (int i = 0; i <5; i++)
		cout << "━";
	cout << "┛";
}

/***************************************************************************
  函数名称：
  功    能：画出各种球消去历史的记录
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
           int remove：记录各种球消去情况的数组
  返 回 值：
  说    明：
***************************************************************************/
void draw_record(const arrays origin,int* remove)
{
	/*统计各种颜色的数量*/
	double num[8]={0};
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			num[origin.record[i][j]]++;
		}
	}
	cct_gotoxy(boardx,recordy);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┏";
	for (int i = 0; i < 12; i++)
		cout << "━";
	cout << "┓";            //画上表框
	for (int i = 0; i <= 7; i++)
	{
		cct_gotoxy(boardx, recordy + i + 1);
		cout << "┃";
		if (i == 0)
			cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
		else
		    cct_setcolor(COLOR_HWHITE, i+6);
		cout << "●";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << ":" << setfill('0') << setw(2) << int(num[i]) << "/" << "(" << setfill(' ') << setiosflags(ios::fixed)
			<< setprecision(2) <<setw(5)<< (num[i] / (origin.rows * origin.cols)*100) << "%) " << "消除-" << setw(4) << setiosflags(ios::left)
			<< remove[i] << "┃";
		cout << resetiosflags(ios::left);//消去左对齐
	}
	cct_gotoxy(boardx, recordy + 9);//画下表框
	cout << "┗";
	for (int i = 0; i <12; i++)
		cout << "━";
	cout << "┛";
}

/***************************************************************************
  函数名称：
  功    能：画出接下来三个要产生的球
  输入参数：int *next3,指向存储接下来三个球的数组的指针
  返 回 值：
  说    明：
***************************************************************************/
void draw_next_three(int* next3)
{
	srand((unsigned)time(NULL));
	cct_gotoxy(boardx, next3y);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "┏";
	for (int i = 0; i < 2; i++)
		cout << "━┳";
	cout << "━┓";
	cct_gotoxy(boardx, next3y + 1);
	cout << "┃";
	for (int i = 0; i < 3; i++)
	{
		next3[i] = rand() % 7 + 1;
		cct_setcolor(COLOR_HWHITE, next3[i] + 6);
		cout << "●";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout<< "┃";
	}
	cct_gotoxy(boardx, next3y + 2);
	cout << "┗";
	for (int i = 0; i < 2; i++)
		cout << "━┻";
	cout << "━┛";
}

/***************************************************************************
  函数名称：
  功    能：改变选中位置的色块颜色
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
		   int row： 该色块的行  int col：该色块的列
		   bool choose：是否选中
  返 回 值：
  说    明：choose为1，则将色块置青色阴影，为0，则消去之前选中的色块的青色阴影
***************************************************************************/
void change_shade(const arrays origin,int row,int col,bool choose)
{
	int fg_color;
	cct_gotoxy(4*col+2,2*row+2);//row，col统一为从0开始
	if (origin.record[row][col] != 0)
		fg_color = origin.record[row][col] + 6;
	else
		fg_color = COLOR_HWHITE;
	if (choose == 1)
		cct_setcolor(COLOR_CYAN, fg_color);
	else
		cct_setcolor(COLOR_HWHITE, fg_color);
	cout << "●";
}

/***************************************************************************
  函数名称：
  功    能：画出各种球移动的路径过程
  输入参数：const arrays origin :只读的记录内部数组的自定义结构体类型
		   pos start：移动的起始位置       pos end:移动的终点位置
  返 回 值：
  说    明：通过find_path函数标记的path数组中的路径来移动
***************************************************************************/
void draw_path(const arrays origin,pos start,pos end)
{
	int dr[4] = { 0,0,1,-1 };
	int dc[4] = { 1,-1,0,0 };
	int vis[MAX_ROW][MAX_COL]={0};
	vis[start.row][start.col] = 1;
	pos temp = start;
	while (temp.row != end.row||temp.col!=end.col) {
		for (int i = 0; i < 4; i++)
		{
			if (origin.path[temp.row + dr[i]][temp.col + dc[i]]==-1&&vis[temp.row + dr[i]][temp.col + dc[i]]==0)
			{
				vis[temp.row + dr[i]][temp.col + dc[i]] = 1;//访问过进行标记
				cct_gotoxy(2 + 4 * temp.col, 2 + 2 * temp.row);
				cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
				cout << "  ";
				cct_gotoxy(2 + 4*temp.col+2*dc[i], 2 + 2 * temp.row+dr[i]);
				cct_setcolor(COLOR_CYAN, origin.record[start.row][start.col] + 6);
				cout << "●";
				Sleep(100);
				cct_gotoxy(2 + 4 * temp.col + 2*dc[i], 2 + 2 * temp.row + dr[i]);
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				if (i == 0 || i == 1)//水平移动
					cout << "┃";
				else                 //纵向移动
					cout << "━";
				cct_gotoxy(2 + 4 * temp.col + 4*dc[i], 2 + 2 * temp.row + 2*dr[i]);
				cct_setcolor(COLOR_CYAN, origin.record[start.row][start.col] + 6);
				cout << "●";
				Sleep(100);
				temp.row = temp.row + dr[i];//临时行和列更新
				temp.col = temp.col + dc[i];
				break;
			}
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：画出整个一次移动的过程
  输入参数：arrays &origin :记录内部数组的自定义结构体类型的引用
		   pos start：移动的起始位置       pos end:移动的终点位置
		   int choice： 功能选项    int *next3：放置下一次添加的三个球的数组的指针
		   int remove：记录各种球消去情况的数组   bool &success :移动是否成功的引用
  返 回 值： 此次移动获得的分数
  说    明：
***************************************************************************/
int draw_move(arrays &origin,pos start,pos end,int choice,int *next3,int *remove,bool &success)
{
	int score=0;
	if (find_path(origin, start, end))//可以移动成功
	{
		if (choice == 6)
			cct_gotoxy(0, 2*origin.rows + 2);
		else
			cct_gotoxy(0, tipy);
		cct_setcolor();
		cout << "[提示] 可以从" << "[" << char('A' + start.row) << start.col+1 << "]" << "移动到"
			<< "[" << char('A' + end.row) << end.col+1 << "]           ";
		draw_path(origin, start, end);//绘制移动路径
		if (choice == 7) {
			score=move(origin, next3, start, end,remove);//改变内部数组
			cct_gotoxy(0, 1);
			draw_with_line(origin);//更新数组
		}
		success = 1;
	}
	else {
		if (choice == 6)
			cct_gotoxy(0, 2*origin.rows + 2);
		else
			cct_gotoxy(0, tipy);
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "[错误] 无法从" << "[" << char('A' + start.row) << start.col+1 << "]" << "移动到"
			<< "[" << char('A' + end.row) << end.col+1 << "]           ";
		Sleep(500);//停留一段时间
		cct_setcolor();
		success=0;//用来标记没有移动成功，不需要产生新的三个球
	}
	return score;
}

/***************************************************************************
  函数名称：
  功    能：cmd界面图形版的完整实现
  输入参数：arrays origin :记录内部数组的自定义结构体类型
		   int choice： 功能选项  
  返 回 值： 
  说    明：此函数将功能项6和7结合
***************************************************************************/
void  console_version_game(arrays origin,int choice)
{
	int total_score = 0,score=0;
	bool success = 1;
	int next3[3],remove[8]={0};
	cct_enable_mouse();//允许鼠标
	cct_setcursor(CURSOR_INVISIBLE);//隐藏光标
	int MX = 0, MY = 0, MAction, keycode1, keycode2,temp_row=0,temp_col=0;
	bool choose=0;
	draw_next_three(next3);   //先画将要生成的三个
	while (!game_over(origin))
	{
		if (cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2) == CCT_MOUSE_EVENT)  //获取鼠标的事件
		{
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK)//右击
				break;
			else if (MAction == MOUSE_ONLY_MOVED)   //仅移动
			{
				if ((MX%4==2||MX%4==3)&&MX<4*origin.cols && MY%2==0&&MY<=2*origin.rows+1&&MY>0)
				{
					if (choice == 6)
						cct_gotoxy(0, 2*origin.rows + 2);
					else
						cct_gotoxy(0, tipy);
					cct_setcolor();
					cout << "[当前鼠标] " << char('A' + MY/2-1) << "行" << MX/4+1 << "列                             ";
				}
			}
			else if (MAction == MOUSE_LEFT_BUTTON_CLICK&&(MX % 4 == 2 || MX % 4 == 3) && MX < 4 * origin.cols 
				     && MY % 2 == 0 && MY <= 2 * origin.rows + 1 && MY>0)   //在合理位置点击左键
			{
				if (origin.record[MY / 2 - 1][MX / 4]) //选中非空白
				{
					change_shade(origin,temp_row,temp_col,0);//消除上一次选中的
					change_shade(origin,MY / 2-1, MX / 4 ,1);//标记这一次选的
					temp_row = MY / 2-1;
					temp_col = MX / 4;          //临时行列更新
					choose = 1;//标记起点已经选中
				}
				else {                              //选中空白
					if (choose == 1) {
						pos start = { temp_row,temp_col };
						pos end = { MY / 2-1 ,MX / 4 };
						score=draw_move(origin,start, end,choice,next3,remove,success);//对6，7进行区分
						if (success) {
							if (origin.record[end.row][end.col] == 0)//被消去了
								choose = 0;
							else
								change_shade(origin, end.row, end.col, 1);//没有消去的话，重新为移动的球附上阴影
						}
						else
							continue;
						if (choice == 6)//选项6在此退出
							break;
						total_score += score;
						if(score==0&&success)//不得分但是成功移动，更新下三个球
							draw_next_three(next3);
						if(score!=0)            //更新分数
						    draw_score(total_score);
						draw_record(origin, remove);
						if (success) {
							temp_row = MY / 2 - 1;//更新临时位置
							temp_col = MX / 4;
						}
					}
				}
			}
		}
	}
	if (choice == 7) {
		cct_gotoxy(0, tipy - 1);
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << "游戏结束！！！总得分："<<total_score;
	}
	cct_disable_mouse();//鼠标清除
	cct_setcursor(CURSOR_VISIBLE_NORMAL);//光标恢复
	if (choice == 6)
		cct_gotoxy(0, 2 * origin.rows + 1);
	else
		cct_gotoxy(0, tipy-1);
}