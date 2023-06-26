/* 2152095 计科 龚宣 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
/*给纵向打印设置一个常变量基准*/
const int X = 10;    //纵向打印基座的x坐标
const int Y1 = 12;   //4项基座y坐标
const int Y2 = 28;   //8，9两项的基座y坐标

/*菜单函数的声明*/
int menu();
void huiche(int choice);

/*基础功能函数的声明*/
void pause();//延时函数
//各初始化函数
void init_landscape(int choice);
void init_portrait(char src, int n, int choice);
void init_column(char src, int n);
void init(int n,char src,char dst,int choice);
//画图函数
void draw_base();
void draw_move(char src, char dst, int n);
//其他函数
void order_input(int* n, char* src, char* tmp, char* dst, bool sleep);
void move(char src, char dst);
void print_landscape(int n, char src, char dst, int choice);
void print_portrait(char src, char dst, int choice);
void fun(int n, char src, char dst, int choice);
void hanoi(int n, char src, char tmp, char dst, int choice);
bool game_over(int n, char dst);
void game_version(int n, char src, char dst);
