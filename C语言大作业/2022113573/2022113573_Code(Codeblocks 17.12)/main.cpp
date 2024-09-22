#include "gui.h"
#include "calc.h"

PIMAGE button_img[2];//定义按钮图片数组。全局使用
BLOCK board[26][32];//定义地图，全局使用s

/*
对于代码，工程文件中已经作出了相应配置，所以理论上说是不需要再进行任何配置就可以进行编译的
若实在无法进行编译，可以在release文件夹中打开已经编译好的exe文件进行游玩

在编译时，若出现了对于本代码之外的代码（极大可能是对ege的代码）抛出warning，本人概不负责
*/

int main(void)
{
    int command;
    MAP_INFO map_info;//定义地图信息结构体
    LoadButtonImage(button_img);

    command = ShowMenu();//显示菜单
    if (command == 1)//用户单击退出按钮，或强制关闭窗口
        exit(0);

    do{
        int game_type = GetInfo(&map_info);//通过图形界面，获取游戏信息
        command = GameStart(&map_info, game_type);//游戏开始
    }while (command == 1);

    ReleaseImage(button_img, 2);
    return 0;
}
