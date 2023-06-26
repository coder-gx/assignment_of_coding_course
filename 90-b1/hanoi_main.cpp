/*2152095 �ƿ� ���� */

/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

     ���ļ�Ҫ��
	1����������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ�֣�const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
#include<iostream>
#include"hanoi.h"
#include"cmd_console_tools.h"

using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ļ��ʽ��������ع��ܺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);
	while (1) 
	{
		int choice = menu();//��ȡ�˵�ѡ��
		int n;//��ŵ���Ĳ�����
		char src, tmp, dst;//��ʼ�����м�����Ŀ����

		if (choice == 0)//�˳�
			break;
		else if (choice == 1||choice==2||choice==3)//������/�����⣨������¼��/�ڲ�������ʾ������
			order_input(&n, &src, &tmp, &dst,0);
		else if (choice == 4)//�ڲ�������ʾ������+����
		{
			order_input(&n, &src, &tmp, &dst, 1);
			cct_cls();
		}
		else if (choice>=5)//���л�ͼ�Ĳ��ֵĹ���ѡ��
		{
			if (choice == 6 || choice == 7 || choice == 9)
				order_input(&n, &src, &tmp, &dst, 0);
			else if(choice==8)
				order_input(&n, &src, &tmp, &dst, 1);
			cct_cls();
			cct_setcursor(CURSOR_INVISIBLE);
			draw_base();//������
		}
		/*��ʼ���͵��ú�ŵ������*/
		if (choice != 5 ) //5���Ҫ��ʼ���ͺ�ŵ���ƶ�
		{
			cct_setcursor(CURSOR_INVISIBLE);
			init(n, src, dst, choice);//��ʼ����ر���
			if (choice == 7)  //7������ǣ�����һ���ƶ�
			{
				if (n % 2 == 0)
					draw_move(src, tmp, 1);
				else
					draw_move(src, dst, 1);
			}
			if(choice!=6&&choice!=7&&choice!=9)//6��7��9����Ҫ��ŵ���ƶ�
				hanoi(n, src, tmp, dst, choice);
			if (choice == 9)
				game_version(n, src, dst);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			
		}
		huiche(choice);//���ö�ȡ�س��ĺ���
		cct_cls();  //����
	}

	return 0;
}
