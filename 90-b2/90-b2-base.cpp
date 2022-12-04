#include<iostream>
#include"cmd_console_tools.h"
#include"90-b2.h"
#include<iomanip>
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ�ڲ�����
  ���������const arrays origin:ֻ���ļ�¼�ڲ�������Զ���ṹ������  
           int choice:��ӡ��ʽ��BALL_SHADE������ĵط���ɫ��PATH����ӡ·����PATH_SHADE:·������λ����ɫ��
  �� �� ֵ��
  ˵    ����
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
	cct_showch(x, y, '-', 0, 7, 3 * origin.cols); //��ӡ���
	cout << endl;
	for (int i = 0; i < origin.rows; i++)
	{
		cout << char('A' + i) << " | ";
		for (int j = 0; j < origin.cols; j++)
		{
			cout << " ";
			if (choice == BALL_SHADE)//����ĵط���ɫ
			{
				if (origin.record[i][j]) {
					cct_setcolor(14, origin.record[i][j]-1);
					cout << origin.record[i][j];
					cct_setcolor();
				}
				else
					cout << '0';
			}
			else if (choice == PATH)//��ӡ·��
			{
				if (origin.path[i][j] == -1)
					cout << "*";
				else
					cout << "0";
			}
			else if(choice==PATH_SHADE)//·������λ����ɫ
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
  �������ƣ�
  ��    �ܣ������ƶ�ָ��
  ���������pos &start����ʼλ�ýṹ�������   pos &end���յ�λ�ýṹ�������
		   const arrays origin:ֻ���ļ�¼�ڲ�������Զ���ṹ������ 
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void move_input(pos &start, pos &end,const arrays origin)
{
	char s[50];
	int x, y,target=0;//�洢��������,traget�������������㻹���յ�
	bool ok;//ok�ж������Ƿ�ɹ�
	while (1) {
		cout << "������ĸ+���ֵ���ʽ[����c2]����Ҫ�ƶ����";
		cout << (target ? "Ŀ��" : "����");
		cout<< "����:";
		cct_getxy(x, y);//��ȡλ��
		while (1)
		{
			ok = 0;
			cin >> s;
			if (s[0] >= 'a' && s[0] <= 'a' + origin.rows - 1)//��Сдȥ��
				s[0] += 'A' - 'a';
			if (strlen(s) == 2 && (s[0] >= 'A' && s[0] <= 'A' + origin.rows - 1) && (s[1] >= '1' && s[1] <= '1' + origin.cols - 1))
			{
				/*target=0��������㣬Ҫ�����ǿգ�target=1,�����յ㣬Ҫ���յ�Ϊ��*/
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
					cout << "����Ϊ" << s[0] << "��" << s[1] << "��"<<endl;
					ok = 1;
					break;
				}
				cout <<( target ? "��ʼλ�÷ǿ�" : "Ŀ��λ��Ϊ��");
				cout<<",����������.\n";
				break;
			}
			cout << "�����������������\n";
			cct_showch(x, y, ' ', 0, 7, 50);
			cct_gotoxy(x, y);
		}//�ڲ���������while
		if (ok&&target==2)//����ָ�����ɹ��������˳�
			break;
	}//�������������ȷָ���while
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ��������������
  ���������int *next:  �洢��һ����ӵ������� int score���˴��ƶ���õķ���
           bool success�� �˴��ƶ��Ƿ�ɹ�
  �� �� ֵ��
  ˵    �������÷��Ҵ˴��ƶ��ɹ��Ŷ�next������и���
***************************************************************************/
void print_next_three(int* next3,int score,bool success)
{
	srand((unsigned)time(NULL));
	cout << "\n��3���������ɫ�ֱ��ǣ�";
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
  �������ƣ�
  ��    �ܣ���ӡ���ƶ���·��
  ���������arrays origin :��¼�ڲ�������Զ���ṹ������ 
           pos start����ʼλ�� pos end���յ�λ��
  �� �� ֵ��
  ˵    �����ҵ�·����ӡ���Ҳ���������ʾ
***************************************************************************/
void print_path(arrays origin,pos start,pos end)
{
	if (find_path(origin, start, end)) {
		cout << endl;
		cout << "���ҽ�����飺\n";
		print_array(origin, PATH);
		cout << endl << endl;
		cout << "�ƶ�·������ͬɫ��ʶ����\n";
		print_array(origin, PATH_SHADE);
	}
	else
		cout << "�޷��ҵ��ƶ�·��" << endl;
	cout << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ���ƶ�����µ�����͵÷�
  ���������const arrays origin :ֻ���ļ�¼�ڲ�������Զ���ṹ������
		   int score: �ƶ���һ�εķ��� int total_score:�ۼƵ��ܷ�
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_after_move(const arrays  origin,int score,int total_score)
{
	cout << "\n�ƶ��������" << endl;
	print_array(origin, BALL_SHADE);
	cout << endl;
	cout << "���ε÷֣�" << score << " �ܵ÷֣�" << total_score<<endl<<endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ڲ�����ʵ�ֵĺ�������
  ���������arrays origin :��¼�ڲ�������Զ���ṹ�����͵����� int choice:����ѡ���ѡ��
  �� �� ֵ��
  ˵    ������2��3ѡ�����ϣ�ͳһ���ڲ����鷽ʽ��Ϸ
***************************************************************************/
void base_version_game(arrays origin,int choice)
{
	int total_score = 0,score=0;
	pos start, end;
	bool success = 1;
	int next3[3],remove[8];//��һ�γ��ֵ�3��������������û�ã�Ϊ�����㺯������Ҫ����ͼ�ν��溯��ͳһ��
	while (!game_over(origin)) {
		cout << endl << "��ǰ���飺" << endl;
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
				cout << "�޷��ҵ��ƶ�·��" << endl;
			success = 0;
		}
		if (choice == 2)
			break;
	}
	if (choice == 3) {
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << "\n��Ϸ����!!!" << endl;
		cct_setcolor();
	}
}