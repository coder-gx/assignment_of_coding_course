#include<iostream>
#include"90-b2.h"
#include<climits>
#include"cmd_console_tools.h"
#include<Windows.h>
#include<ctime>
#include<cstring>
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ������к���
  ����������к��е�����
  �� �� ֵ��
  ˵    ������������к��е�ֵͨ�����ô����ṹ��origin
***************************************************************************/
void row_col_input(int &row, int &col)
{
	while (1)
	{
		cout << "����������(7-9):\n";  
		cin >> row;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');//��ջ�����
			continue;
		}
		if (row >= 7 && row<=9)
			break;
	}
	while (1)
	{
		cout << "����������(7-9):\n";
		cin >> col;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');//��ջ�����
			continue;
		}
		if (col >= 7 && col <= 9)
			break;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�һ�����������������end����Сд�����У����¿�ʼ��һ�ֽ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void end_input()
{
	cct_setcolor();
	cout << "\n��С�����,������End����...";  //������ʾ
	int x, y;
	cct_getxy(x, y);//��ȡλ��
	while (1)
	{
		char end[50];
		cin >> end;
		if (strlen(end) == 3 && (end[0] == 'e' || end[0] == 'E') && (end[1] == 'n' || end[1] == 'N') && (end[2] == 'd' || end[2] == 'D'))
			break;
		cout << "�����������������\n";
		cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 50);
		cct_gotoxy(x, y);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ڲ������ʼ��
  ���������arrays &origin:��¼�ڲ�������Զ���ṹ�����͵����� int choice������ѡ��
  �� �� ֵ��
  ˵    ��������Ҫ��ʼ���ڲ����飬���ı䣬������
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
	/*�������record�е�n����ȷ�����ظ���ͬһλ������*/
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
  �������ƣ�
  ��    �ܣ�Ѱ������ƶ�·������¼
  ���������arrays &origin:��¼�ڲ�������Զ���ṹ�����͵����� 
           pos start:��ʼλ��      pos end:�յ�λ��     
  �� �� ֵ���ܷ��ҵ�·�����ҵ�����true���Ҳ�������false
  ˵    ������������origin�е�path�����¼·��
***************************************************************************/
bool find_path(arrays& origin, pos start, pos end)
{
	/*����bfs�㷨Ѱ������ƶ�·����������������ģ����У�û�в���STL*/
	int dr[4] = { 0,0,1,-1 };
	int dc[4] = { 1,-1,0,0 };
	int vis[MAX_ROW][MAX_COL];//������¼ÿ��λ�õ����ٲ���
	pos q[MAX_ROW * MAX_COL*4];//ģ�����
	memset(vis, 0, sizeof(vis));
	int head = 0, tail = 1, step[MAX_ROW * MAX_COL*4];//��¼����
	q[head].row = start.row;
	q[head].col = start.col;
	step[0] = 0;
	while (head < tail)//���зǿ�
	{
		for (int i = 0; i < 4; i++)//�����ĸ�����
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
	if (vis[end.row][end.col])//�ҵ���·��,���л��ݱ�ǣ���˳�����ݼ���·�����ص���㼴��
	{
		pos p = { end.row,end.col };
		origin.path[end.row][end.col] = -1;
		while (p.row != start.row || p.col != start.col) {
			for (int i = 0; i < 4; i++)//�����ĸ�������һ��Ҫ����Խ�磬�����˻�ȥ����������һ
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
	else//û���ҵ�
		return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������ƶ���ʼ�գ��ı��ڲ����飬�ж��Ƿ���ȥ������ȥ�����µ�����
  ���������arrays &origin:��¼�ڲ�������Զ���ṹ�����͵�����
           int *next3: �²����������������ɫ����
		   pos start:��ʼλ��      pos end:�յ�λ��
		   int *remove:��¼�����ĸ���ɫ�������
  �� �� ֵ���˴��ƶ��ķ���
  ˵    �����˺����������ɵ�����λ�õ�����ֽ�����һ���Ƿ������ȥ���жϣ�
            ��ȷ�����Ľ�����󲻻��п���ȥ�����
***************************************************************************/
int move(arrays &origin,int *next3,pos start,pos end,int *remove)
{
	memset(origin.path, 0, sizeof(origin.path));//��path�ļ�¼ɾ����Ϊ�����׼��
	origin.record[end.row][end.col]=origin.record[start.row][start.col];
	origin.record[start.row][start.col] = 0;
	int line=judge_five(origin);
	int plus = 0;
	if (line == 0)//û��5������һ��ģ����²�������
	{
		srand((unsigned)time(0));
		//ע�������ʣ�Ĳ���������ʱ����game_overΪ�ж����ݣ�������ѭ��
		for (int i = 0; i < 3&&(!game_over(origin)); i++)
		{
			int x, y;
			if (origin.record[x = rand() % origin.rows][y = rand() % origin.cols] == 0)
				origin.record[x][y] = next3[i];
			else
				i--;
		}
		plus = judge_five(origin);//�����ɺ��ٴ��ж�
	}
	/*����5�����߻����²���������λ�ô���5����������*/
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
	memset(origin.path, 0, sizeof(origin.path));//��path�ļ�¼ɾ����Ϊ��һ�α����׼��
	return (line+plus==0 ? 0 : (5 * (line+plus) - 1) * (5 * (line+plus) - 2));//���ط���
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ж��Ƿ��������������ȥ�����
  ���������arrays &origin:��¼�ڲ�������Զ���ṹ�����͵�����
  �� �� ֵ������������5����Ķ������ظ�����
  ˵    ������������origin�е�path�����¼Ҫ������λ��
***************************************************************************/
int judge_five(arrays &origin)
{
	int line=0;
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			if (origin.record[i][j] != 0) {
				/*����*/
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
				/*����*/
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
				/*б��*/
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
				/*��б��*/
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
  �������ƣ�
  ��    �ܣ��ж���Ϸ�Ƿ����
  ���������const arrays origin:ֻ���ļ�¼�ڲ�������Զ���ṹ������
  �� �� ֵ����Ϸ�Ƿ��������������true����֮����false
  ˵    ����
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

