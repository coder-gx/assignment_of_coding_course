/* 2152095 计科 龚宣 */


/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
#include<iostream>
#include<climits>
#include<iomanip>
#include<Windows.h>
#include<conio.h>
#include"hanoi.h"
#include"cmd_console_tools.h"
using namespace std;


const int Y_base=16,W_base=23,H_base=12;//画图的基座y坐标，基座宽度和高度
static int pause_time=4;//静态全局变量，延时时间,缺省为4
static int step;//总移动步数
static int top[3], stack[3][10];//1+1方式记录栈顶指针和栈内容

/***************************************************************************
  函数名称：
  功    能：延时函数
  输入参数：
  返 回 值：
  说    明：本函数只用于打印延时，画图延时在函数中单独实行
***************************************************************************/
void pause() 
{
    switch (pause_time)
    {
        case 0:
            while (1)
            {
                int ch = _getch();
                if (ch == '\r')
                    break;
            }
            break;
        case 1:
            Sleep(1000);
            break;
        case 2:
            Sleep(500);
            break;
        case 3:
            Sleep(250);
            break;
        case 4:
            Sleep(100);
            break;
        case 5:
            Sleep(50);
            break;
        default:
            cerr << "error" << endl;
            break;
    }
}

/***************************************************************************
  函数名称：
  功    能：横向打印的初始化
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void init_landscape(int choice)
{
    /*确定打印位置*/
    if (choice == 4)
        cct_gotoxy(0, Y1 + 5);
    else if (choice == 8 || choice == 9)
        cct_gotoxy(0, Y2 + 5);
    /*打印初始数组*/
    cout << "初始:                "; 
    for (int i = 0; i < 3; i++)
    {
        cout << char('A' + i) << ": ";
        for (int j = 0; j < 10; j++)
        {
            if (stack[i][j] != 0)
                cout << setw(2) << stack[i][j];
            else
                cout << "  ";
        }
        cout << " ";
    }
    cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：纵向打印的初始化
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void init_portrait(char src,int n,int choice)
{
    int Y;
    if (choice == 4)
        Y = Y1;
    else if (choice == 8 || choice == 9)
        Y = Y2;
    /*打印基座*/
    cct_gotoxy(X, Y);
    cout << "=========================";
    cct_gotoxy(X + 2, Y + 1);
    cout << 'A';
    cct_gotoxy(X + 12, Y + 1);
    cout << 'B';
    cct_gotoxy(X + 22, Y + 1);
    cout << 'C';
    /*打印初始情况下的表盘*/
    int x = X + 2 + 10 * (src - 'A');
    for (int i = 0; i < n; i++)
    {
        cct_gotoxy(x - 1, Y - 1 - i);
        cout << setw(2) << n - i;
    }
}

/***************************************************************************
  函数名称：
  功    能：汉诺塔起始柱的初始化，在上面画n个盘子
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void init_column(char src, int n)
{
    int x = W_base/2 + (W_base+4) * (src - 'A');
    for (int i = 1; i <= n; i++)
    {
        cct_showch(x- n +i, Y_base - i, ' ', n-i+1,7 , 3+2*n - 2 * i);
        Sleep(150);
    }
    cct_setcolor();//恢复颜色
}

/***************************************************************************
  函数名称：
  功    能：初始化各全局变量和全局数组，调用各初始化函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void init(int n,char src,char dst,int choice)
{
    int p = n;//记录原始的n
    step = 0;
    if (choice == 7 || choice == 9)//没有进行选择的延时设置为4
        pause_time = 4;
    top[0] = top[1] = top[2] = 0;
    for (int i = 0; i <10; i++)//初始化全局数组
    {
        stack[src - 'A'][i] = p;
        if (p > 0) {
            top[src - 'A']++;
            p--;
        }
        stack[(src - 'A' + 1) % 3][i] = 0;
        stack[(src - 'A' + 2) % 3][i] = 0; 
    }
    if (choice == 3 || choice == 4 || choice == 8 || choice == 9)//3,4,8,9需要横向初始化
    {
        init_landscape(choice);
    }
    if (choice == 4 || choice == 8 || choice == 9)//4,8,9需要初始纵向初始化
    {
        cct_gotoxy(0, 0);
        cout << "从 " << src << " 移动到  " << dst << "，共 " << n << " 层, " << "延时设置为 " << pause_time;
        init_portrait(src,n,choice);
    }
    if (choice == 6 || choice == 7) {
        cct_gotoxy(0, 0);
        cout << "从 " << src << " 移动到  " << dst << "，共 " << n << " 层";
    }
    if (choice == 6 || choice == 7 || choice == 8 || choice == 9)//6，7，8，9需要起始柱画图初始化
        init_column(src,n);
    if (choice == 7)//对7的情况先进性一次移动，来改变内部数组，调用draw_move时与8，9统一
    {
        Sleep(2000);
        if (n % 2 == 0)
            move(src, 'A'+'B'+'C'-src-dst);
        else
            move(src, dst);
    }
}

/***************************************************************************
  函数名称：
  功    能：输入多个参数给1234678
  输入参数：通过指针传参
  返 回 值：
  说    明：输入后需判断错误，有选择的获取延时输入
***************************************************************************/
void order_input(int* n,char *src,char* tmp,char *dst,bool sleep)
{
    /*输入层数，起始柱，目标柱*/
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-10)\n";
        cin >> *n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if (*n > 0 && *n < 11)
            break;
    }
    while (1)
    {
        cout << "请输入起始柱(A-C)\n";
        cin >> *src;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if ((*src >= 'A' && *src <= 'C') || (*src >= 'a' && *src <= 'c'))
        {
            if (*src >= 'a')
                *src -= 'a' - 'A';
            break;
        }
    }
    while (1)
    {
        cout << "请输入目标柱(A-C)\n";
        cin >> *dst;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if ((*dst >= 'A' && *dst <= 'C') || (*dst >= 'a' && *dst <= 'c'))
        {
            if (*dst >= 'a')
                *dst -= 'a' - 'A';
            if (*dst == *src)
            {
                cout << "目标柱(" << *dst << ")不能与起始柱(" << *src << ")相同\n";
                continue;
            }
            else
                break;
        }
    }
    if (sleep) {
        /*输入移动速度*/
        while (1)
        {
            cout << "请输入移动速度(0-5:0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
            cin >> pause_time;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            cin.ignore(INT_MAX, '\n');
            if (pause_time >= 0 && pause_time <= 5)
                break;
        }
    }
    *tmp = 'A' + 'B' + 'C' - *src - *dst;  //计算中间盘
}

/***************************************************************************
  函数名称：
  功    能: 汉诺塔的盘发生移动，修改内部数组
  输入参数：
  返 回 值：
  说    明：此函数为1，2，3，4，7，8，9函数共用，其中7在init中单独调用，其他通过汉诺塔功能函数fun来调用
***************************************************************************/
void move(char src, char dst)
{
    stack[dst-'A'][top[dst-'A']++] = stack[src-'A'][--top[src-'A']];
    stack[src-'A'][top[src-'A']] = 0;
}

/***************************************************************************
  函数名称：
  功    能: 汉诺塔的盘发生移动，画图模拟移动过程
  输入参数：
  返 回 值：
  说    明：画图函数有单独的延时设计，此函数为7，8，9项共用
***************************************************************************/
void draw_move(char src, char dst,int n)
{
    int s = src - 'A',d=dst-'A';
    int x_src = 1 + W_base / 2 + s * (W_base + 4),x_dst= 1 + W_base / 2 + d * (W_base + 4);
    /*往上移*/
    for (int i = Y_base - top[s]-1; i >=Y_base- H_base - 1; i--) {
        cct_showch(x_src-W_base/2, i, ' ', 0, 7, W_base / 2);
        if (i == Y_base - H_base-1)
            cct_showch(x_src, i, ' ', 0, 7);
        else
            cct_showch(x_src, i, ' ', 14, 7);
        cct_showch(1 + x_src, i, ' ', 0, 7, W_base / 2); //消去上一个位置
        cct_showch(x_src - n, i - 1, ' ', n, 7, 2*n+1);//画出下一个位置
        if (pause_time == 0)
            Sleep(50);
        else
            Sleep(50*(5-pause_time));
    }
    int x = x_src,y= Y_base - H_base - 2,dx;
    if (s < d)//移动方向
        dx=1;
    else
        dx=-1;
    /*横向移动*/
    while (x!= x_dst){
        cct_showch(x-n, y, ' ', 0, 7, n*2+1);
        cct_showch(x+dx-n, y, ' ', n, n, n*2+1);
        if (pause_time == 0)
            Sleep(50);
        else
            Sleep(50 * (5-pause_time));
        x += dx;
    }
    /*向下移动*/
    for (int i = y; i <= Y_base - top[d]-1; i++) {
        cct_showch(x_dst - W_base / 2, i, ' ', 0, 7, W_base / 2);
        if (i == y||i==y+1)
            cct_showch(x_dst, i, ' ', 0, 7);
        else
            cct_showch(x_dst, i, ' ', 14, 7);
        cct_showch(1 + x_dst, i, ' ', 0, 7, W_base / 2);
        cct_showch(x_dst - n, i + 1, ' ', n, 7, 2 * n + 1);
        if (pause_time == 0)
            Sleep(50);
        else
            Sleep(50 *( 5-pause_time));
    }  
    cct_setcolor();//恢复默认色
}

/***************************************************************************
  函数名称：
  功    能: 横向打印内部数组
  输入参数：
  返 回 值：
  说    明：此函数为1，2，3，4，8，9功能项共用
***************************************************************************/
void print_landscape(int n, char src,char dst, int choice)
{
    if (choice == 4)
        cct_gotoxy(0, Y1+5);
    else if (choice == 8||choice==9)
        cct_gotoxy(0, Y2+5);
    if(choice!=1)
        cout << "第" << setw(4) << step << "步 (";
    cout << setw(2) << setiosflags(ios::right) << n << "# " << src << "-->" << dst;
    if (choice != 1)
        cout << ") ";
    if (choice > 2) {
        for(int i=0;i<3;i++)
        {
            cout << char('A' + i) << ": ";
            for (int j = 0; j < 10; j++)
            {
                if (stack[i][j] != 0)
                    cout << setw(2) << stack[i][j];
                else
                    cout << "  ";

            }
            cout << " ";
        }
    }
    cout << endl;
}
/***************************************************************************
  函数名称：
  功    能: 修改纵向的内部数组
  输入参数：
  返 回 值：
  说    明：此函数为4，8，9项共用
***************************************************************************/
void print_portrait(char src, char dst,int choice)
{
    int Y;
    if (choice == 4)
        Y = Y1;
    else
        Y = Y2;
    cct_gotoxy(X + (src - 'A') * 10 + 1, Y - top[src - 'A'] - 1);
    cout << "  ";  //清楚被移动的字符，下同,注意是两个空格，防止二位数的出现
    cct_gotoxy(X + (dst - 'A') * 10 + 1, Y - top[dst - 'A']);
    cout << setw(2) << stack[dst - 'A'][top[dst - 'A'] - 1];//打印移动后的字符,下同    
}


/***************************************************************************
  函数名称：
  功    能: 汉诺塔递归函数各个功能函数的具体调用
  输入参数：
  返 回 值：
  说    明：通过选择，进行函数调用分配，让函数尽可能共用
***************************************************************************/
void fun(int n, char src, char dst, int choice)
{
    move(src, dst);//内部数组移动
    if (choice <= 4||choice>=8) 
    {
        if(choice>=4)
            pause();
        print_landscape(n, src, dst, choice);
    }
    if (choice == 4 ||choice==8||choice==9)
    {
        print_portrait(src, dst, choice);
        if(choice==8||choice==9)
            draw_move(src, dst, n);
    }
}

/***************************************************************************
  函数名称：
  功    能: 汉诺塔唯一的递归函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst,int choice)
{
    if (n == 1) {
        step++;
        fun(1, src, dst, choice);
    }
    else{
        hanoi(n - 1, src, dst, tmp,choice);
        step++;
        fun(n, src, dst, choice);
        hanoi(n - 1, tmp, src, dst,choice);
    }
}
/***************************************************************************
  函数名称：
  功    能: 绘制汉诺塔基座汉诺塔
  输入参数：
  返 回 值：
  说    明：此函数为5，6，7，8，9共用
***************************************************************************/
void draw_base()
{
    cct_showch(1,Y_base,' ', 14,7,W_base);//基底
    cct_showch(1+W_base+4, Y_base, ' ', 14, 7,W_base);
    cct_showch(1+(W_base+4) * 2, Y_base, ' ', 14, 7, W_base);
    for (int i = 1; i <= H_base; i++)//柱子
    {
        cct_showch(1+W_base/2, Y_base-i, ' ', 14,7 );
        cct_showch(1+W_base+4+W_base/2, Y_base-i, ' ', 14,7);
        cct_showch(1 + (W_base+4)*2+W_base/2, Y_base-i, ' ', 14,7);
        Sleep(300);
    }
    cct_setcolor();
}
/***************************************************************************
  函数名称：
  功    能:判断汉诺塔移动是否成功
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
bool game_over(int n,char dst)
{
    for (int i = 0; i < n; i++)
    {
        if (stack[dst - 'A'][i] != n - i)
            return 0;
    }
    return 1;
}
/***************************************************************************
  函数名称：
  功    能:游戏版函数的实现
  输入参数：
  返 回 值：
  说    明：此函数为9单独使用
***************************************************************************/
void game_version(int n, char src, char dst)
{
    char order[20]={0};//初始化均为0
    cct_gotoxy(0, Y2 + 7);
    cout << "请输入移动的柱号(命令形式：AC=A顶段的盘子移动到C，Q=退出):";
    int px, py;
    cct_getxy(px, py);
    while (!game_over(n, dst)) //游戏不结束
    {
        cct_showch(px, py, ' ', 0, 7, 100);
        cct_gotoxy(px, py);
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
        char ch;
        int count = 0;
        while ((ch = _getch()) != '\r') {   //控制输入一定数量的字符重新输入
            if (ch>32)//只打印图形字符
                cout<<ch;
            if (ch == 0 || ch == -32)//对拓展字符进行二次读取
                _getch();
            if (count < 20&&ch>32)
                order[count++] = ch;
            else{
                cct_showch(px, py, ' ', 0, 7, 100);
                cct_gotoxy(px, py);
                count = 0;
            }
        }
        cout << endl;
        cct_setcursor(CURSOR_INVISIBLE);
        if (count==1 && (order[0] == 'q' || order[0] == 'Q'))//退出
        {
            cout << "游戏中止!!!!!!";
            return;
        }
        else if (count==2&& (order[0] >= 'A' && order[0] <= 'C' || order[0] >= 'a' && order[0] <= 'c') &&
            (order[1] >= 'A' && order[1] <= 'C' || order[1] >= 'a' && order[1] <= 'c'))//输入无误，进行移动
        {
            if (order[0] >= 'a')
                order[0] += 'A' - 'a';
            if (order[1] >= 'a')
                order[1] += 'A' - 'a';
            if (top[order[0] - 'A'] == 0)
            {
                cout << "源柱为空!!!!!";
                Sleep(1000);
                cct_showch(0, py + 1, ' ', 0, 7, 100);
                continue;
            }
            if (top[order[1] - 'A'] != 0 && (stack[order[0] - 'A'][top[order[0] - 'A'] - 1] > stack[order[1] - 'A'][top[order[1] - 'A'] - 1]))
            {
                cout << "大盘压小盘，非法移动!!!!!";
                Sleep(1000);
                cct_showch(0, py + 1, ' ', 0, 7, 100);
                continue;
            }
            step++;
            fun(stack[order[0] - 'A'][top[order[0] - 'A'] - 1], order[0], order[1], 9);//调用功能函数
        }
    }
    cct_gotoxy(0, Y2 + 8);
    cout << "游戏结束!!!!!";
}

