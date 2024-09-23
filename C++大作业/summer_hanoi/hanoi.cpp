#include "hanoi.h"

//�ļ���:hanoi.cpp
//���ݣ�������Hanoi���еķ���

//***************************************
//��������solve
//�ࣺHanoi
//�βΣ�MyStack pillar[3] ���������ӣ���int level�������̵Ĵ�С����int from, int to, int by����ʼ�����յ�������������
//����ֵ��
//���ã��ݹ���㺺ŵ����Ϸ���裬���ĺ���
//***************************************
void Hanoi::solve(MyStack pillar[3], int level, int from, int to, int by)
{
    //��׼��ŵ�����ģ��
    if (level == 1)
    {
        ++cnt;
        show(pillar, level, from, to, by);
        //ÿ����һ���ƶ�ʱ���ƶ���+1����չʾ�ƶ�����
    }
    else
    {
        solve(pillar, level-1, from, by, to);

        ++cnt;
        show(pillar, level, from, to, by);
        //ÿ����һ���ƶ�ʱ���ƶ���+1����չʾ�ƶ�����

        solve(pillar, level-1, by, to, from);
    }
}


//***************************************
//��������show
//�ࣺHanoi
//�βΣ�MyStack pillar[3] ���������ӣ���int level�������̵Ĵ�С����int from, int to, int by����ʼ�����յ�������������
//����ֵ��
//���ã���������ֵ��cmd����չʾ��ͬ�ĺ�ŵ����Ϸ����
//***************************************
void Hanoi::show(MyStack pillar[3], int level, int from, int to, int by)
{
    pillar[to].push(pillar[from].pop());
    //���ӵ��ƶ�����

    switch(cmd){
    case 1://1.������

        showSimple(level, from, to);
        cout << '\n';
        break;

    case 2://2.������(������¼)

        showSimpleWithCount(level, from, to);
        cout << '\n';
        break;

    case 3://3.�ڲ�������ʾ(����)

        showSimpleWithCountAndStacks(pillar, level, from, to);
        cout << '\n';
        break;

    case 4://4.�ڲ�������ʾ(����+����)

        cct_cls();
        showVerticalStacksAndLabels(pillar, from, to, 10, 3);
        cct_gotoxy(10, 17);
        showSimpleWithCountAndStacks(pillar, level, from, to);

        cct_gotoxy(10, 19);
        if (speed==0)//speedΪ0ʱΪ��������
        {
            system("pause");
            cct_showstr(10, 19, " ", COLOR_BLACK, COLOR_WHITE, 20, -1);//������ʾ��������
        }
        else//������ʱһ��ʱ��
            Sleep(1000/speed);
        break;

    case 5://5.ͼ�ν�-�Զ���Ϸ�汾

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        showVerticalStacksAndLabels(pillar, from, to, 90, 4);
        cct_gotoxy(10, 18);
        showSimpleWithCount(level, from, to);//��ʾ����
        cct_setcolor(COLOR_BLACK, GetColor(level));//��ò����õ�ǰ���ӵ���ɫ
        cout << "������������";//��ǰ������ɫָʾ��
        showMove(pillar, 5, 3, level, from, to);
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);

        cct_gotoxy(10, 20);
        if (speed==0)//speedΪ0ʱΪ��������
        {
            system("pause");
            cct_showstr(10, 20, " ", COLOR_BLACK, COLOR_WHITE, 20, -1);//������ʾ��������
        }
        else//������ʱһ��ʱ��
            Sleep(1000/speed);
    }
}


//***************************************
//��������showSimple
//�ࣺHanoi
//�βΣ�int level�������̵Ĵ�С����int from, int to����ʼ�����յ�����
//����ֵ��
//���ã��򵥴�ӡ���裬����5# A-->C
//***************************************
void Hanoi::showSimple(int level, int from, int to)
{
    cout << setw(1) << level << "# " << (char)(from+'A') << "-->" << (char)(to+'A');
}


//***************************************
//��������showSimpleWithCount
//�ࣺHanoi
//�βΣ�int level�������̵Ĵ�С����int from, int to����ʼ�����յ�����
//����ֵ��
//���ã��򵥴�ӡ���裬����������������  94 �� (2# C-->A)
//***************************************
void Hanoi::showSimpleWithCount(int level, int from, int to)
{
    cout << "��" << setw(4) << cnt << " �� (" << setw(1) << level << "#: " << (char)(from+'A') << "-->" << (char)(to+'A') << ") ";
}


//***************************************
//��������showSimpleWithCountAndStacks
//�ࣺHanoi
//�βΣ�MyStack pillar[3] ���������ӣ���int level�������̵Ĵ�С����int from, int to����ʼ�����յ�����
//����ֵ��
//���ã��򵥴�ӡ���裬�����������Լ�����չʾ���������е��������
//������ 114 �� (2#: B-->C)  A: 1                   B: 4 3                 C: 7 6 5 2
//***************************************
void Hanoi::showSimpleWithCountAndStacks(MyStack pillar[3], int level, int from, int to)
{
    showSimpleWithCount(level, from, to);
    for (int i = 0; i < 3; i++)
    {
        cout << ' ' << (char)(i+'A') << ':';
        pillar[i].showHorizontal();
    }
}


//***************************************
//��������showVerticalStacksAndLabels
//�ࣺHanoi
//�βΣ�MyStack pillar[3] ���������ӣ���int from, int to����ʼ�����յ�������int x, int y����ӡ���꣩
//����ֵ��
//���ã��ڹ�괦���ֱ���ֱ��ӡÿ�����ӵ���������ֽ����Լ���ǩ��������
//����
//        5
//        6    1    2
//        7    4    3
//      ===============
//        A    B    C
//***************************************
void Hanoi::showVerticalStacksAndLabels(MyStack pillar[3], int from, int to, int x, int y)
{
    for (int i = 0; i < 3; i++)
    {
        pillar[i].showVertical(x + 5*i, y);
        cct_gotoxy(x + 5*i, y+10);
        cout << "=====";
        cct_gotoxy(x + 5*i, y+11);
        cout << "  " << (char)(i+'A') << "  ";
    }
}


//***************************************
//��������showElement
//�ࣺHanoi
//�βΣ�int type��Ԫ�����ͣ���int x, int y����ӡ���꣩
//����ֵ��
//���ã��ڹ�괦��ӡԪ�أ�0Ϊ���ӣ�1-10Ϊ���ӣ�-1Ϊ���׵�����
//***************************************
void Hanoi::showElement(int type, int x, int y)
{
    int f_color = GetColor(type);//  ��ͬԪ��Ӧ���в�ͬ����ɫ

    if (type==-1){
        cct_showstr(x, y, "��", COLOR_BLACK, f_color, 23, -1);//����
    }else{
        //����������
        cct_showstr(x, y, " ", COLOR_BLACK, f_color, 11-type, -1);//���ӻ������󴦵Ŀհ�
        cct_showstr(x+11-type, y, "��", COLOR_BLACK, f_color, type*2+1, -1);//���ӻ����ӱ���
        cct_showstr(x+13+type, y, " ", COLOR_BLACK, f_color, 11-type, -1);//���ӻ������ұߵĿհ�

        //�����տտտտտտտ����տտտտտտտ�

        //�����տտտտ��������������̿տտտտ�
    }
}


//***************************************
//��������showPillar
//�ࣺHanoi
//�βΣ�MyStack pillar[3] ���������ӣ���int x, int y����ӡ���꣩
//����ֵ��
//���ã��ڹ�괦���δ�ӡ��������
//***************************************
void Hanoi::showPillar(MyStack pillar[3], int x, int y)
{
    for (int i = 0; i < 3; i++){//�����������α�����������
        for (int j = 0; j <= 11; j++){
            if (j == 11)
                showElement(-1, x + 26*i, y + j);//11Ϊ����
            else if (j==0)
                showElement(0, x + 26*i, y + j);//0Ϊ���ӣ���֤ʼ�������Ӵ��ڣ�����ȫ�����ӣ�û�����ӵ��������֤���ۣ�
            else
                showElement(pillar[i].data[10-j], x + 26*i, y + j);//����Ϊ���ӻ�����
        }
    }
}


//***************************************
//��������showMove
//�ࣺHanoi
//�βΣ�MyStack pillar[3] ���������ӣ���int x, int y����ӡ���꣩��int level�������̵Ĵ�С����int from, int to����ʼ�����յ�����
//����ֵ��
//���ã�չ�ֳ���level��С�����Ӵ�from���ƶ���to���Ķ�������
//***************************************
void Hanoi::showMove(MyStack pillar[3], int x, int y, int level, int from, int to)
{
    int start_x, end_x, start_y, end_y;//�����ƶ��ĳ�ʼx,yֵ���Լ��յ�x,yֵ
    start_x = x + 26 * from;
    end_x = x + 26 * to;
    start_y = y + 10 - pillar[from].top;
    end_y = y + 11 - pillar[to].top;

    int now_x = start_x, now_y = start_y;//��¼���ڵ�x,yֵ

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
    //���ع��

    do{
        cct_showstr(now_x, now_y, " ", COLOR_BLACK, COLOR_WHITE, 23, -1);//����ǰλ�����հ�
        if (now_y>=y)
            showElement(0, now_x, now_y);//�ڷ�Χ�ڣ��������ߺ�ʣ�µ�һ�������ӣ������Ӱѿհײ���
        now_y--;
        showElement(level, now_x, now_y);//λ�ø��º��ٴλ�������

        Sleep(speed!=0 ? 250/speed : 40);//�����ӳ�
    }while (now_y>1);
    //����������

    do{
        //���¹���ͬ����
        cct_showstr(now_x, now_y, " ", COLOR_BLACK, COLOR_WHITE, 23, -1);
        if (now_y>=y)
            showElement(0, now_x, now_y);
        if (now_x<end_x)
            now_x+=2;
        else
            now_x-=2;
        showElement(level, now_x, now_y);
        Sleep(speed!=0 ? 250/speed : 40);
    }while (now_x!=end_x);
    //���������ƻ�����

    do{
        cct_showstr(now_x, now_y, " ", COLOR_BLACK, COLOR_WHITE, 23, -1);
        if (now_y>=y)
            showElement(0, now_x, now_y);
        now_y++;
        showElement(level, now_x, now_y);
        Sleep(speed!=0 ? 250/speed : 40);
    }while (now_y<end_y);
    //����������

    CursorInfo.bVisible = true;
    SetConsoleCursorInfo(handle, &CursorInfo);
    //ȡ�����ع��
}
