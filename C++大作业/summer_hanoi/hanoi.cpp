#include "hanoi.h"

//文件名:hanoi.cpp
//内容：定义了Hanoi类中的方法

//***************************************
//方法名：solve
//类：Hanoi
//形参：MyStack pillar[3] （三个柱子），int level（操作盘的大小），int from, int to, int by（初始柱，终点柱，经由柱）
//返回值：
//作用：递归计算汉诺塔游戏步骤，核心函数
//***************************************
void Hanoi::solve(MyStack pillar[3], int level, int from, int to, int by)
{
    //标准汉诺塔求解模板
    if (level == 1)
    {
        ++cnt;
        show(pillar, level, from, to, by);
        //每进行一次移动时，移动数+1，并展示移动过程
    }
    else
    {
        solve(pillar, level-1, from, by, to);

        ++cnt;
        show(pillar, level, from, to, by);
        //每进行一次移动时，移动数+1，并展示移动过程

        solve(pillar, level-1, by, to, from);
    }
}


//***************************************
//方法名：show
//类：Hanoi
//形参：MyStack pillar[3] （三个柱子），int level（操作盘的大小），int from, int to, int by（初始柱，终点柱，经由柱）
//返回值：
//作用：根据命令值（cmd），展示不同的汉诺塔游戏步骤
//***************************************
void Hanoi::show(MyStack pillar[3], int level, int from, int to, int by)
{
    pillar[to].push(pillar[from].pop());
    //盘子的移动操作

    switch(cmd){
    case 1://1.基本解

        showSimple(level, from, to);
        cout << '\n';
        break;

    case 2://2.基本解(步数记录)

        showSimpleWithCount(level, from, to);
        cout << '\n';
        break;

    case 3://3.内部数组显示(横向)

        showSimpleWithCountAndStacks(pillar, level, from, to);
        cout << '\n';
        break;

    case 4://4.内部数组显示(纵向+横向)

        cct_cls();
        showVerticalStacksAndLabels(pillar, from, to, 10, 3);
        cct_gotoxy(10, 17);
        showSimpleWithCountAndStacks(pillar, level, from, to);

        cct_gotoxy(10, 19);
        if (speed==0)//speed为0时为单步运行
        {
            system("pause");
            cct_showstr(10, 19, " ", COLOR_BLACK, COLOR_WHITE, 20, -1);//覆盖提示按键字样
        }
        else//否则延时一定时间
            Sleep(1000/speed);
        break;

    case 5://5.图形解-自动游戏版本

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        showVerticalStacksAndLabels(pillar, from, to, 90, 4);
        cct_gotoxy(10, 18);
        showSimpleWithCount(level, from, to);//显示步骤
        cct_setcolor(COLOR_BLACK, GetColor(level));//获得并设置当前盘子的颜色
        cout << "██████";//当前盘子颜色指示器
        showMove(pillar, 5, 3, level, from, to);
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);

        cct_gotoxy(10, 20);
        if (speed==0)//speed为0时为单步运行
        {
            system("pause");
            cct_showstr(10, 20, " ", COLOR_BLACK, COLOR_WHITE, 20, -1);//覆盖提示按键字样
        }
        else//否则延时一定时间
            Sleep(1000/speed);
    }
}


//***************************************
//方法名：showSimple
//类：Hanoi
//形参：int level（操作盘的大小），int from, int to（初始柱，终点柱）
//返回值：
//作用：简单打印步骤，例：5# A-->C
//***************************************
void Hanoi::showSimple(int level, int from, int to)
{
    cout << setw(1) << level << "# " << (char)(from+'A') << "-->" << (char)(to+'A');
}


//***************************************
//方法名：showSimpleWithCount
//类：Hanoi
//形参：int level（操作盘的大小），int from, int to（初始柱，终点柱）
//返回值：
//作用：简单打印步骤，带步骤数，例：第  94 步 (2# C-->A)
//***************************************
void Hanoi::showSimpleWithCount(int level, int from, int to)
{
    cout << "第" << setw(4) << cnt << " 步 (" << setw(1) << level << "#: " << (char)(from+'A') << "-->" << (char)(to+'A') << ") ";
}


//***************************************
//方法名：showSimpleWithCountAndStacks
//类：Hanoi
//形参：MyStack pillar[3] （三个柱子），int level（操作盘的大小），int from, int to（初始柱，终点柱）
//返回值：
//作用：简单打印步骤，带步骤数，以及横向展示各个柱子中的盘子情况
//例：第 114 步 (2#: B-->C)  A: 1                   B: 4 3                 C: 7 6 5 2
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
//方法名：showVerticalStacksAndLabels
//类：Hanoi
//形参：MyStack pillar[3] （三个柱子），int from, int to（初始柱，终点柱），int x, int y（打印坐标）
//返回值：
//作用：在光标处，分别竖直打印每个柱子的情况，带分界线以及标签，见下例
//例：
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
//方法名：showElement
//类：Hanoi
//形参：int type（元素类型），int x, int y（打印坐标）
//返回值：
//作用：在光标处打印元素，0为柱子，1-10为盘子，-1为柱底的托盘
//***************************************
void Hanoi::showElement(int type, int x, int y)
{
    int f_color = GetColor(type);//  不同元素应具有不同的颜色

    if (type==-1){
        cct_showstr(x, y, "█", COLOR_BLACK, f_color, 23, -1);//托盘
    }else{
        //盘子与柱子
        cct_showstr(x, y, " ", COLOR_BLACK, f_color, 11-type, -1);//盘子或柱子左处的空白
        cct_showstr(x+11-type, y, "█", COLOR_BLACK, f_color, type*2+1, -1);//盘子或柱子本身
        cct_showstr(x+13+type, y, " ", COLOR_BLACK, f_color, 11-type, -1);//盘子或柱子右边的空白

        //例：空空空空空空空空柱空空空空空空空空

        //例：空空空空空盘盘盘盘盘盘盘空空空空空
    }
}


//***************************************
//方法名：showPillar
//类：Hanoi
//形参：MyStack pillar[3] （三个柱子），int x, int y（打印坐标）
//返回值：
//作用：在光标处依次打印三个柱子
//***************************************
void Hanoi::showPillar(MyStack pillar[3], int x, int y)
{
    for (int i = 0; i < 3; i++){//从左至右依次遍历三个柱子
        for (int j = 0; j <= 11; j++){
            if (j == 11)
                showElement(-1, x + 26*i, y + j);//11为托盘
            else if (j==0)
                showElement(0, x + 26*i, y + j);//0为柱子（保证始终有柱子存在，避免全是盘子，没有柱子的情况，保证美观）
            else
                showElement(pillar[i].data[10-j], x + 26*i, y + j);//其余为柱子或盘子
        }
    }
}


//***************************************
//方法名：showMove
//类：Hanoi
//形参：MyStack pillar[3] （三个柱子），int x, int y（打印坐标），int level（操作盘的大小），int from, int to（初始柱，终点柱）
//返回值：
//作用：展现出将level大小的盘子从from柱移动至to柱的动画过程
//***************************************
void Hanoi::showMove(MyStack pillar[3], int x, int y, int level, int from, int to)
{
    int start_x, end_x, start_y, end_y;//盘子移动的初始x,y值，以及终点x,y值
    start_x = x + 26 * from;
    end_x = x + 26 * to;
    start_y = y + 10 - pillar[from].top;
    end_y = y + 11 - pillar[to].top;

    int now_x = start_x, now_y = start_y;//记录现在的x,y值

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
    //隐藏光标

    do{
        cct_showstr(now_x, now_y, " ", COLOR_BLACK, COLOR_WHITE, 23, -1);//将当前位置填充空白
        if (now_y>=y)
            showElement(0, now_x, now_y);//在范围内，盘子移走后，剩下的一定是柱子，用柱子把空白补上
        now_y--;
        showElement(level, now_x, now_y);//位置更新后，再次绘制盘子

        Sleep(speed!=0 ? 250/speed : 40);//动画延迟
    }while (now_y>1);
    //将盘子上移

    do{
        //以下过程同上理
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
    //将盘子左移或右移

    do{
        cct_showstr(now_x, now_y, " ", COLOR_BLACK, COLOR_WHITE, 23, -1);
        if (now_y>=y)
            showElement(0, now_x, now_y);
        now_y++;
        showElement(level, now_x, now_y);
        Sleep(speed!=0 ? 250/speed : 40);
    }while (now_y<end_y);
    //将盘子下移

    CursorInfo.bVisible = true;
    SetConsoleCursorInfo(handle, &CursorInfo);
    //取消隐藏光标
}
