#include "hanoi.h"

//文件名:main.cpp
//内容：游戏运行主体

int main()
{
    MyStack pillar[3];
    //实例化三个柱子（栈）

    Menu menu;
    menu.getMessage();
    //获取游戏信息：命令值，汉诺塔层数，起点终点，以及动画播放速度

    pillar[(int)menu.from].init(menu.lvl);
    //将起点柱上放置对应数量的盘子

    menu.actCommand(pillar);
    //根据命令值执行不同程序

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
