#include<iostream>
#include<conio.h>
#include"cmd_console_tools.h"
#include<Windows.h>
#include"90-b2.h"
#include<iomanip>

using namespace std;
/*[7*7]����µĿ���̨����*/
const int console_cols = 35;
const int console_cols_complete = 70;
const int console_rows_no_line = 13;
const int console_rows_with_line = 19;
const int console_rows_complete = 23;
/*���峤������*/
const int console_fonthigh = 36;
const int console_fonthigh_complete = 24;
/*��ر���λ������*/
const int tipy = 21;
const int boardx=40;
const int scorey = 1;
const int next3y = 5;
const int recordy = 9;

/***************************************************************************
  �������ƣ�
  ��    ��: ����س�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void enter_input()
{
	cout << "\n���س�����ʾͼ��...";
	while (1)
	{
		int huiche = _getch();
		if (huiche == '\r')
			break;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ���ƶ���·��
  ���������arrays origin :��¼�ڲ�������Զ���ṹ������
		   pos start����ʼλ�� pos end���յ�λ��
  �� �� ֵ��
  ˵    �����ҵ�·����ӡ���Ҳ���������ʾ
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
	cct_setfontsize("������", font, 0);
	cout << "��Ļ��" << rows << "��" << cols << "��";
	if (choice == 6 || choice == 7)
		cout << "(�Ҽ��˳�)";
	cout<< endl;
	
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����û�зָ��ߵĿ�ܺͳ�ʼ��5����
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
  �� �� ֵ��
  ˵    ����
***************************************************************************/ 
void draw_no_line(const arrays origin)
{
	cct_setcolor(15, 0);
	int x, y;
	cout << "��";
	cct_getxy(x, y);
	cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK, origin.cols);
	cout << "��" << endl;            //���ϱ��
	for (int i = 0; i < origin.rows; i++)
	{
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "��";
		for (int j = 0; j < origin.cols; j++)
		{
			if (origin.record[i][j] == 0)
				cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
			else {
				cct_setcolor(COLOR_HWHITE, origin.record[i][j]+6);
			}
			cout << "��";
		}
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "��" << endl;
	}
	cout << "��";
	cct_getxy(x, y);
	cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK,  origin.cols);
	cout << "��" << endl;            //���±��
	cct_setcolor();         //��ɫ����
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������зָ��ߵĿ�ܺͳ�ʼ��60%����
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_with_line(const arrays origin)
{
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "��";
	for (int i = 0; i < origin.cols - 1; i++)
	{
		cout << "����";
	}
	cout << "����" << endl;            //���ϱ��
	for (int i = 0; i < 2*origin.rows-1; i++)
	{
		if (i % 2 == 0)
			cout << "��";
		else 
			cout << "��";
		for (int j = 0; j < origin.cols; j++)
		{
			if (i % 2 == 0) {
				if (origin.record[i / 2][j] != 0)
					cct_setcolor(COLOR_HWHITE, origin.record[i / 2][j] + 6);//ע����ɫ����ֵ+6
				else
					cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
				cout << "��";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "��";
			}
			else {
				if (j < origin.cols - 1)
					cout << "����";
				else
					cout << "����";
			}
		}
		cout << endl;	
	}
	cout << "��";
	for (int i = 0; i < origin.cols - 1; i++)
		cout << "����";
	cout << "����" << endl;           //���±��
	cct_setcolor();         //��ɫ����
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����������Ϸ��Ļ���ͼ��
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
  �� �� ֵ��
  ˵    ����draw_next3��������Ϸ����ʵ�ֵ��Ǹ������У�������ֵ����
***************************************************************************/
void draw_complete(const arrays origin)
{
	int remove[8] = { 0 };//����ʼ����
	draw_with_line(origin);
	draw_score(0);
	draw_record(origin, remove);
}
	
/***************************************************************************
  �������ƣ�
  ��    �ܣ������õ����ֿܷ�
  ���������int double���ܷ�
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_score(int score)
{
	cct_gotoxy(boardx, scorey);
	cct_setcolor(COLOR_HWHITE, 0);
	cout << "��";
	for (int i = 0; i < 5; i++)
		cout << "��";
	cout << "��";
	cct_gotoxy(boardx, scorey + 1);
	cout << "���÷֣�" <<setw(4)<<setiosflags(ios::left)<<score << "��";;
	cout<<resetiosflags(ios::left);//��ȥ�����
	cct_gotoxy(boardx, scorey + 2);
	cout << "��";
	for (int i = 0; i <5; i++)
		cout << "��";
	cout << "��";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������ȥ��ʷ�ļ�¼
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
           int remove����¼��������ȥ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_record(const arrays origin,int* remove)
{
	/*ͳ�Ƹ�����ɫ������*/
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
	cout << "��";
	for (int i = 0; i < 12; i++)
		cout << "��";
	cout << "��";            //���ϱ��
	for (int i = 0; i <= 7; i++)
	{
		cct_gotoxy(boardx, recordy + i + 1);
		cout << "��";
		if (i == 0)
			cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
		else
		    cct_setcolor(COLOR_HWHITE, i+6);
		cout << "��";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << ":" << setfill('0') << setw(2) << int(num[i]) << "/" << "(" << setfill(' ') << setiosflags(ios::fixed)
			<< setprecision(2) <<setw(5)<< (num[i] / (origin.rows * origin.cols)*100) << "%) " << "����-" << setw(4) << setiosflags(ios::left)
			<< remove[i] << "��";
		cout << resetiosflags(ios::left);//��ȥ�����
	}
	cct_gotoxy(boardx, recordy + 9);//���±��
	cout << "��";
	for (int i = 0; i <12; i++)
		cout << "��";
	cout << "��";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������������Ҫ��������
  ���������int *next3,ָ��洢������������������ָ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void draw_next_three(int* next3)
{
	srand((unsigned)time(NULL));
	cct_gotoxy(boardx, next3y);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "��";
	for (int i = 0; i < 2; i++)
		cout << "����";
	cout << "����";
	cct_gotoxy(boardx, next3y + 1);
	cout << "��";
	for (int i = 0; i < 3; i++)
	{
		next3[i] = rand() % 7 + 1;
		cct_setcolor(COLOR_HWHITE, next3[i] + 6);
		cout << "��";
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout<< "��";
	}
	cct_gotoxy(boardx, next3y + 2);
	cout << "��";
	for (int i = 0; i < 2; i++)
		cout << "����";
	cout << "����";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ı�ѡ��λ�õ�ɫ����ɫ
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
		   int row�� ��ɫ�����  int col����ɫ�����
		   bool choose���Ƿ�ѡ��
  �� �� ֵ��
  ˵    ����chooseΪ1����ɫ������ɫ��Ӱ��Ϊ0������ȥ֮ǰѡ�е�ɫ�����ɫ��Ӱ
***************************************************************************/
void change_shade(const arrays origin,int row,int col,bool choose)
{
	int fg_color;
	cct_gotoxy(4*col+2,2*row+2);//row��colͳһΪ��0��ʼ
	if (origin.record[row][col] != 0)
		fg_color = origin.record[row][col] + 6;
	else
		fg_color = COLOR_HWHITE;
	if (choose == 1)
		cct_setcolor(COLOR_CYAN, fg_color);
	else
		cct_setcolor(COLOR_HWHITE, fg_color);
	cout << "��";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ƶ���·������
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
		   pos start���ƶ�����ʼλ��       pos end:�ƶ����յ�λ��
  �� �� ֵ��
  ˵    ����ͨ��find_path������ǵ�path�����е�·�����ƶ�
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
				vis[temp.row + dr[i]][temp.col + dc[i]] = 1;//���ʹ����б��
				cct_gotoxy(2 + 4 * temp.col, 2 + 2 * temp.row);
				cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
				cout << "  ";
				cct_gotoxy(2 + 4*temp.col+2*dc[i], 2 + 2 * temp.row+dr[i]);
				cct_setcolor(COLOR_CYAN, origin.record[start.row][start.col] + 6);
				cout << "��";
				Sleep(100);
				cct_gotoxy(2 + 4 * temp.col + 2*dc[i], 2 + 2 * temp.row + dr[i]);
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				if (i == 0 || i == 1)//ˮƽ�ƶ�
					cout << "��";
				else                 //�����ƶ�
					cout << "��";
				cct_gotoxy(2 + 4 * temp.col + 4*dc[i], 2 + 2 * temp.row + 2*dr[i]);
				cct_setcolor(COLOR_CYAN, origin.record[start.row][start.col] + 6);
				cout << "��";
				Sleep(100);
				temp.row = temp.row + dr[i];//��ʱ�к��и���
				temp.col = temp.col + dc[i];
				break;
			}
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������һ���ƶ��Ĺ���
  ���������arrays &origin :��¼�ڲ�������Զ���ṹ�����͵�����
		   pos start���ƶ�����ʼλ��       pos end:�ƶ����յ�λ��
		   int choice�� ����ѡ��    int *next3��������һ����ӵ�������������ָ��
		   int remove����¼��������ȥ���������   bool &success :�ƶ��Ƿ�ɹ�������
  �� �� ֵ�� �˴��ƶ���õķ���
  ˵    ����
***************************************************************************/
int draw_move(arrays &origin,pos start,pos end,int choice,int *next3,int *remove,bool &success)
{
	int score=0;
	if (find_path(origin, start, end))//�����ƶ��ɹ�
	{
		if (choice == 6)
			cct_gotoxy(0, 2*origin.rows + 2);
		else
			cct_gotoxy(0, tipy);
		cct_setcolor();
		cout << "[��ʾ] ���Դ�" << "[" << char('A' + start.row) << start.col+1 << "]" << "�ƶ���"
			<< "[" << char('A' + end.row) << end.col+1 << "]           ";
		draw_path(origin, start, end);//�����ƶ�·��
		if (choice == 7) {
			score=move(origin, next3, start, end,remove);//�ı��ڲ�����
			cct_gotoxy(0, 1);
			draw_with_line(origin);//��������
		}
		success = 1;
	}
	else {
		if (choice == 6)
			cct_gotoxy(0, 2*origin.rows + 2);
		else
			cct_gotoxy(0, tipy);
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "[����] �޷���" << "[" << char('A' + start.row) << start.col+1 << "]" << "�ƶ���"
			<< "[" << char('A' + end.row) << end.col+1 << "]           ";
		Sleep(500);//ͣ��һ��ʱ��
		cct_setcolor();
		success=0;//�������û���ƶ��ɹ�������Ҫ�����µ�������
	}
	return score;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�cmd����ͼ�ΰ������ʵ��
  ���������arrays origin :��¼�ڲ�������Զ���ṹ������
		   int choice�� ����ѡ��  
  �� �� ֵ�� 
  ˵    �����˺�����������6��7���
***************************************************************************/
void  console_version_game(arrays origin,int choice)
{
	int total_score = 0,score=0;
	bool success = 1;
	int next3[3],remove[8]={0};
	cct_enable_mouse();//�������
	cct_setcursor(CURSOR_INVISIBLE);//���ع��
	int MX = 0, MY = 0, MAction, keycode1, keycode2,temp_row=0,temp_col=0;
	bool choose=0;
	draw_next_three(next3);   //�Ȼ���Ҫ���ɵ�����
	while (!game_over(origin))
	{
		if (cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2) == CCT_MOUSE_EVENT)  //��ȡ�����¼�
		{
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK)//�һ�
				break;
			else if (MAction == MOUSE_ONLY_MOVED)   //���ƶ�
			{
				if ((MX%4==2||MX%4==3)&&MX<4*origin.cols && MY%2==0&&MY<=2*origin.rows+1&&MY>0)
				{
					if (choice == 6)
						cct_gotoxy(0, 2*origin.rows + 2);
					else
						cct_gotoxy(0, tipy);
					cct_setcolor();
					cout << "[��ǰ���] " << char('A' + MY/2-1) << "��" << MX/4+1 << "��                             ";
				}
			}
			else if (MAction == MOUSE_LEFT_BUTTON_CLICK&&(MX % 4 == 2 || MX % 4 == 3) && MX < 4 * origin.cols 
				     && MY % 2 == 0 && MY <= 2 * origin.rows + 1 && MY>0)   //�ں���λ�õ�����
			{
				if (origin.record[MY / 2 - 1][MX / 4]) //ѡ�зǿհ�
				{
					change_shade(origin,temp_row,temp_col,0);//������һ��ѡ�е�
					change_shade(origin,MY / 2-1, MX / 4 ,1);//�����һ��ѡ��
					temp_row = MY / 2-1;
					temp_col = MX / 4;          //��ʱ���и���
					choose = 1;//�������Ѿ�ѡ��
				}
				else {                              //ѡ�пհ�
					if (choose == 1) {
						pos start = { temp_row,temp_col };
						pos end = { MY / 2-1 ,MX / 4 };
						score=draw_move(origin,start, end,choice,next3,remove,success);//��6��7��������
						if (success) {
							if (origin.record[end.row][end.col] == 0)//����ȥ��
								choose = 0;
							else
								change_shade(origin, end.row, end.col, 1);//û����ȥ�Ļ�������Ϊ�ƶ���������Ӱ
						}
						else
							continue;
						if (choice == 6)//ѡ��6�ڴ��˳�
							break;
						total_score += score;
						if(score==0&&success)//���÷ֵ��ǳɹ��ƶ���������������
							draw_next_three(next3);
						if(score!=0)            //���·���
						    draw_score(total_score);
						draw_record(origin, remove);
						if (success) {
							temp_row = MY / 2 - 1;//������ʱλ��
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
		cout << "��Ϸ�����������ܵ÷֣�"<<total_score;
	}
	cct_disable_mouse();//������
	cct_setcursor(CURSOR_VISIBLE_NORMAL);//���ָ�
	if (choice == 6)
		cct_gotoxy(0, 2 * origin.rows + 1);
	else
		cct_gotoxy(0, tipy-1);
}