#pragma once
#define MENU_WIDTH 640
#define MENU_HEIGHT 400
#define SELECT_WIDTH 620
#define SELECT_HEIGHT 240

#include "load.h"
#include "calc.h"

typedef struct{
    int x, y;//按钮左上角像素的坐标
    int width, height;//按钮的宽与长
    bool is_press;//按钮是否被按下
    const char* label;//按钮的标签
}RectButton;

//===================================================
//函数名：ShowMenu
//功能：显示菜单，及其按钮与对应功能
//输入参数：无
//返回值：用户触发按钮的id
//===================================================
int ShowMenu(void);

//===================================================
//函数名：GetInfo
//功能：显示选择菜单，及其按钮与对应功能，主要功能是获取游戏地图的数据
//输入参数：指向地图信息结构体的结构体指针(MAP_INFO*)
//返回值：0为开启新游戏，1为继续游戏
//===================================================
int GetInfo(MAP_INFO* pmap_info);

//===================================================
//函数名：GameStart
//功能：包括扫雷游戏的主要内容
//输入参数：指向地图信息结构体的结构体指针(MAP_INFO*)，游戏类型(int，0为开启新游戏；1为继续上局游戏，需读取文件)
//返回值：0为退出，1为返回难度设置界面
//===================================================
int GameStart(MAP_INFO* pmap_info, int game_type);

//===================================================
//函数名：DrawButton
//功能：按指定字体大小绘制所有按钮
//输入参数：按钮数组(RectButton*)，按钮数量(int)，字体大小(int)
//返回值：无
//===================================================
void DrawButton(const RectButton* button, int n, int font_size);

//===================================================
//函数名：SearchButton
//功能：搜索输入坐标所对应的按钮id
//输入参数：坐标x，y，按钮数组(RectButton*)，按钮数量(int)
//返回值：输入坐标所对应的按钮id，-1为无对应按钮
//===================================================
int SearchButton(int x, int y, const RectButton* button, int n);

//===================================================
//函数名：IsInBottonRange
//功能：判断坐标是否在按钮范围内
//输入参数：需要判断的坐标(int,int)(x，y值)，与需要判断的按钮(RectButton*)
//返回值：bool类型，表明坐标是否在按钮范围内
//===================================================
bool IsInBottonRange(int x, int y, const RectButton* button);

//===================================================
//函数名：MouseButtonEventProcess
//功能：处理鼠标事件，反映在按钮上
//输入参数：鼠标消息，按钮数组(RectButton*)，按钮数量(int)
//返回值：用户选择的按钮id，-1为未选择
//===================================================
int MouseButtonEventProcess(mouse_msg msg, RectButton* button, int n);

//===================================================
//函数名：MouseMapEventProcess
//功能：处理鼠标事件，反映在地图上
//输入参数：鼠标消息(mouse_msg)，雷是否已埋下(bool)，游戏状态指针(int*)，地图信息结构体指针(MAP_INFO*)
//返回值：鼠标消息中鼠标位置对应的地图坐标
//===================================================
MAP_POS MouseMapEventProcess(mouse_msg msg, bool* map_is_set, int* game_state, MAP_INFO* pmap_info);

//===================================================
//函数名：DrawBoundary
//功能：绘制网格
//输入参数：地图信息结构体指针(MAP_INFO*)
//返回值：无
//===================================================
void DrawBoundary(MAP_INFO* pmap_info);

//===================================================
//函数名：DrawImage
//功能：绘制网格图片
//输入参数：游戏图片数组(PIMAGE*)，地图信息结构体指针(int*)，游戏运行状态(int)
//返回值：无
//===================================================
void DrawImage(PIMAGE* game_img, MAP_INFO* pmap_info, int game_state);

//===================================================
//函数名：DrawEmoji
//功能：绘制Emoji图片
//输入参数：游戏图片数组(PIMAGE*)，是否展示惊讶的布尔值(bool)，游戏运行状态(int)，地图的列数(int)
//返回值：无
//===================================================
void DrawEmoji(PIMAGE* game_img, bool is_surprised, int game_state, int map_col);
