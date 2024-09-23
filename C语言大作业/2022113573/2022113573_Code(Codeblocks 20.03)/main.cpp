#include "gui.h"
#include "calc.h"

PIMAGE button_img[2];//���尴ťͼƬ���顣ȫ��ʹ��
BLOCK board[26][32];//�����ͼ��ȫ��ʹ��s

/*
���ڴ��룬�����ļ����Ѿ���������Ӧ���ã�����������˵�ǲ���Ҫ�ٽ����κ����þͿ��Խ��б����
��ʵ���޷����б��룬������release�ļ����д��Ѿ�����õ�exe�ļ���������

�ڱ���ʱ���������˶��ڱ�����֮��Ĵ��루��������Ƕ�ege�Ĵ��룩�׳�warning�����˸Ų�����
*/

int main(void)
{
    int command;
    MAP_INFO map_info;//�����ͼ��Ϣ�ṹ��
    LoadButtonImage(button_img);

    command = ShowMenu();//��ʾ�˵�
    if (command == 1)//�û������˳���ť����ǿ�ƹرմ���
        exit(0);

    do{
        int game_type = GetInfo(&map_info);//ͨ��ͼ�ν��棬��ȡ��Ϸ��Ϣ
        command = GameStart(&map_info, game_type);//��Ϸ��ʼ
    }while (command == 1);

    ReleaseImage(button_img, 2);
    return 0;
}
