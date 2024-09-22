#include "calc.h"
extern BLOCK board[26][32];//引用外部变量

MAP_POS surround[8]={{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};//八个方向的移动

//===================================================
//函数名：MouseToPos
//功能：将鼠标对窗口的相对坐标转换为地图坐标
//输入参数：鼠标信息(mouse_msg)
//返回值：对应的地图坐标(MAP_POS)
//===================================================
MAP_POS MouseToPos(mouse_msg msg)
{
    return MAP_POS((msg.y-12)/18 + 1, (msg.x-12)/18 + 1);
}

//===================================================
//函数名：PosToMouse
//功能：将地图坐标转换为鼠标对窗口的相对坐标(地图坐标对应格的左上角的像素坐标)
//输入参数：对应的地图坐标(MAP_POS)，用于接受鼠标相对于窗口坐标的指针(&x, &y)(int*)
//返回值：无
//===================================================
void PosToMouse(MAP_POS pos, int* pmouse_x, int* pmouse_y)
{
    *pmouse_x = (pos.col-1)*18 + 12 + 1;
    *pmouse_y = (pos.row-1)*18 + 12 + 1;
}

//===================================================
//函数名：InitialMap
//功能：初始化地图，将地图清空
//输入参数：无
//返回值：无
//===================================================
void InitialMap(void)//初始化地图
{
    memset(board, 0, sizeof(BLOCK)*26*32);
}

//===================================================
//函数名：SetMines
//功能：埋雷，并更新雷周边的数字
//输入参数：用户点击的地图坐标(MAP_POS)，指向地图信息结构体的结构体指针(MAP_INFO*)
//返回值：无
//===================================================
void SetMines(MAP_POS act_pos, const MAP_INFO* pmap_info)
{
    srand(time(0));//设置随机数种子
    int mine_set=0;

    do{
        int rand_row = rand() % pmap_info->map_row + 1;
        int rand_col = rand() % pmap_info->map_col + 1;
        if (board[rand_row][rand_col].num != 15 && MAP_POS(rand_row, rand_col) != act_pos){//该格不为雷且不是用户点击的格子时
            board[rand_row][rand_col].num = 15;//埋雷
            mine_set++;

            for (int i=0; i<8; i++){//对周围八个格子
                if ((MAP_POS(rand_row, rand_col) + surround[i]).is_legal(pmap_info) &&\
                board[rand_row + surround[i].row][rand_col + surround[i].col].num != 15){//当格子坐标合法，且不是雷时
                    board[rand_row + surround[i].row][rand_col + surround[i].col].num++;//该格数字加1
                }
            }
        }
    }while (mine_set < pmap_info->map_mines);//直到埋雷数等于地图雷数
}

//===================================================
//函数名：OpenBlock
//功能：打开格子，若为空格，递归打开周边格子
//输入参数：用户点击的地图坐标(MAP_POS)，指向游戏状态的指针，指向地图信息结构体的结构体指针
//返回值：无
//===================================================
void OpenBlock(MAP_POS act_pos, int* game_state, MAP_INFO* pmap_info)
{
    if (act_pos.is_legal(pmap_info)){//当用户点击坐标合法时
        BLOCK* pblock = &board[act_pos.row][act_pos.col];//取个别名，方便使用

        if (pblock->is_open == 0 && pblock->state == 0){//当且仅当格子没被打开，且格子没有被标记时，格子才能被打开
            pblock->is_open = 1;
            (pmap_info->map_open)++;//被打开的格子数加1

            if (pblock->num == 15)//打开了雷
                *game_state = 1;//游戏失败

            if (pblock->num == 0)//当周边雷数为0时
                for (int i=0; i<=7; i++){//遍历周边格子
                    if ((act_pos + surround[i]).is_legal(pmap_info))//当周边格子坐标合法时
                        OpenBlock(act_pos + surround[i], game_state, pmap_info);//递归打开周边的格子
                }
        }
    }
}

//===================================================
//函数名：ChangeState
//功能：改变格子标记状态
//输入参数：用户点击的地图坐标对应的格子的地址(BLOCK*)，地图中的旗帜数
//返回值：无
//===================================================
void ChangeState(BLOCK* pblock, int* map_flag)
{
    if (pblock->is_open  == 0){//格子没被打开，才能标记
        switch (pblock->state){
        case 0:
            pblock->state = 1;//普通格变为旗帜
            (*map_flag)++;//旗帜数加1
            break;
        case 1:
            pblock->state = 2;//旗帜变为问号
            (*map_flag)--;//旗帜数减1
            break;
        case 2:
            pblock->state = 0;//问号变为普通格
            break;
        }
    }
}

//===================================================
//函数名：OpenSurround
//功能：打开周边的格子，当且仅当周边的旗帜数等于该格的数字
//输入参数：用户点击的地图坐标(MAP_POS)，指向游戏状态的指针，指向地图信息结构体的结构体指针
//返回值：无
//===================================================
void OpenSurround(MAP_POS act_pos, int* game_state, MAP_INFO* pmap_info)
{
    if (act_pos.is_legal(pmap_info)){
        BLOCK* pblock = &board[act_pos.row][act_pos.col];

        if (pblock->is_open && pblock->num != 0 && pblock->num == CountFlags(act_pos))//当且仅当格子被打开时且周边的旗帜数等于该格的数字
            for (int i=0; i<=7; i++)//遍历周边格子
                if ((act_pos + surround[i]).is_legal(pmap_info)){//当周边格子坐标合法时
                    OpenBlock(act_pos + surround[i], game_state, pmap_info);//打开周边格子
                }
    }
}

//===================================================
//函数名：CountFlags
//功能：数出周围的旗帜数
//输入参数：用户点击的地图坐标(MAP_POS)
//返回值：周围的旗帜数(int)
//===================================================
int CountFlags(MAP_POS act_pos)
{
    int flag_count=0;
    for (int i=0; i<8; i++)
        if (board[act_pos.row + surround[i].row][act_pos.col + surround[i].col].state == 1)
            flag_count++;
    return flag_count;
}

//===================================================
//函数名：EncryptBlock
//功能：将地图格子的信息进行加密
//输入参数：地图格子(BLOCK)
//返回值：加密结果(unsigned)
//===================================================
unsigned EncryptBlock(BLOCK block)
{
    unsigned num =((rand()%8388608)<<8) + (block.num<<4) + (block.is_down<<3) + (block.is_open<<2) + block.state;//前24位为随机数，后8位存放信息
    num ^= 1571530884;//加掩码
    num = num>>23 | num<<(32-23);//循环移位
    num ^= 2145043451;//加掩码
    return num;
}

//===================================================
//函数名：EncryptNum
//功能：将数字进行加密
//输入参数：数字(unsigned)
//返回值：加密结果(unsigned)
//===================================================
unsigned EncryptNum(unsigned data)
{
    data ^= 1839588510;
    data = data>>19 | data<<(32-19);
    data ^= 1977583954;
    return data;
}

//===================================================
//函数名：DecryptBlock
//功能：将地图格子的信息进行解密
//输入参数：加密结果(unsigned)
//返回值：解密结果(BLOCK)
//===================================================
BLOCK DecryptBlock(unsigned key)
{
    key ^= 2145043451;
    key = key<<23 | key>>(32-23);
    key ^= 1571530884;
    BLOCK block;
    block.num = (key&240)>>4;   //240=11110000
    block.is_down = (key&8)>>3; //8=00001000
    block.is_open = (key&4)>>2; //4=00000100
    block.state = key&3;        //3=00000011
    return block;
}

//===================================================
//函数名：DecryptNum
//功能：将数字进行解密
//输入参数：数字(unsigned)
//返回值：解密结果(unsigned)
//===================================================
unsigned DecryptNum(unsigned key)
{
    key ^= 1977583954;
    key = key<<19 | key>>(32-19);
    key ^= 1839588510;
    return key;
}
