#include "hanoi.h"

//�ļ���:main.cpp
//���ݣ���Ϸ��������

int main()
{
    MyStack pillar[3];
    //ʵ�����������ӣ�ջ��

    Menu menu;
    menu.getMessage();
    //��ȡ��Ϸ��Ϣ������ֵ����ŵ������������յ㣬�Լ����������ٶ�

    pillar[(int)menu.from].init(menu.lvl);
    //��������Ϸ��ö�Ӧ����������

    menu.actCommand(pillar);
    //��������ִֵ�в�ͬ����

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "\n\n" << endl;
    system("pause");
    return 0;
}

int GetColor(int type)
{
    if (type == -1 || type == 0)
        return COLOR_WHITE;
    else if (type >= 1 && type <= 6)
        return type;
    else
        return type + 2;
}
