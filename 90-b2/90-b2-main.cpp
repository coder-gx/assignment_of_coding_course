#include<iostream>
#include<climits>
#include<Windows.h>
#include<conio.h>
#include"cmd_console_tools.h"
#include"90-b2.h"
using namespace std;


/*�˵����������ÿ���̨�ĸ�ʽ�����岢�����˵�*/
int menu() 
{
	cct_setconsoleborder(120, 30, 120, 9001);
	cct_setfontsize("������", 16, 0);
	cct_setcolor();
	cct_setconsoleborder(120, 30, 120, 9001);//������һ�Σ���ֹ֮ǰ��Ϊ���ڴ��ڻ���������ʧЧ
	cout << "---------------------------------------------\n";
	cout << "1.�ڲ����飬������ɳ�ʼ5����\n";
	cout << "2.�ڲ����飬�������60%����Ѱ���ƶ�·��\n";
	cout << "3.�ڲ����飬������\n";
	cout << "4.����n*n�Ŀ�ܣ��޷ָ��ߣ��������ʾ5����\n";
	cout << "5.����n*n�Ŀ�ܣ��зָ��ߣ��������ʾ5����\n";
	cout << "6.n*n�Ŀ�ܣ�60%����֧����꣬���һ���ƶ�\n";
	cout << "7.cmdͼ�ν���������\n";
	cout << "---------------------------------------------\n";
	cout << "0.�˳�\n";
	cout << "---------------------------------------------\n";
	cout << "[��ѡ��:]";
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
	arrays origin;//����һ���Զ���arrays���͵�origin����
	while (1) {
		int choice=menu();
		if (choice == 0)
			break;
		cct_cls();
		row_col_input(origin.rows, origin.cols);
		init_array(origin, choice);  //�ڲ������ʼ��

		/*�ڲ������ʵ��*/
		if (choice == 1||choice==4||choice==5) 
		{
			cout << endl << "��ʼ���飺" << endl;
			print_array(origin, BALL_SHADE);
		}
		else if (choice == 2||choice==3)
			base_version_game(origin, choice);//��2��3��ϣ���ɻ�������Ϸ

		/*ͼ�ν����ʵ��*/
		if (choice>=4){
			if(choice==4||choice==5)
				enter_input();
			cct_cls();
			init_console(origin, choice);//����̨��ʼ��
			if (choice == 4)
				draw_no_line(origin);
			else if (choice == 5 || choice == 6)
				draw_with_line(origin);
			else
				draw_complete(origin);
			if (choice == 6 || choice == 7)//��6��7��ϣ����ͼ�ν�����Ϸ
				console_version_game(origin, choice);
		}
		end_input();
	}
	return 0;
}
