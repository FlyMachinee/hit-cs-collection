#include "calc.h"
extern BLOCK board[26][32];//�����ⲿ����

MAP_POS surround[8]={{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};//�˸�������ƶ�

//===================================================
//��������MouseToPos
//���ܣ������Դ��ڵ��������ת��Ϊ��ͼ����
//��������������Ϣ(mouse_msg)
//����ֵ����Ӧ�ĵ�ͼ����(MAP_POS)
//===================================================
MAP_POS MouseToPos(mouse_msg msg)
{
    return MAP_POS((msg.y-12)/18 + 1, (msg.x-12)/18 + 1);
}

//===================================================
//��������PosToMouse
//���ܣ�����ͼ����ת��Ϊ���Դ��ڵ��������(��ͼ�����Ӧ������Ͻǵ���������)
//�����������Ӧ�ĵ�ͼ����(MAP_POS)�����ڽ����������ڴ��������ָ��(&x, &y)(int*)
//����ֵ����
//===================================================
void PosToMouse(MAP_POS pos, int* pmouse_x, int* pmouse_y)
{
    *pmouse_x = (pos.col-1)*18 + 12 + 1;
    *pmouse_y = (pos.row-1)*18 + 12 + 1;
}

//===================================================
//��������InitialMap
//���ܣ���ʼ����ͼ������ͼ���
//�����������
//����ֵ����
//===================================================
void InitialMap(void)//��ʼ����ͼ
{
    memset(board, 0, sizeof(BLOCK)*26*32);
}

//===================================================
//��������SetMines
//���ܣ����ף����������ܱߵ�����
//����������û�����ĵ�ͼ����(MAP_POS)��ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ��(MAP_INFO*)
//����ֵ����
//===================================================
void SetMines(MAP_POS act_pos, const MAP_INFO* pmap_info)
{
    srand(time(0));//�������������
    int mine_set=0;

    do{
        int rand_row = rand() % pmap_info->map_row + 1;
        int rand_col = rand() % pmap_info->map_col + 1;
        if (board[rand_row][rand_col].num != 15 && MAP_POS(rand_row, rand_col) != act_pos){//�ø�Ϊ���Ҳ����û�����ĸ���ʱ
            board[rand_row][rand_col].num = 15;//����
            mine_set++;

            for (int i=0; i<8; i++){//����Χ�˸�����
                if ((MAP_POS(rand_row, rand_col) + surround[i]).is_legal(pmap_info) &&\
                board[rand_row + surround[i].row][rand_col + surround[i].col].num != 15){//����������Ϸ����Ҳ�����ʱ
                    board[rand_row + surround[i].row][rand_col + surround[i].col].num++;//�ø����ּ�1
                }
            }
        }
    }while (mine_set < pmap_info->map_mines);//ֱ�����������ڵ�ͼ����
}

//===================================================
//��������OpenBlock
//���ܣ��򿪸��ӣ���Ϊ�ո񣬵ݹ���ܱ߸���
//����������û�����ĵ�ͼ����(MAP_POS)��ָ����Ϸ״̬��ָ�룬ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ��
//����ֵ����
//===================================================
void OpenBlock(MAP_POS act_pos, int* game_state, MAP_INFO* pmap_info)
{
    if (act_pos.is_legal(pmap_info)){//���û��������Ϸ�ʱ
        BLOCK* pblock = &board[act_pos.row][act_pos.col];//ȡ������������ʹ��

        if (pblock->is_open == 0 && pblock->state == 0){//���ҽ�������û���򿪣��Ҹ���û�б����ʱ�����Ӳ��ܱ���
            pblock->is_open = 1;
            (pmap_info->map_open)++;//���򿪵ĸ�������1

            if (pblock->num == 15)//������
                *game_state = 1;//��Ϸʧ��

            if (pblock->num == 0)//���ܱ�����Ϊ0ʱ
                for (int i=0; i<=7; i++){//�����ܱ߸���
                    if ((act_pos + surround[i]).is_legal(pmap_info))//���ܱ߸�������Ϸ�ʱ
                        OpenBlock(act_pos + surround[i], game_state, pmap_info);//�ݹ���ܱߵĸ���
                }
        }
    }
}

//===================================================
//��������ChangeState
//���ܣ��ı���ӱ��״̬
//����������û�����ĵ�ͼ�����Ӧ�ĸ��ӵĵ�ַ(BLOCK*)����ͼ�е�������
//����ֵ����
//===================================================
void ChangeState(BLOCK* pblock, int* map_flag)
{
    if (pblock->is_open  == 0){//����û���򿪣����ܱ��
        switch (pblock->state){
        case 0:
            pblock->state = 1;//��ͨ���Ϊ����
            (*map_flag)++;//��������1
            break;
        case 1:
            pblock->state = 2;//���ı�Ϊ�ʺ�
            (*map_flag)--;//��������1
            break;
        case 2:
            pblock->state = 0;//�ʺű�Ϊ��ͨ��
            break;
        }
    }
}

//===================================================
//��������OpenSurround
//���ܣ����ܱߵĸ��ӣ����ҽ����ܱߵ����������ڸø������
//����������û�����ĵ�ͼ����(MAP_POS)��ָ����Ϸ״̬��ָ�룬ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ��
//����ֵ����
//===================================================
void OpenSurround(MAP_POS act_pos, int* game_state, MAP_INFO* pmap_info)
{
    if (act_pos.is_legal(pmap_info)){
        BLOCK* pblock = &board[act_pos.row][act_pos.col];

        if (pblock->is_open && pblock->num != 0 && pblock->num == CountFlags(act_pos))//���ҽ������ӱ���ʱ���ܱߵ����������ڸø������
            for (int i=0; i<=7; i++)//�����ܱ߸���
                if ((act_pos + surround[i]).is_legal(pmap_info)){//���ܱ߸�������Ϸ�ʱ
                    OpenBlock(act_pos + surround[i], game_state, pmap_info);//���ܱ߸���
                }
    }
}

//===================================================
//��������CountFlags
//���ܣ�������Χ��������
//����������û�����ĵ�ͼ����(MAP_POS)
//����ֵ����Χ��������(int)
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
//��������EncryptBlock
//���ܣ�����ͼ���ӵ���Ϣ���м���
//�����������ͼ����(BLOCK)
//����ֵ�����ܽ��(unsigned)
//===================================================
unsigned EncryptBlock(BLOCK block)
{
    unsigned num =((rand()%8388608)<<8) + (block.num<<4) + (block.is_down<<3) + (block.is_open<<2) + block.state;//ǰ24λΪ���������8λ�����Ϣ
    num ^= 1571530884;//������
    num = num>>23 | num<<(32-23);//ѭ����λ
    num ^= 2145043451;//������
    return num;
}

//===================================================
//��������EncryptNum
//���ܣ������ֽ��м���
//�������������(unsigned)
//����ֵ�����ܽ��(unsigned)
//===================================================
unsigned EncryptNum(unsigned data)
{
    data ^= 1839588510;
    data = data>>19 | data<<(32-19);
    data ^= 1977583954;
    return data;
}

//===================================================
//��������DecryptBlock
//���ܣ�����ͼ���ӵ���Ϣ���н���
//������������ܽ��(unsigned)
//����ֵ�����ܽ��(BLOCK)
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
//��������DecryptNum
//���ܣ������ֽ��н���
//�������������(unsigned)
//����ֵ�����ܽ��(unsigned)
//===================================================
unsigned DecryptNum(unsigned key)
{
    key ^= 1977583954;
    key = key<<19 | key>>(32-19);
    key ^= 1839588510;
    return key;
}
