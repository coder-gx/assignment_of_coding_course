#include<iostream>
#include"90-b2.h"
#include<climits>
#include"cmd_console_tools.h"
#include<Windows.h>
#include<ctime>
#include<cstring>
using namespace std;

/***************************************************************************
  函数名称：
  功    能：输入行和列
  输入参数：行和列的引用
  返 回 值：
  说    明：将输入的行和列的值通过引用传给结构体origin
***************************************************************************/
void row_col_input(int &row, int &col)
{
	while (1)
	{
		cout << "请输入行数(7-9):\n";  
		cin >> row;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');//清空缓冲区
			continue;
		}
		if (row >= 7 && row<=9)
			break;
	}
	while (1)
	{
		cout << "请输入列数(7-9):\n";
		cin >> col;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');//清空缓冲区
			continue;
		}
		if (col >= 7 && col <= 9)
			break;
	}
}

/***************************************************************************
  函数名称：
  功    能：一个功能项结束后，输入end（大小写不敏感）重新开始下一轮进程
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void end_input()
{
	cct_setcolor();
	cout << "\n本小题结束,请输入End继续...";  //结束提示
	int x, y;
	cct_getxy(x, y);//获取位置
	while (1)
	{
		char end[50];
		cin >> end;
		if (strlen(end) == 3 && (end[0] == 'e' || end[0] == 'E') && (end[1] == 'n' || end[1] == 'N') && (end[2] == 'd' || end[2] == 'D'))
			break;
		cout << "输入错误，请重新输入\n";
		cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 50);
		cct_gotoxy(x, y);
	}
}

/***************************************************************************
  函数名称：
  功    能：内部数组初始化
  输入参数：arrays &origin:记录内部数组的自定义结构体类型的引用 int choice：功能选项
  返 回 值：
  说    明：这里要初始化内部数组，即改变，用引用
***************************************************************************/
void init_array(arrays &origin,int choice)
{
	int n=0;
	if (choice == 1||choice==3||choice==4||choice==5||choice==7)
		n = 5;
	else if (choice == 2||choice==6)
		n = int(0.6 * origin.rows * origin.cols);
	memset(origin.record, 0, sizeof(origin.record));
	memset(origin.path, 0, sizeof(origin.path));
	/*随机生成record中的n个球，确保不重复在同一位置生成*/
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		int x, y;
		if (!origin.record[x = rand() % origin.rows][y = rand() % origin.cols])
			origin.record[x][y] = rand() % 7 + 1;
		else
			i--;
	}
}

/***************************************************************************
  函数名称：
  功    能：寻找最短移动路径并记录
  输入参数：arrays &origin:记录内部数组的自定义结构体类型的引用 
           pos start:起始位置      pos end:终点位置     
  返 回 值：能否找到路径，找到返回true，找不到返回false
  说    明：本函数用origin中的path数组记录路径
***************************************************************************/
bool find_path(arrays& origin, pos start, pos end)
{
	/*采用bfs算法寻找最短移动路径，其中利用数组模拟队列，没有采用STL*/
	int dr[4] = { 0,0,1,-1 };
	int dc[4] = { 1,-1,0,0 };
	int vis[MAX_ROW][MAX_COL];//用来记录每个位置的最少步数
	pos q[MAX_ROW * MAX_COL*4];//模拟队列
	memset(vis, 0, sizeof(vis));
	int head = 0, tail = 1, step[MAX_ROW * MAX_COL*4];//记录步数
	q[head].row = start.row;
	q[head].col = start.col;
	step[0] = 0;
	while (head < tail)//队列非空
	{
		for (int i = 0; i < 4; i++)//遍历四个方向
		{
			int x = q[head].row + dr[i];
			int y = q[head].col + dc[i];
			if (x >= 0 && x < origin.rows && y >= 0 && y < origin.cols && origin.record[x][y] == 0 && vis[x][y] == 0)
			{
				q[tail].row = x;
				q[tail].col = y;
				step[tail] = step[head] + 1;
				vis[x][y] = step[tail];
				tail++;
			}
		}
		head++;
	}
	if (vis[end.row][end.col])//找到了路径,进行回溯标记，按顺步数递减的路径返回到起点即可
	{
		pos p = { end.row,end.col };
		origin.path[end.row][end.col] = -1;
		while (p.row != start.row || p.col != start.col) {
			for (int i = 0; i < 4; i++)//遍历四个方向，下一步要求不能越界，不能退回去，按步数减一
			{
				if ((p.row + dr[i]) >= 0 && (p.row + dr[i]) < origin.rows && (p.col + dc[i]) >= 0 && (p.col + dc[i]) < origin.cols
					&& vis[p.row + dr[i]][p.col + dc[i]] == vis[p.row][p.col] - 1
					&&(origin.record[p.row+dr[i]][p.col+dc[i]]==0|| (p.row+dr[i] == start.row && p.col+dc[i] == start.col)))
				{
					p.row = p.row + dr[i];
					p.col = p.col + dc[i];
					origin.path[p.row][p.col] = -1;
					break;
				}
			}
		}
		return 1;
	}
	else//没有找到
		return 0;
}

/***************************************************************************
  函数名称：
  功    能：根据移动的始终，改变内部数组，判断是否消去，不消去产生新的三个
  输入参数：arrays &origin:记录内部数组的自定义结构体类型的引用
           int *next3: 新产生的下三个球的颜色数组
		   pos start:起始位置      pos end:终点位置
		   int *remove:记录消除的各颜色球的数量
  返 回 值：此次移动的分数
  说    明：此函数对新生成的三个位置的球后又进行了一次是否可以消去的判断，
            以确保最后的结果矩阵不会有可消去的情况
***************************************************************************/
int move(arrays &origin,int *next3,pos start,pos end,int *remove)
{
	memset(origin.path, 0, sizeof(origin.path));//对path的记录删除，为标记作准备
	origin.record[end.row][end.col]=origin.record[start.row][start.col];
	origin.record[start.row][start.col] = 0;
	int line=judge_five(origin);
	int plus = 0;
	if (line == 0)//没有5个连在一起的，则新产生三个
	{
		srand((unsigned)time(0));
		//注意在最后剩的不足三个的时候以game_over为判断依据，避免死循环
		for (int i = 0; i < 3&&(!game_over(origin)); i++)
		{
			int x, y;
			if (origin.record[x = rand() % origin.rows][y = rand() % origin.cols] == 0)
				origin.record[x][y] = next3[i];
			else
				i--;
		}
		plus = judge_five(origin);//新生成后再次判断
	}
	/*对有5个连线或者新产生的三个位置凑齐5个进行消除*/
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			if (origin.path[i][j] == -1) {
				remove[origin.record[i][j]]++;
				origin.record[i][j] = 0;
			}
		}
	}
	memset(origin.path, 0, sizeof(origin.path));//对path的记录删除，为下一次标记作准备
	return (line+plus==0 ? 0 : (5 * (line+plus) - 1) * (5 * (line+plus) - 2));//返回分数
}

/***************************************************************************
  函数名称：
  功    能：判断是否有连续五个可消去的情况
  输入参数：arrays &origin:记录内部数组的自定义结构体类型的引用
  返 回 值：消除的连续5个球的对数，重复计数
  说    明：本函数用origin中的path数组记录要消除的位置
***************************************************************************/
int judge_five(arrays &origin)
{
	int line=0;
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			if (origin.record[i][j] != 0) {
				/*横向*/
				if (j <= origin.cols - 5) {
					bool mark = 1;
					for (int k = 1; k < 5; k++)
					{
						if (origin.record[i][j] != origin.record[i][j + k])
							mark = 0;
					}
					if (mark) {
						for (int k = 0; k < 5; k++)
							origin.path[i][j + k] = -1;
						line++;
					}
				}
				/*纵向*/
				if (i <= origin.rows - 5) {
					bool mark = 1;
					for (int k = 1; k < 5; k++)
					{
						if (origin.record[i][j] != origin.record[i + k][j])
							mark = 0;
					}
					if (mark) {
						for (int k = 0; k < 5; k++)
							origin.path[i + k][j] = -1;
						line++;
					}
				}
				/*斜向*/
				if (i <= origin.rows - 5 && j <= origin.cols - 5) {
					bool mark = 1;
					for (int k = 1; k < 5; k++)
					{
						if (origin.record[i][j] != origin.record[i + k][j + k])
							mark = 0;
					}
					if (mark) {
						for (int k = 0; k < 5; k++)
							origin.path[i + k][j + k] = -1;
						line++;
					}
				}
				/*反斜向*/
				if (i >= 4 && j <= origin.cols - 5) {
					bool mark = 1;
					for (int k = 1; k < 5; k++)
					{
						if (origin.record[i][j] != origin.record[i-k][j + k])
							mark = 0;
					}
					if (mark) {
						for (int k = 0; k < 5; k++)
							origin.path[i-k][j + k] = -1;
						line++;
					}
				}
			}
		}
	}
	return line;
}

/***************************************************************************
  函数名称：
  功    能：判断游戏是否结束
  输入参数：const arrays origin:只读的记录内部数组的自定义结构体类型
  返 回 值：游戏是否结束，结束返回true，反之返回false
  说    明：
***************************************************************************/
bool game_over(const arrays origin)
{
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			if (origin.record[i][j] == 0)
				return 0;
		}
	}
	return 1;
}

