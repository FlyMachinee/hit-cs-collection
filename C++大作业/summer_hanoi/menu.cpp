#include "hanoi.h"

//�ļ���:menu.cpp
//���ݣ�������Menu���еķ���

//***************************************
//��������getMessage
//�ࣺMenu
//�βΣ�
//����ֵ��
//���ã���ȡ��Ϸ��Ϣ
//***************************************
void Menu::getMessage()
{
    cout << "==========================================\n";
    cout << "1.������\n";
    cout << "2.������(������¼)\n";
    cout << "3.�ڲ�������ʾ(����)\n";
    cout << "4.�ڲ�������ʾ(����+����)\n";
    cout << "5.ͼ�ν�-�Զ���Ϸ�汾\n";
    cout << "6.ͼ�ν�-��Ϸ��\n";
    cout << "0.�˳�\n";
    cout << "==========================================\n";

    cout << "[��ѡ��:]";

    char ch;

    while (!(cin >> cmd) || cmd<0 || cmd>6){
        cin.clear();
        while((ch = getc(stdin)) != '\n' && ch != EOF);
        cout << "[��ѡ��:]";
    }
    while((ch = getc(stdin)) != '\n' && ch != EOF);//������뻺����


    if (cmd!=0){
        cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
        while (!(cin >> lvl) || lvl<1 || lvl>10){
            //1��10֮���ֵ���ǺϷ���
            cin.clear();
            while((ch = getchar()) != '\n');//������뻺����
            cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
        }
        while((ch = getchar()) != '\n');//������뻺����

        cout << "��������ʼ��(A-C/a-c)��\n";
        while (!(cin >> from) || (!(from>='a' && from<='c') && !(from>='A' && from<='C'))){
            //�Ϸ��������cout
            cin.clear();
            while((ch = getchar()) != '\n');//������뻺����
            cout << "��������ʼ��(A-C/a-c)��\n";
        }
        while((ch = getchar()) != '\n');//������뻺����
        if (from>='a' && from<='c')
            from += 'A' - 'a';//Сдת��д

        from -= 'A';//'A'-->0, 'B'-->1, 'C'-->2

        cout << "������Ŀ����(A-C/a-c)��\n";
        while (!(cin >> to) || (!(to>='a' && to<='c') && !(to>='A' && to<='C')) || ((to>='a' && to<='c') ? to + 'A' - 'a' : to)==from){
            //�Ϸ��������cout
            cin.clear();
            while((ch = getchar()) != '\n');//������뻺����
            cout << "������Ŀ����(A-C/a-c)��\n";
        }
        while((ch = getchar()) != '\n');//������뻺����
        if (to>='a' && to<='c')
            to += 'A' - 'a';//Сдת��д

        to -= 'A';//'A'-->0, 'B'-->1, 'C'-->2
    }

    //��������յ㣬���㾭�����ı��
    if ((from==0 && to==1) || (from==1 && to==0))
        by = 2;
    else if ((from==2 && to==1) || (from==1 && to==2))
        by = 0;
    else
        by = 1;


    if (cmd==4 || cmd==5){
        cout << "�������ƶ��ٶ�(0-5,0Ϊ������ʾ)��\n";
        while (!(cin >> speed) || speed<0 || speed>5){
            //�Ϸ��������cout
            cin.clear();
            while((ch = getchar()) != '\n');//������뻺����
            cout << "�������ƶ��ٶ�(0-5,0Ϊ������ʾ)��\n";
        }
        while((ch = getchar()) != '\n');//������뻺����
    }
}


//***************************************
//��������actCommand
//�ࣺMenu
//�βΣ�
//����ֵ��
//���ã����ݲ�ͬ��ѡ��ִ�в�ͬ���
//***************************************
void Menu::actCommand(MyStack pillar[3])
{
    if (cmd == 0)//0����˳�
    {
        system("pause");
        exit(0);
    }
    else if (cmd != 6)//1-5����������㺺ŵ������
    {
        Hanoi game;
        game.cmd = cmd;
        game.speed = speed;

        if (cmd == 5)//��Ϊ5�������ǰ���Ƴ�ʼͼ��
        {
            cct_cls();
            game.showPillar(pillar, 5, 3);
        }

        //�ݹ����������裬�����ݲ�ͬ����������ͬ��Ӧ
        game.solve(pillar, lvl, from, to, by);
    }
    else//6��������������
    {
        Manual manual_game;
        manual_game.game(pillar, lvl, from, to);
    }

}
