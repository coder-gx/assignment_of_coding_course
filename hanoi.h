/* 2152095 �ƿ� ���� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */
/*�������ӡ����һ����������׼*/
const int X = 10;    //�����ӡ������x����
const int Y1 = 12;   //4�����y����
const int Y2 = 28;   //8��9����Ļ���y����

/*�˵�����������*/
int menu();
void huiche(int choice);

/*�������ܺ���������*/
void pause();//��ʱ����
//����ʼ������
void init_landscape(int choice);
void init_portrait(char src, int n, int choice);
void init_column(char src, int n);
void init(int n,char src,char dst,int choice);
//��ͼ����
void draw_base();
void draw_move(char src, char dst, int n);
//��������
void order_input(int* n, char* src, char* tmp, char* dst, bool sleep);
void move(char src, char dst);
void print_landscape(int n, char src, char dst, int choice);
void print_portrait(char src, char dst, int choice);
void fun(int n, char src, char dst, int choice);
void hanoi(int n, char src, char tmp, char dst, int choice);
bool game_over(int n, char dst);
void game_version(int n, char src, char dst);
