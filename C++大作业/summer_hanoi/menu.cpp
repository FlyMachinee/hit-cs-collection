#include "hanoi.h"

//文件名:menu.cpp
//内容：定义了Menu类中的方法

//***************************************
//方法名：getMessage
//类：Menu
//形参：
//返回值：
//作用：获取游戏信息
//***************************************
void Menu::getMessage()
{
    cout << "==========================================\n";
    cout << "1.基本解\n";
    cout << "2.基本解(步数记录)\n";
    cout << "3.内部数组显示(横向)\n";
    cout << "4.内部数组显示(纵向+横向)\n";
    cout << "5.图形解-自动游戏版本\n";
    cout << "6.图形解-游戏版\n";
    cout << "0.退出\n";
    cout << "==========================================\n";

    cout << "[请选择:]";

    char ch;

    while (!(cin >> cmd) || cmd<0 || cmd>6){
        cin.clear();
        while((ch = getc(stdin)) != '\n' && ch != EOF);
        cout << "[请选择:]";
    }
    while((ch = getc(stdin)) != '\n' && ch != EOF);//清空输入缓冲区


    if (cmd!=0){
        cout << "请输入汉诺塔的层数(1-10)：\n";
        while (!(cin >> lvl) || lvl<1 || lvl>10){
            //1至10之间的值才是合法的
            cin.clear();
            while((ch = getchar()) != '\n');//清空输入缓冲区
            cout << "请输入汉诺塔的层数(1-10)：\n";
        }
        while((ch = getchar()) != '\n');//清空输入缓冲区

        cout << "请输入起始柱(A-C/a-c)：\n";
        while (!(cin >> from) || (!(from>='a' && from<='c') && !(from>='A' && from<='C'))){
            //合法输入见上cout
            cin.clear();
            while((ch = getchar()) != '\n');//清空输入缓冲区
            cout << "请输入起始柱(A-C/a-c)：\n";
        }
        while((ch = getchar()) != '\n');//清空输入缓冲区
        if (from>='a' && from<='c')
            from += 'A' - 'a';//小写转大写

        from -= 'A';//'A'-->0, 'B'-->1, 'C'-->2

        cout << "请输入目标柱(A-C/a-c)：\n";
        while (!(cin >> to) || (!(to>='a' && to<='c') && !(to>='A' && to<='C')) || ((to>='a' && to<='c') ? to + 'A' - 'a' : to)==from){
            //合法输入见上cout
            cin.clear();
            while((ch = getchar()) != '\n');//清空输入缓冲区
            cout << "请输入目标柱(A-C/a-c)：\n";
        }
        while((ch = getchar()) != '\n');//清空输入缓冲区
        if (to>='a' && to<='c')
            to += 'A' - 'a';//小写转大写

        to -= 'A';//'A'-->0, 'B'-->1, 'C'-->2
    }

    //根据起点终点，推算经由柱的编号
    if ((from==0 && to==1) || (from==1 && to==0))
        by = 2;
    else if ((from==2 && to==1) || (from==1 && to==2))
        by = 0;
    else
        by = 1;


    if (cmd==4 || cmd==5){
        cout << "请输入移动速度(0-5,0为单步演示)：\n";
        while (!(cin >> speed) || speed<0 || speed>5){
            //合法输入见上cout
            cin.clear();
            while((ch = getchar()) != '\n');//清空输入缓冲区
            cout << "请输入移动速度(0-5,0为单步演示)：\n";
        }
        while((ch = getchar()) != '\n');//清空输入缓冲区
    }
}


//***************************************
//方法名：actCommand
//类：Menu
//形参：
//返回值：
//作用：根据不同的选项执行不同语句
//***************************************
void Menu::actCommand(MyStack pillar[3])
{
    if (cmd == 0)//0命令即退出
    {
        system("pause");
        exit(0);
    }
    else if (cmd != 6)//1-5命令，需程序计算汉诺塔步骤
    {
        Hanoi game;
        game.cmd = cmd;
        game.speed = speed;

        if (cmd == 5)//若为5命令，需提前绘制初始图像
        {
            cct_cls();
            game.showPillar(pillar, 5, 3);
        }

        //递归计算操作步骤，并根据不同命令作出不同响应
        game.solve(pillar, lvl, from, to, by);
    }
    else//6命令，玩家自行游玩
    {
        Manual manual_game;
        manual_game.game(pillar, lvl, from, to);
    }

}
