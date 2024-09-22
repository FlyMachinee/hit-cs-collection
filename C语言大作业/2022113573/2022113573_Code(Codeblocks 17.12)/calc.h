#pragma once

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <graphics.h>

typedef struct MAP_INFO{//定义地图信息结构体
    int map_row, map_col, map_mines, map_flag, map_open, run_time;//地图的行数，列数，雷数，标旗数，以及打开的格子数，与已运行时间
}MAP_INFO;

typedef struct BLOCK{//地图中一格的数据结构体
    unsigned char num:4    ;//0~8表示周围的雷数，15表示本身就是雷
    unsigned char is_down:1;//该格是否被按下
    unsigned char is_open:1;//该格是否被打开
    unsigned char state:2  ;//该格的标记状态(0为无标记，1为标旗，2为问号)
}BLOCK;//通过指定成员的位数，可大大减少地图存储所占的空间

typedef struct MAP_POS{//定义地图坐标结构体
    int row;//地图坐标的行值，从1开始
    int col;//地图坐标的列值，从1开始

    MAP_POS(int row=0, int col=0){//返回输入x，y值对应的地图坐标结构体
        this->row = row;
        this->col = col;
    }

    MAP_POS operator+ (const MAP_POS& pos){//定义地图坐标之间的加法
        return MAP_POS(row + pos.row, col + pos.col);
    }

    bool operator== (const MAP_POS& pos){//定义地图坐标之间的等于比较
        return row == pos.row && col == pos.col;
    }

    bool operator!= (const MAP_POS& pos){//定义地图坐标之间的不等于比较
        return row != pos.row || col != pos.col;
    }

    bool is_legal(const MAP_INFO* pmap_info) {//判断地图坐标是否合法
        return row >= 1 && row <= pmap_info->map_row && col >= 1 && col <= pmap_info->map_col;
    }
}MAP_POS;

typedef struct RANK_INFO{//定义排名信息结构体
    char username[33];
    int time;
}RANK_INFO;

//===================================================
//函数名：MouseToPos
//功能：将鼠标对窗口的相对坐标转换为地图坐标
//输入参数：鼠标信息(mouse_msg)
//返回值：对应的地图坐标(MAP_POS)
//===================================================
MAP_POS MouseToPos(mouse_msg msg);

//===================================================
//函数名：PosToMouse
//功能：将地图坐标转换为鼠标对窗口的相对坐标(地图坐标对应格的左上角的像素坐标)
//输入参数：对应的地图坐标(MAP_POS)，用于接受鼠标相对于窗口坐标的指针(&x, &y)(int*,int*)
//返回值：无
//===================================================
void PosToMouse(MAP_POS pos, int* pmouse_x, int* pmouse_y);

//===================================================
//函数名：InitialMap
//功能：初始化地图，将地图清空
//输入参数：无
//返回值：无
//===================================================
void InitialMap(void);

//===================================================
//函数名：SetMines
//功能：埋雷，并更新雷周边的数字
//输入参数：用户点击的地图坐标(MAP_POS)，地图信息结构体指针(MAP_INFO*)
//返回值：无
//===================================================
void SetMines(MAP_POS act_pos, const MAP_INFO* pmap_info);//设置地雷，并更新周围的数字

//===================================================
//函数名：OpenBlock
//功能：打开格子，若为空格，递归打开周边格子
//输入参数：用户点击的地图坐标(MAP_POS)，指向游戏状态的指针，指向地图信息结构体的结构体指针
//返回值：无
//===================================================
void OpenBlock(MAP_POS act_pos, int* game_state, MAP_INFO* pmap_info);

//===================================================
//函数名：ChangeState
//功能：改变格子标记状态，按无标记->旗帜->问号循环切换
//输入参数：用户点击的地图坐标对应的格子的地址(BLOCK*)，地图旗帜数地址(int*)
//返回值：无
//===================================================
void ChangeState(BLOCK* pblock, int* map_flag);//按无标记->旗帜->问号循环标记格子

//===================================================
//函数名：OpenSurround
//功能：打开周边的格子，当且仅当周边的旗帜数等于该格的数字
//输入参数：用户点击的地图坐标(MAP_POS)，游戏状态指针(int*)，地图信息结构体指针(MAP_INFO*)
//返回值：无
//===================================================
void OpenSurround(MAP_POS act_pos, int* game_state, MAP_INFO* pmap_info);

//===================================================
//函数名：CountFlags
//功能：数出周围的旗帜数
//输入参数：用户点击的地图坐标(MAP_POS)
//返回值：周围的旗帜数(int)
//===================================================
int CountFlags(MAP_POS act_pos);//计算周围的旗帜数

//===================================================
//函数名：EncryptBlock
//功能：将地图格子的信息进行加密
//输入参数：地图格子(BLOCK)
//返回值：加密结果(unsigned)
//===================================================
unsigned EncryptBlock(BLOCK block);

//===================================================
//函数名：EncryptNum
//功能：将数字进行加密
//输入参数：数字(unsigned)
//返回值：加密结果(unsigned)
//===================================================
unsigned EncryptNum(unsigned data);

//===================================================
//函数名：DecryptBlock
//功能：将地图格子的信息进行解密
//输入参数：加密结果(unsigned)
//返回值：解密结果(BLOCK)
//===================================================
BLOCK DecryptBlock(unsigned key);

//===================================================
//函数名：DecryptNum
//功能：将数字进行解密
//输入参数：数字(unsigned)
//返回值：解密结果(unsigned)
//===================================================
unsigned DecryptNum(unsigned key);
