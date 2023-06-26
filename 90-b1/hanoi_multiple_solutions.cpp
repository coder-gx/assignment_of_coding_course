/* 2152095 �ƿ� ���� */


/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

     ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
#include<iostream>
#include<climits>
#include<iomanip>
#include<Windows.h>
#include<conio.h>
#include"hanoi.h"
#include"cmd_console_tools.h"
using namespace std;


const int Y_base=16,W_base=23,H_base=12;//��ͼ�Ļ���y���꣬������Ⱥ͸߶�
static int pause_time=4;//��̬ȫ�ֱ�������ʱʱ��,ȱʡΪ4
static int step;//���ƶ�����
static int top[3], stack[3][10];//1+1��ʽ��¼ջ��ָ���ջ����

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʱ����
  ���������
  �� �� ֵ��
  ˵    ����������ֻ���ڴ�ӡ��ʱ����ͼ��ʱ�ں����е���ʵ��
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
  �������ƣ�
  ��    �ܣ������ӡ�ĳ�ʼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void init_landscape(int choice)
{
    /*ȷ����ӡλ��*/
    if (choice == 4)
        cct_gotoxy(0, Y1 + 5);
    else if (choice == 8 || choice == 9)
        cct_gotoxy(0, Y2 + 5);
    /*��ӡ��ʼ����*/
    cout << "��ʼ:                "; 
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
  �������ƣ�
  ��    �ܣ������ӡ�ĳ�ʼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void init_portrait(char src,int n,int choice)
{
    int Y;
    if (choice == 4)
        Y = Y1;
    else if (choice == 8 || choice == 9)
        Y = Y2;
    /*��ӡ����*/
    cct_gotoxy(X, Y);
    cout << "=========================";
    cct_gotoxy(X + 2, Y + 1);
    cout << 'A';
    cct_gotoxy(X + 12, Y + 1);
    cout << 'B';
    cct_gotoxy(X + 22, Y + 1);
    cout << 'C';
    /*��ӡ��ʼ����µı���*/
    int x = X + 2 + 10 * (src - 'A');
    for (int i = 0; i < n; i++)
    {
        cct_gotoxy(x - 1, Y - 1 - i);
        cout << setw(2) << n - i;
    }
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ŵ����ʼ���ĳ�ʼ���������滭n������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void init_column(char src, int n)
{
    int x = W_base/2 + (W_base+4) * (src - 'A');
    for (int i = 1; i <= n; i++)
    {
        cct_showch(x- n +i, Y_base - i, ' ', n-i+1,7 , 3+2*n - 2 * i);
        Sleep(150);
    }
    cct_setcolor();//�ָ���ɫ
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ����ȫ�ֱ�����ȫ�����飬���ø���ʼ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void init(int n,char src,char dst,int choice)
{
    int p = n;//��¼ԭʼ��n
    step = 0;
    if (choice == 7 || choice == 9)//û�н���ѡ�����ʱ����Ϊ4
        pause_time = 4;
    top[0] = top[1] = top[2] = 0;
    for (int i = 0; i <10; i++)//��ʼ��ȫ������
    {
        stack[src - 'A'][i] = p;
        if (p > 0) {
            top[src - 'A']++;
            p--;
        }
        stack[(src - 'A' + 1) % 3][i] = 0;
        stack[(src - 'A' + 2) % 3][i] = 0; 
    }
    if (choice == 3 || choice == 4 || choice == 8 || choice == 9)//3,4,8,9��Ҫ�����ʼ��
    {
        init_landscape(choice);
    }
    if (choice == 4 || choice == 8 || choice == 9)//4,8,9��Ҫ��ʼ�����ʼ��
    {
        cct_gotoxy(0, 0);
        cout << "�� " << src << " �ƶ���  " << dst << "���� " << n << " ��, " << "��ʱ����Ϊ " << pause_time;
        init_portrait(src,n,choice);
    }
    if (choice == 6 || choice == 7) {
        cct_gotoxy(0, 0);
        cout << "�� " << src << " �ƶ���  " << dst << "���� " << n << " ��";
    }
    if (choice == 6 || choice == 7 || choice == 8 || choice == 9)//6��7��8��9��Ҫ��ʼ����ͼ��ʼ��
        init_column(src,n);
    if (choice == 7)//��7������Ƚ���һ���ƶ������ı��ڲ����飬����draw_moveʱ��8��9ͳһ
    {
        Sleep(2000);
        if (n % 2 == 0)
            move(src, 'A'+'B'+'C'-src-dst);
        else
            move(src, dst);
    }
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������1234678
  ���������ͨ��ָ�봫��
  �� �� ֵ��
  ˵    ������������жϴ�����ѡ��Ļ�ȡ��ʱ����
***************************************************************************/
void order_input(int* n,char *src,char* tmp,char *dst,bool sleep)
{
    /*�����������ʼ����Ŀ����*/
    while (1)
    {
        cout << "�����뺺ŵ���Ĳ���(1-10)\n";
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
        cout << "��������ʼ��(A-C)\n";
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
        cout << "������Ŀ����(A-C)\n";
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
                cout << "Ŀ����(" << *dst << ")��������ʼ��(" << *src << ")��ͬ\n";
                continue;
            }
            else
                break;
        }
    }
    if (sleep) {
        /*�����ƶ��ٶ�*/
        while (1)
        {
            cout << "�������ƶ��ٶ�(0-5:0-���س�������ʾ 1-��ʱ� 5-��ʱ���)" << endl;
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
    *tmp = 'A' + 'B' + 'C' - *src - *dst;  //�����м���
}

/***************************************************************************
  �������ƣ�
  ��    ��: ��ŵ�����̷����ƶ����޸��ڲ�����
  ���������
  �� �� ֵ��
  ˵    �����˺���Ϊ1��2��3��4��7��8��9�������ã�����7��init�е������ã�����ͨ����ŵ�����ܺ���fun������
***************************************************************************/
void move(char src, char dst)
{
    stack[dst-'A'][top[dst-'A']++] = stack[src-'A'][--top[src-'A']];
    stack[src-'A'][top[src-'A']] = 0;
}

/***************************************************************************
  �������ƣ�
  ��    ��: ��ŵ�����̷����ƶ�����ͼģ���ƶ�����
  ���������
  �� �� ֵ��
  ˵    ������ͼ�����е�������ʱ��ƣ��˺���Ϊ7��8��9���
***************************************************************************/
void draw_move(char src, char dst,int n)
{
    int s = src - 'A',d=dst-'A';
    int x_src = 1 + W_base / 2 + s * (W_base + 4),x_dst= 1 + W_base / 2 + d * (W_base + 4);
    /*������*/
    for (int i = Y_base - top[s]-1; i >=Y_base- H_base - 1; i--) {
        cct_showch(x_src-W_base/2, i, ' ', 0, 7, W_base / 2);
        if (i == Y_base - H_base-1)
            cct_showch(x_src, i, ' ', 0, 7);
        else
            cct_showch(x_src, i, ' ', 14, 7);
        cct_showch(1 + x_src, i, ' ', 0, 7, W_base / 2); //��ȥ��һ��λ��
        cct_showch(x_src - n, i - 1, ' ', n, 7, 2*n+1);//������һ��λ��
        if (pause_time == 0)
            Sleep(50);
        else
            Sleep(50*(5-pause_time));
    }
    int x = x_src,y= Y_base - H_base - 2,dx;
    if (s < d)//�ƶ�����
        dx=1;
    else
        dx=-1;
    /*�����ƶ�*/
    while (x!= x_dst){
        cct_showch(x-n, y, ' ', 0, 7, n*2+1);
        cct_showch(x+dx-n, y, ' ', n, n, n*2+1);
        if (pause_time == 0)
            Sleep(50);
        else
            Sleep(50 * (5-pause_time));
        x += dx;
    }
    /*�����ƶ�*/
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
    cct_setcolor();//�ָ�Ĭ��ɫ
}

/***************************************************************************
  �������ƣ�
  ��    ��: �����ӡ�ڲ�����
  ���������
  �� �� ֵ��
  ˵    �����˺���Ϊ1��2��3��4��8��9�������
***************************************************************************/
void print_landscape(int n, char src,char dst, int choice)
{
    if (choice == 4)
        cct_gotoxy(0, Y1+5);
    else if (choice == 8||choice==9)
        cct_gotoxy(0, Y2+5);
    if(choice!=1)
        cout << "��" << setw(4) << step << "�� (";
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
  �������ƣ�
  ��    ��: �޸�������ڲ�����
  ���������
  �� �� ֵ��
  ˵    �����˺���Ϊ4��8��9���
***************************************************************************/
void print_portrait(char src, char dst,int choice)
{
    int Y;
    if (choice == 4)
        Y = Y1;
    else
        Y = Y2;
    cct_gotoxy(X + (src - 'A') * 10 + 1, Y - top[src - 'A'] - 1);
    cout << "  ";  //������ƶ����ַ�����ͬ,ע���������ո񣬷�ֹ��λ���ĳ���
    cct_gotoxy(X + (dst - 'A') * 10 + 1, Y - top[dst - 'A']);
    cout << setw(2) << stack[dst - 'A'][top[dst - 'A'] - 1];//��ӡ�ƶ�����ַ�,��ͬ    
}


/***************************************************************************
  �������ƣ�
  ��    ��: ��ŵ���ݹ麯���������ܺ����ľ������
  ���������
  �� �� ֵ��
  ˵    ����ͨ��ѡ�񣬽��к������÷��䣬�ú��������ܹ���
***************************************************************************/
void fun(int n, char src, char dst, int choice)
{
    move(src, dst);//�ڲ������ƶ�
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
  �������ƣ�
  ��    ��: ��ŵ��Ψһ�ĵݹ麯��
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    ��: ���ƺ�ŵ��������ŵ��
  ���������
  �� �� ֵ��
  ˵    �����˺���Ϊ5��6��7��8��9����
***************************************************************************/
void draw_base()
{
    cct_showch(1,Y_base,' ', 14,7,W_base);//����
    cct_showch(1+W_base+4, Y_base, ' ', 14, 7,W_base);
    cct_showch(1+(W_base+4) * 2, Y_base, ' ', 14, 7, W_base);
    for (int i = 1; i <= H_base; i++)//����
    {
        cct_showch(1+W_base/2, Y_base-i, ' ', 14,7 );
        cct_showch(1+W_base+4+W_base/2, Y_base-i, ' ', 14,7);
        cct_showch(1 + (W_base+4)*2+W_base/2, Y_base-i, ' ', 14,7);
        Sleep(300);
    }
    cct_setcolor();
}
/***************************************************************************
  �������ƣ�
  ��    ��:�жϺ�ŵ���ƶ��Ƿ�ɹ�
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    ��:��Ϸ�溯����ʵ��
  ���������
  �� �� ֵ��
  ˵    �����˺���Ϊ9����ʹ��
***************************************************************************/
void game_version(int n, char src, char dst)
{
    char order[20]={0};//��ʼ����Ϊ0
    cct_gotoxy(0, Y2 + 7);
    cout << "�������ƶ�������(������ʽ��AC=A���ε������ƶ���C��Q=�˳�):";
    int px, py;
    cct_getxy(px, py);
    while (!game_over(n, dst)) //��Ϸ������
    {
        cct_showch(px, py, ' ', 0, 7, 100);
        cct_gotoxy(px, py);
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
        char ch;
        int count = 0;
        while ((ch = _getch()) != '\r') {   //��������һ���������ַ���������
            if (ch>32)//ֻ��ӡͼ���ַ�
                cout<<ch;
            if (ch == 0 || ch == -32)//����չ�ַ����ж��ζ�ȡ
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
        if (count==1 && (order[0] == 'q' || order[0] == 'Q'))//�˳�
        {
            cout << "��Ϸ��ֹ!!!!!!";
            return;
        }
        else if (count==2&& (order[0] >= 'A' && order[0] <= 'C' || order[0] >= 'a' && order[0] <= 'c') &&
            (order[1] >= 'A' && order[1] <= 'C' || order[1] >= 'a' && order[1] <= 'c'))//�������󣬽����ƶ�
        {
            if (order[0] >= 'a')
                order[0] += 'A' - 'a';
            if (order[1] >= 'a')
                order[1] += 'A' - 'a';
            if (top[order[0] - 'A'] == 0)
            {
                cout << "Դ��Ϊ��!!!!!";
                Sleep(1000);
                cct_showch(0, py + 1, ' ', 0, 7, 100);
                continue;
            }
            if (top[order[1] - 'A'] != 0 && (stack[order[0] - 'A'][top[order[0] - 'A'] - 1] > stack[order[1] - 'A'][top[order[1] - 'A'] - 1]))
            {
                cout << "����ѹС�̣��Ƿ��ƶ�!!!!!";
                Sleep(1000);
                cct_showch(0, py + 1, ' ', 0, 7, 100);
                continue;
            }
            step++;
            fun(stack[order[0] - 'A'][top[order[0] - 'A'] - 1], order[0], order[1], 9);//���ù��ܺ���
        }
    }
    cct_gotoxy(0, Y2 + 8);
    cout << "��Ϸ����!!!!!";
}

