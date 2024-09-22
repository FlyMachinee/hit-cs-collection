#include "hanoi.h"

//�ļ���:manual.cpp
//���ݣ�������Manual���еķ���

//***************************************
//��������game
//�ࣺManual
//�βΣ�MyStack pillar[3] ���������ӣ���int level�������̵Ĵ�С����int from, int to����ʼ�����յ�����
//����ֵ��
//���ã������ֶ���Ϸ����
//***************************************
void Manual::game(MyStack pillar[3], int level, int from, int to)
{
    cct_cls();

    Hanoi hanoi;
    hanoi.speed = 0;
    hanoi.showPillar(pillar, 5, 3);
    //�˴�hanoi����ֻ����ͼ����ƣ������в������

    bool no_input_yet=true, is_error=false;
    //��¼�Ƿ���δ���룬�����Ƿ����
    int input_from, input_to;
    //��¼���������ƶ�����
    int cnt=0, dish_size;
    //��¼����ƶ����������ƶ������Ӵ�С

    while (1){
        //��Ϸѭ��

        cct_gotoxy(0, 0);
        cout << "Ŀ�꣺" << (char)(from+'A') << "-->" << (char)(to+'A');
        //չʾ��ϷĿ��

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        hanoi.showVerticalStacksAndLabels(pillar, from, to, 90, 4);

        cct_gotoxy(10, 20);
        if (no_input_yet)
            cout << "��ʼ: ";
        else
            cout << "��" << setw(4) << cnt << " �� (" << setw(1) << dish_size << "#: " << (char)(input_from+'A') << "-->" << (char)(input_to+'A') << ") ";
            //չʾ��ҵĵ�ǰ��������

        if (!no_input_yet)
            //������ҵ�ǰ�������裬���������ƶ��Ķ���
            hanoi.showMove(pillar, 5, 3, dish_size, input_from, input_to);

        if (isWin(pillar, level, to))
            //����Ϸʤ�����˳���Ϸѭ��
            break;

        do{
            //ָ������ѭ��

            if (is_error){
                //��������ʾ��������
                cct_gotoxy(10, 22);
                cout << "���벻���������ԣ�";
                is_error=false;
            }

            getGameCommand(input_from, input_to);//��ȡָ��
            cct_showstr(10, 22, " ", COLOR_BLACK, COLOR_WHITE, 20, -1);
            no_input_yet=false;//��Ϊ����״̬Ϊ��

            if (input_from=='Q' || input_from=='q')
                //������ֶ��˳������˳�ָ������ѭ��
                break;

            if (input_from==input_to){
                //�����������������ͬ������Ƿ�
                is_error = true;
                continue;
            }
            if (pillar[input_from].top==0){
                //�����б��ƶ�������Ϊ�գ�����Ƿ�
                is_error = true;
                continue;
            }

            //��֤���ƶ��������ӵ�����£���ȡ���������Ӵ�С
            dish_size = pillar[input_from].getTop();

            //��ȡ�ƶ��յ��������������Ӵ�С
            int lower_dish_size = (pillar[input_to].top==0 ? 11 : pillar[input_to].getTop());

            if (dish_size>lower_dish_size){
                //�����ӷ���С�����ϣ��ƶ��Ƿ�
                is_error = true;
                continue;
            }

        }while (is_error);//���д������½���ָ������ѭ��

        is_error=false;

        if (input_from=='Q' || input_from=='q')
            //������ֶ��˳������˳���Ϸѭ��
            break;

        pillar[input_to].push(pillar[input_from].pop());
        cnt++;
        //�����ƶ���������+1
    }
    if (isWin(pillar, level, to)){
        //��Ϸʤ����չʾʤ������
        cct_showstr(10, 25, " ", COLOR_BLACK, COLOR_WHITE, 70, -1);
        cct_gotoxy(10, 25);
        cout << "��ϲ����Ӯ�ˣ�                                                                     ";
    }

}


//***************************************
//��������isWin
//�ࣺManual
//�βΣ�MyStack pillar[3] ���������ӣ���int level�������̵Ĵ�С����int to���յ�����
//����ֵ��
//���ã��ж���Ϸ�Ƿ�ʤ��
//***************************************
bool Manual::isWin(MyStack pillar[3], int level, int to)
{
    //�ж��߼�Ϊ�յ㴦�������Ƿ����ηź�
    for (int i=0; i<level; i++){
        if (pillar[to].data[i] != level-i)
            return false;
    }
    return true;
}


//***************************************
//��������getGameCommand
//�ࣺManual
//�βΣ�int &from, int &to���ֶ���ĳ�̴�from���ƶ���to����
//����ֵ��
//���ã���ȡ�ֶ��ƶ�ָ��
//***************************************
void Manual::getGameCommand(int &from, int &to)
{
    //��ȡָ���߼��ɲο�Menu���е�getMessage����
    cct_showstr(10, 25, " ", COLOR_BLACK, COLOR_WHITE, 70, -1);
    cct_gotoxy(10, 25);
    char input_from, input_to;

    cout << "�������ƶ�������(������ʽ��AC �� ac = A���˵������ƶ���C����Сд���ɣ���Q = �˳�)\n";
    cct_gotoxy(10, 26);
    while (!(cin >> input_from) || (!(input_from>='a' && input_from<='c') && !(input_from>='A' && input_from<='C')) || !(cin >> input_to) || ((!(input_to>='a' && input_to<='c') && !(input_to>='A' && input_to<='C')))){
        cin.clear();
        cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
        cct_showstr(10, 26, " ", COLOR_BLACK, COLOR_WHITE, 10, -1);
        if (input_from=='Q' || input_from=='q')
        {
            from = input_from;
            return;
        }
        cct_showstr(10, 25, " ", COLOR_BLACK, COLOR_WHITE, 80, -1);
        cct_gotoxy(10, 25);
        cout << "�������ƶ������� (������ʽ: AC �� ac = A���˵������ƶ���C����Сд���ɣ�, Q = �˳�)\n";
        cct_gotoxy(10, 26);
    }
    cin.clear();
    cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
    cct_showstr(10, 26, " ", COLOR_BLACK, COLOR_WHITE, 10, -1);
    if (input_from>='a' && input_from<='c')
        input_from += 'A' - 'a';
    if (input_to>='a' && input_to<='c')
        input_to += 'A' - 'a';

    from = input_from - 'A';
    to = input_to - 'A';

}
