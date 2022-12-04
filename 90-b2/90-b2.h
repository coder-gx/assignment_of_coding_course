#pragma once
#define MAX_ROW 9//最大行数
#define MAX_COL 9//最大列数

/*内部数组的打印方式*/
#define BALL_SHADE 1//有球的地方着色
#define PATH 2        //打印路径
#define PATH_SHADE 3  //路径覆盖位置着色

 /*定义双数组结构体，放置矩阵*/
typedef struct arrays   
{
	int rows;  //行数
	int cols;   //列数
	int record[MAX_ROW][MAX_COL];//记录数组变化
	int path[MAX_ROW][MAX_COL];//记录移动路径与消去的小球位置
}arrays;

/*定义结构体,放置行和列*/
typedef struct pos  //定义pos类型，来记录在矩阵中的位置
{
	int row;//行
	int col;//列
}pos;

/*共用函数声明*/
void row_col_input(int& row, int& col);
void end_input();
void init_array(arrays& origin,int choice);
bool find_path(arrays& origin, pos start, pos end);
int move(arrays& origin, int* next3, pos start, pos end,int *remove);
int judge_five(arrays& origin);
bool game_over(const arrays origin);

/*base部分函数声明*/
void print_array(const arrays origin, int choice);
void print_next_three(int* next,int score,bool sucess);
void move_input(pos& start, pos& end, const arrays origin);
void print_path(arrays origin, pos start, pos end);
void print_after_move(const arrays  origin, int score, int total_score);
void base_version_game(arrays origin, int choice);

/*console部分函数声明*/
void enter_input();
void draw_no_line(arrays origin);
void draw_with_line(arrays origin);
void init_console(arrays origin, int choice);
void draw_next_three(int* next3);
void draw_complete(const arrays origin);
void draw_score(int score);
void draw_record(const arrays origin, int* remove);
void change_shade(const arrays origin,int row, int col, bool choose);
void draw_path(const arrays origin, pos start, pos end);
int draw_move(arrays& origin, pos start, pos end, int choice, int* next3, int* remove,bool &success);
void  console_version_game(arrays origin, int choice);