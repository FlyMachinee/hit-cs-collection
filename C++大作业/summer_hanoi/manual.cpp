#include "hanoi.h"

//文件名:manual.cpp
//内容：定义了Manual类中的方法

//***************************************
//方法名：game
//类：Manual
//形参：MyStack pillar[3] （三个柱子），int level（操作盘的大小），int from, int to（初始柱，终点柱）
//返回值：
//作用：进行手动游戏过程
//***************************************
void Manual::game(MyStack pillar[3], int level, int from, int to)
{
    cct_cls();

    Hanoi hanoi;
    hanoi.speed = 0;
    hanoi.showPillar(pillar, 5, 3);
    //此处hanoi对象只参与图像绘制，不进行步骤计算

    bool no_input_yet=true, is_error=false;
    //记录是否尚未输入，输入是否出错
    int input_from, input_to;
    //记录玩家输入的移动步骤
    int cnt=0, dish_size;
    //记录玩家移动步骤数，移动的盘子大小

    while (1){
        //游戏循环

        cct_gotoxy(0, 0);
        cout << "目标：" << (char)(from+'A') << "-->" << (char)(to+'A');
        //展示游戏目标

        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        hanoi.showVerticalStacksAndLabels(pillar, from, to, 90, 4);

        cct_gotoxy(10, 20);
        if (no_input_yet)
            cout << "初始: ";
        else
            cout << "第" << setw(4) << cnt << " 步 (" << setw(1) << dish_size << "#: " << (char)(input_from+'A') << "-->" << (char)(input_to+'A') << ") ";
            //展示玩家的当前操作步骤

        if (!no_input_yet)
            //根据玩家当前操作步骤，绘制盘子移动的动画
            hanoi.showMove(pillar, 5, 3, dish_size, input_from, input_to);

        if (isWin(pillar, level, to))
            //若游戏胜利，退出游戏循环
            break;

        do{
            //指令输入循环

            if (is_error){
                //若出错，提示重新输入
                cct_gotoxy(10, 22);
                cout << "输入不合理，请重试！";
                is_error=false;
            }

            getGameCommand(input_from, input_to);//获取指令
            cct_showstr(10, 22, " ", COLOR_BLACK, COLOR_WHITE, 20, -1);
            no_input_yet=false;//置为输入状态为否

            if (input_from=='Q' || input_from=='q')
                //若玩家手动退出，即退出指令输入循环
                break;

            if (input_from==input_to){
                //输入的两个操作柱相同，输入非法
                is_error = true;
                continue;
            }
            if (pillar[input_from].top==0){
                //输入中被移动的柱子为空，输入非法
                is_error = true;
                continue;
            }

            //保证被移动柱有盘子的情况下，获取柱顶的盘子大小
            dish_size = pillar[input_from].getTop();

            //获取移动终点柱的柱顶的盘子大小
            int lower_dish_size = (pillar[input_to].top==0 ? 11 : pillar[input_to].getTop());

            if (dish_size>lower_dish_size){
                //大盘子放在小盘子上，移动非法
                is_error = true;
                continue;
            }

        }while (is_error);//若有错误，重新进行指令输入循环

        is_error=false;

        if (input_from=='Q' || input_from=='q')
            //若玩家手动退出，即退出游戏循环
            break;

        pillar[input_to].push(pillar[input_from].pop());
        cnt++;
        //盘子移动，步骤数+1
    }
    if (isWin(pillar, level, to)){
        //游戏胜利，展示胜利字样
        cct_showstr(10, 25, " ", COLOR_BLACK, COLOR_WHITE, 70, -1);
        cct_gotoxy(10, 25);
        cout << "恭喜！你赢了！                                                                     ";
    }

}


//***************************************
//方法名：isWin
//类：Manual
//形参：MyStack pillar[3] （三个柱子），int level（操作盘的大小），int to（终点柱）
//返回值：
//作用：判断游戏是否胜利
//***************************************
bool Manual::isWin(MyStack pillar[3], int level, int to)
{
    //判断逻辑为终点处的盘子是否依次放好
    for (int i=0; i<level; i++){
        if (pillar[to].data[i] != level-i)
            return false;
    }
    return true;
}


//***************************************
//方法名：getGameCommand
//类：Manual
//形参：int &from, int &to（手动将某盘从from柱移动至to柱）
//返回值：
//作用：获取手动移动指令
//***************************************
void Manual::getGameCommand(int &from, int &to)
{
    //获取指令逻辑可参考Menu类中的getMessage方法
    cct_showstr(10, 25, " ", COLOR_BLACK, COLOR_WHITE, 70, -1);
    cct_gotoxy(10, 25);
    char input_from, input_to;

    cout << "请输入移动的柱号(命令形式：AC 或 ac = A顶端的盘子移动到C（大小写均可），Q = 退出)\n";
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
        cout << "请输入移动的柱号 (命令形式: AC 或 ac = A顶端的盘子移动到C（大小写均可）, Q = 退出)\n";
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
