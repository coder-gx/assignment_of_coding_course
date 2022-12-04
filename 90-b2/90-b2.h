#pragma once
#define MAX_ROW 9//�������
#define MAX_COL 9//�������

/*�ڲ�����Ĵ�ӡ��ʽ*/
#define BALL_SHADE 1//����ĵط���ɫ
#define PATH 2        //��ӡ·��
#define PATH_SHADE 3  //·������λ����ɫ

 /*����˫����ṹ�壬���þ���*/
typedef struct arrays   
{
	int rows;  //����
	int cols;   //����
	int record[MAX_ROW][MAX_COL];//��¼����仯
	int path[MAX_ROW][MAX_COL];//��¼�ƶ�·������ȥ��С��λ��
}arrays;

/*����ṹ��,�����к���*/
typedef struct pos  //����pos���ͣ�����¼�ھ����е�λ��
{
	int row;//��
	int col;//��
}pos;

/*���ú�������*/
void row_col_input(int& row, int& col);
void end_input();
void init_array(arrays& origin,int choice);
bool find_path(arrays& origin, pos start, pos end);
int move(arrays& origin, int* next3, pos start, pos end,int *remove);
int judge_five(arrays& origin);
bool game_over(const arrays origin);

/*base���ֺ�������*/
void print_array(const arrays origin, int choice);
void print_next_three(int* next,int score,bool sucess);
void move_input(pos& start, pos& end, const arrays origin);
void print_path(arrays origin, pos start, pos end);
void print_after_move(const arrays  origin, int score, int total_score);
void base_version_game(arrays origin, int choice);

/*console���ֺ�������*/
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