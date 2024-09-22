#include "gui.h"
#include "load.h"
#include "calc.h"
#include <ege/sys_edit.h>

extern BLOCK board[26][32];//�����ⲿ����

//===================================================
//��������ShowMenu
//���ܣ���ʾ�˵������䰴ť���Ӧ����
//�����������
//����ֵ���û�������ť��id(int)
//===================================================
int ShowMenu(void)
{
    initgraph(MENU_WIDTH, MENU_HEIGHT, INIT_RENDERMANUAL | INIT_WITHLOGO);//��ʼ���˵����ڣ�Ϊ�ֶ�ˢ��ģʽ
    setcaption("�˵�");//���ñ���

    PIMAGE menu_background = newimage();//���������ز˵�����ͼƬ
    getimage(menu_background, "resource\\menu_background.png");

    RectButton menu_button[2]={{88       , MENU_HEIGHT-45-100, 210, 100, false, "�� ��"},
                               {88+210+44, MENU_HEIGHT-45-100, 210, 100, false, "�� ��"}};
    //������ť���飬0Ϊ���水ť��1Ϊ�˳���ť

    int command = -1;//�洢�û�����İ�ť��-1Ϊδ������0Ϊ���棬1Ϊ�˳�

    for (; command==-1; delay_fps(60)){//��ͼѭ��
        mouse_msg msg;
        while (mousemsg()){
            msg = getmouse();
            command = MouseButtonEventProcess(msg, menu_button, 2);//��������¼�
        }

		cleardevice();//����
        putimage(0, 0, menu_background);//���Ʊ���ͼƬ
		DrawButton(menu_button, 2, 50);//���ư�ť
    }
    closegraph();//�رղ˵�����
    ReleaseImage(&menu_background, 1);//�ͷ�ͼƬ�ڴ�
    return command;
}

//===================================================
//��������GetInfo
//���ܣ���ʾѡ��˵������䰴ť���Ӧ���ܣ���Ҫ�����ǻ�ȡ��Ϸ��ͼ������
//���������ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ��
//����ֵ��0Ϊ��������Ϸ��1Ϊ������Ϸ
//===================================================
int GetInfo(MAP_INFO* pmap_info)
{
    initgraph(SELECT_WIDTH, SELECT_HEIGHT, INIT_RENDERMANUAL);//��ʼ�����ڣ�Ϊ�ֶ�ˢ��ģʽ
    setcaption("�Ѷ�����");//���ñ���
    setbkcolor(EGERGB(204, 204, 204));//���ñ���ɫ

    sys_edit input_box[3];
    for (int i=0; i<3; i++){
        input_box[i].create(false);
        input_box[i].move(408, 54+i*(26+27));
        input_box[i].size(18 * 3, 18 + 8);
        input_box[i].setmaxlen(3);
        input_box[i].setfont(18, 0, "����");
        input_box[i].visible(true);
    }
    //��������ʼ����������飬0Ϊ�����ͼ������1Ϊ�����ͼ������2Ϊ�����ͼ����

    RectButton select_button[5]={{40     , 30,           100, 50, false, "����"},
                                 {40     , 30+50+15,     100, 50, false, "�м�"},
                                 {40     , 30+50*2+15*2, 100, 50, false, "�߼�"},
                                 {240-50 , 30+50+15,     100, 50, false, "�Զ���"},
                                 {620-130, 30+50+15,     100, 50, false, "��ȡ�浵"}};
    //������ť���飬0Ϊ������ť��1Ϊ�м���ť��2Ϊ�߼���ť��3Ϊ�Զ��尴ť��4Ϊ��ȡ�浵��ť

    int command;//�洢�û�����İ�ť��-1Ϊδ������0Ϊ������ť��1Ϊ�м���ť��2Ϊ�߼���ť��3Ϊ�Զ��尴ť��4Ϊ��ȡ�浵��ť
    bool input_no_error, save_no_error;//��¼�Զ��������Ƿ�������ȷ
    do{
        input_no_error = save_no_error = true;
        command = -1;

        for (int i=0; i<3; i++)
            input_box[i].settext("");//��������

        for (; command==-1; delay_fps(60)){//��ͼѭ��
            mouse_msg msg;
            while (mousemsg()){
                msg = getmouse();//��ȡ����¼�
                command = MouseButtonEventProcess(msg, select_button, 5);//������갴ť�¼�
            }

            cleardevice();//����

            DrawButton(select_button, 5, 25);//���ư�ť
            setbkmode(TRANSPARENT);//�������ֱ���͸��
            setfont(18, 0, "����");//��������
            settextjustify(RIGHT_TEXT, CENTER_TEXT);//����ģʽ��ˮƽ�Ҷ��룬��ֱ����
            outtextxy(408, 54+0*(26+27)+13, "�߶�(9-24)");
            outtextxy(408, 54+1*(26+27)+13, "���(9-30)");
            outtextxy(408, 54+2*(26+27)+13, "����(10-668)");
        }

        switch (command){//����ָ�������Ѷ�
        case 0://����
            pmap_info->map_row = 9;
            pmap_info->map_col = 9;
            pmap_info->map_mines = 10;
            break;
        case 1://�м�
            pmap_info->map_row = 16;
            pmap_info->map_col = 16;
            pmap_info->map_mines = 40;
            break;
        case 2://�߼�
            pmap_info->map_row = 16;
            pmap_info->map_col = 30;
            pmap_info->map_mines = 99;
            break;
        case 3://�Զ���
            char str_buffer[8];
            for (int i=0; i<3; i++){//��ȡ��������������
                input_box[i].gettext(8, str_buffer);
                int num;

                if (1 != sscanf(str_buffer, "%d", &num)){
                    input_no_error = false;
                    break;
                }

                if (i==0){
                    if (num<9 || num>24){//����������Χ
                        input_no_error = false;
                        break;
                    }else
                        pmap_info->map_row = num;
                }else if (i==1){
                    if (num<9 || num>30){//����������Χ
                        input_no_error = false;
                        break;
                    }else
                        pmap_info->map_col = num;
                }else{
                    if (num<10 || num>668 || num >= pmap_info->map_row * pmap_info->map_col){//����������Χ
                        input_no_error = false;
                        break;
                    }else
                        pmap_info->map_mines = num;
                }
            }
            break;
        case 4://�����Ͼ�
            save_no_error = !LoadSave(pmap_info, board);
            break;
        }

        if (!input_no_error)//����ʱ��������ʾ��
            MessageBoxA(getHWnd(), "���ֲ��ڷ�Χ�ڣ��������˴�����ַ���", "�������", MB_ICONWARNING | MB_APPLMODAL);
    }while (!input_no_error || !save_no_error);
    closegraph();//�رմ���

    return command==4 ? 1 : 0;//0Ϊ��������Ϸ��1Ϊ������Ϸ
}

//===================================================
//��������GameStart
//���ܣ�����ɨ����Ϸ����Ҫ����
//���������ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ�룬��Ϸ����(0Ϊ��������Ϸ��1Ϊ�����Ͼ���Ϸ�����ȡ�ļ�)
//����ֵ��0Ϊ�˳���1Ϊ�����Ѷ����ý���
//===================================================
int GameStart(MAP_INFO* pmap_info, int game_type)
{
    int game_width=10+2+18*pmap_info->map_col+3+140;
    int game_height=std::max(10+2+18*pmap_info->map_row+3+10, 263);

    initgraph(game_width, game_height, INIT_RENDERMANUAL);//��ʼ���˵����ڣ�Ϊ�ֶ�ˢ��ģʽ
    setcaption("��Ϸ");//���ñ���
    setbkcolor(EGERGB(204, 204, 204));//���ñ���ɫ

    PIMAGE game_img[18];//���������ز˵�����ͼƬ
    LoadGameImage(game_img);

    RectButton game_button[6]={{game_width-125,  90, 50, 25, false, "����"},
                               {game_width-65 ,  90, 50, 25, false, "����"},
                               {game_width-125, 130, 50, 25, false, "����"},
                               {game_width-65 , 130, 50, 25, false, "�˳�"},
                               {game_width-125, 170, 50, 25, false, "����"},
                               {game_width-65 , 170, 50, 25, false, "�߷ְ�"}};
    //������ť���飬0Ϊ���԰�ť��1Ϊ�����Ѷ�ѡ��ť��2Ϊ���水ť��3Ϊ�˳���ť��4Ϊ������ť��5Ϊ�����а�ť

    RANK_INFO rank_info[3];//����������Ϣ����
    LoadRank(rank_info);

    int command;//�洢�û�����İ�ť��-1Ϊδ������0Ϊ���ԣ�1Ϊ���أ�2Ϊ���棬3Ϊ�˳���4Ϊ������5Ϊ���а�
    MAP_POS act_pos;//�洢�û�������λ�ö�Ӧ�ĵ�ͼ����
    int game_state;//������Ϸ����״̬��0Ϊ��Ϸ�У�1Ϊ������2Ϊʤ��
    bool mine_is_set;

    do{//��Ϸѭ��
        command = -1;
        game_state = 0;
        int current_runtime = 0;
        bool mouse_is_down=false, dead_sound_is_played=false, game_is_saved=false;
        int start_time = -1, end_time;//��¼��Ϸ��ʼʱ�������ʱ��

        if (game_type == 0){//����Ĭ����Ϸ
            mine_is_set = false;
            pmap_info->map_flag = pmap_info->map_open = pmap_info->run_time = 0;
            InitialMap();
        }else{//ʹ�ô浵��Ϸ
            mine_is_set = true;
            game_type = 0;
        }
        current_runtime = pmap_info->run_time;
        PlaySound(TEXT("resource\\start.wav"),nullptr,SND_ASYNC);

        for (; command!=0 && command!=1 && command!=3; delay_fps(60)){//��ͼѭ��
            command = -1;

            mouse_msg msg;
            while (mousemsg()){
                msg = getmouse();//��ȡ����¼�

                // �ж���갴�����
                if (msg.is_down())
                    mouse_is_down = true;
                if (msg.is_up())
                    mouse_is_down = false;

                command = MouseButtonEventProcess(msg, game_button, 6);//������갴ť�¼�
                if (game_state == 0)
                    act_pos = MouseMapEventProcess(msg, &mine_is_set, &game_state, pmap_info);//������������¼�
            }

            if (start_time==-1 && mine_is_set)
                start_time = time(0);//��Ϸ��ʼ��(�û���������׺�)����¼��ʼʱ��

            if (game_state == 0 && pmap_info->map_mines == pmap_info->map_row*pmap_info->map_col - pmap_info->map_open){
                //��Ϸû��ʧ�ܣ��ҵ�ͼ��ʣ��ĸ�����������
                game_state = 2;//��Ϸʤ��
                end_time = time(0);//��¼��Ϸ����ʱ��
                PlaySound(TEXT("resource\\winner.wav"),nullptr,SND_ASYNC);
                RankUpdate(rank_info, pmap_info, end_time-start_time);
            }

            if (game_state == 1 && !dead_sound_is_played){//��Ϸʧ�ܺ���������Чû�в���
                end_time = time(0);//��¼��Ϸ����ʱ��
                PlaySound(TEXT("resource\\dead.wav"),nullptr,SND_ASYNC);//����������Ч
                dead_sound_is_played = true;
            }

            cleardevice();//����
            DrawBoundary(pmap_info);//���Ʒֽ���
            DrawImage(game_img, pmap_info, game_state);//���Ƹ���ͼƬ
            DrawEmoji(game_img, act_pos.is_legal(pmap_info) && mouse_is_down, game_state, pmap_info->map_col);//����emoji
            DrawButton(game_button, 6, 18);//���ư�ť

            setbkmode(TRANSPARENT);//�������ֱ���͸��
            setcolor(BLACK);//����������ɫ
            setfont(18, 0, "΢���ź�");//��������
            settextjustify(CENTER_TEXT, CENTER_TEXT);//����������Ϊ��������ʾ
            xyprintf(game_width-70, 220, "ʱ�䣺%d", mine_is_set ? ((game_state==0 ? time(0) : end_time) - start_time + current_runtime) : 0);//��������ʱ��
            xyprintf(game_width-70, 240, "ʣ�ࣺ%d", pmap_info->map_mines - pmap_info->map_flag);//����ʣ������(ʵ������-������)

            switch (command){
            case 2://ѡ���˱��水ť
                if (game_state==0 && mine_is_set){//����Ϸ���ڽ��У���û�н���ʱ�����ܽ��б���
                    pmap_info->run_time += time(0) - start_time;//д����Ϸʱ��
                    SaveGame(pmap_info, board);
                    game_is_saved = true;
                }else
                    MessageBoxA(getHWnd(), "ֻ�ܱ����Ѿ���ʼ������δ��������Ϸ��", "����", MB_ICONWARNING | MB_APPLMODAL);
                break;
            case 3://ѡ�����˳���ť
                if (game_state==0 && mine_is_set && !game_is_saved)
                    if (IDYES == MessageBoxA(getHWnd(), "��Ϸ��δ���棬��Ҫ������Ϸ��", "ע��", MB_ICONQUESTION | MB_APPLMODAL | MB_YESNO)){
                        pmap_info->run_time += time(0) - start_time;//д����Ϸʱ��
                        SaveGame(pmap_info, board);
                }
                break;
            case 4://ѡ���˰�����ť
                MessageBoxA(getHWnd(), "��Ϸ����:\n����������δ�򿪸���:\n"
                                        "\t�򿪸���(���ص��ĵ�һ������)\n"
                                        "��������������:\n"
                                        "\t���ܱ���������������ʱ,���ܱ߸���\n"
                                        "����Ҽ�����δ�򿪸���:\n"
                                        "\t�ı���(��->����->�ʺ�,ѭ��)\n\n"
                                        "���в�����������̧��ʱ�Ż����(�к�ڵĻ���)\n"
                                        "ף����Ϸ���!", "����", MB_ICONASTERISK | MB_APPLMODAL);
                break;
            case 5://ѡ���˸߷ְ�ť
                char buffer[256];
                sprintf(buffer, "�Ѷ�  �û���      \tʱ��\n"
                                "����  %-16s\t%d\n"
                                "�м�  %-16s\t%d\n"
                                "�߼�  %-16s\t%d", \
                    rank_info[0].username, rank_info[0].time, \
                    rank_info[1].username, rank_info[1].time, \
                    rank_info[2].username, rank_info[2].time);
                MessageBoxA(getHWnd(), buffer, "�߷ְ�", MB_APPLMODAL);
            }
        }
    }while (command == 0);//ѡ�����ʱ�����¿�ʼѭ��

    closegraph();//�رղ˵�����
    ReleaseImage(game_img, 18);//�ͷ�ͼƬ�ڴ�
    return command;
}

//===================================================
//��������IsInBottonRange
//���ܣ��ж������Ƿ��ڰ�ť��Χ��
//�����������Ҫ�жϵ�����(x��yֵ)(int, int)������Ҫ�жϵİ�ť(RectButton*)
//����ֵ��(bool)���������Ƿ��ڰ�ť��Χ��
//===================================================
bool IsInBottonRange(int x, int y, const RectButton* button)
{
    return (x >= button->x) && (x < button->x + button->width) && (y >= button->y) && (y < button->y + button->height);
}

//===================================================
//��������DrawButton
//���ܣ���ָ�������С�������а�ť
//�����������ť����(RectButton*)����ť����(int)�������С(int)
//����ֵ����
//===================================================
void DrawButton(const RectButton* button, int n, int font_size)
{
    extern PIMAGE button_img[2];

    setbkmode(TRANSPARENT);//�������ֱ���͸��
    setcolor(BLACK);//����������ɫ
    setfont(font_size, 0, "΢���ź�");//��������
    settextjustify(CENTER_TEXT, CENTER_TEXT);//����������Ϊ��������ʾ

    for (int i = 0; i < n; i++) {
        int x = button[i].x + button[i].width/2;//��ť���ĵ�x����
        int y = button[i].y + button[i].height/2;//��ť���ĵ�y����

		if (button[i].is_press){
			putimage(button[i].x, button[i].y, button[i].width, button[i].height, button_img[1], 0, 0, 759, 381);
			outtextxy(x, y+button[i].height/18, button[i].label);
            //���ư��µİ�ť
		}else{
			putimage(button[i].x, button[i].y, button[i].width, button[i].height, button_img[0], 0, 0, 759, 381);
			outtextxy(x, y, button[i].label);
            //���Ƶ���İ�ť
		}
	}
}

//===================================================
//��������SearchButton
//���ܣ�����������������Ӧ�İ�ťid
//�������������x��y(int, int)����ť����(RectButton*)����ť����(int)
//����ֵ��������������Ӧ�İ�ťid(int)��-1Ϊ�޶�Ӧ��ť
//===================================================
int SearchButton(int x, int y, const RectButton* button, int n)
{
	for (int i = 0; i < n; i++){
		if (IsInBottonRange(x, y, button + i)){
			return i;//�˳����Ѿ���⵽������İ�ť���ټ��
		}
	}
	return -1;
}

//===================================================
//��������MouseButtonEventProcess
//���ܣ���������¼�����ӳ�ڰ�ť��
//�����������ť����(RectButton*)����ť����(int)
//����ֵ���û�ѡ��İ�ťid(int)��NONE(-1)Ϊδѡ��
//===================================================
int MouseButtonEventProcess(mouse_msg msg, RectButton* button, int n)
{
    static bool mouse_is_down = false;
    static int pressed_button = NONE;
    int id = NONE;

    // �ж��������������
	if (msg.is_left()){
		if (msg.is_down())
            mouse_is_down = true;
        if (msg.is_up())
            mouse_is_down = false;
    }
    if (mouse_is_down){
        int select_button = SearchButton(msg.x, msg.y, button, n);//������갴��ʱ��Ӧ�İ�ť

        if (select_button != pressed_button){//��������ǰ���µİ�ť
            if (pressed_button != NONE)
                button[pressed_button].is_press = false;//��ǰ���µİ�ť����
            pressed_button = select_button;
            if (pressed_button != NONE)
                button[pressed_button].is_press = true;//���ڶ�Ӧ�İ�ť����
        }
    }else{//��굯��ʱ�����ض�Ӧ�İ�ťidֵ
        id = pressed_button;
        if (pressed_button != NONE)
            button[pressed_button].is_press = false;//��ť����
        pressed_button = NONE;//��Ȼ��ʱû�а�ť������
    }
    return id;
}

//===================================================
//��������MouseMapEventProcess
//���ܣ���������¼�����ӳ�ڵ�ͼ��
//��������������Ϣ�����Ƿ������£�ָ����Ϸ״̬��ָ�룬ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ��
//����ֵ�������Ϣ�����λ�ö�Ӧ�ĵ�ͼ����(MAP_POS)
//===================================================
MAP_POS MouseMapEventProcess(mouse_msg msg, bool* map_is_set, int* game_state, MAP_INFO* pmap_info)
{
    static bool mouse_is_down = false;
    static MAP_POS pressed_pos(0, 0);
    static MAP_POS act_pos(0, 0);

    // �ж���갴�����
	if (msg.is_down())
        mouse_is_down = true;
    if (msg.is_up())
        mouse_is_down = false;

    if (mouse_is_down){
        MAP_POS select_pos = MouseToPos(msg);//������갴��ʱ��Ӧ�ĵ�ͼ����

        if (select_pos != pressed_pos){//��������ǰ���µĵ�ͼ����
			if (pressed_pos.is_legal(pmap_info))
                board[pressed_pos.row][pressed_pos.col].is_down = 0;//��ǰ���µĵ�ͼ�����Ӧ������
            pressed_pos = select_pos;
            if (pressed_pos.is_legal(pmap_info))
                board[pressed_pos.row][pressed_pos.col].is_down = 1;//���ڶ�Ӧ�ĵ�ͼ�����Ӧ������
        act_pos = pressed_pos;
		}
	}else{//��굯��ʱ�����ݼ�λ(����)��ִ�в����������ز����ĵ�ͼ����
        act_pos = pressed_pos;
        if (pressed_pos.is_legal(pmap_info)){
            board[pressed_pos.row][pressed_pos.col].is_down = 0;//������
            pressed_pos = MAP_POS(0, 0);//��Ȼ��ʱû�����񱻰���

            if (msg.is_left()){//��������δ�򿪵ĸ��ӣ����ߴ��ܱ߸��ӣ����ҽ����ܱ����������ڸø��ܱߵ�����
                if (!*map_is_set){
                    SetMines(act_pos, pmap_info);
                    *map_is_set = true;
                }
                if (board[act_pos.row][act_pos.col].is_open == 0)
                    OpenBlock(act_pos, game_state, pmap_info);
                else
                    OpenSurround(act_pos, game_state, pmap_info);
            }else if (msg.is_right())//����Ҽ��ı���
                ChangeState(&board[act_pos.row][act_pos.col], &(pmap_info->map_flag));
        }
    }
    return act_pos;
}

//===================================================
//��������DrawBoundary
//���ܣ���������
//���������ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ��
//����ֵ����
//===================================================
void DrawBoundary(MAP_INFO* pmap_info)
{
    int map_row = pmap_info->map_row;
    int map_col = pmap_info->map_col;
    setcolor(EGERGB(128, 128, 128));
    setlinewidth(1);
    int point_pair1[16]={10, 10, 10, 10+2+18*map_row+2,
                        11, 10, 11, 10+2+18*map_row+1,
                        10, 10, 10+2+18*map_col+2, 10,
                        10, 11, 10+2+18*map_col+1, 11};
    drawlines(4, point_pair1);//�����ϱ߽���

    for (int i=0; i<=map_col; i++)
        line(12+i*18, 12, 12+i*18, 12+map_row*18);//����������
    for (int i=0; i<=map_row; i++)
        line(12, 12+i*18, 12+map_col*18, 12+i*18);//����������

    setcolor(EGERGB(255, 255, 255));
    int point_pair2[16]={11, 10+2+18*map_row+1, 12+map_col*18+2, 10+2+18*map_row+1,
                        10, 10+2+18*map_row+2, 12+map_col*18+2, 10+2+18*map_row+2,
                        12+map_col*18+1, 11, 12+map_col*18+1, 10+2+18*map_row+2,
                        12+map_col*18+2, 10, 12+map_col*18+2, 10+2+18*map_row+2};
    drawlines(4, point_pair2);//�����±߽���
}

//===================================================
//��������DrawImage
//���ܣ���������ͼƬ
//�����������ϷͼƬ����(PIMAGE*)��ָ���ͼ��Ϣ�ṹ��Ľṹ��ָ�룬��Ϸ����״̬
//����ֵ����
//===================================================
void DrawImage(PIMAGE* game_img, MAP_INFO* pmap_info, int game_state)
{
    for (int i=1; i<=pmap_info->map_row; i++){
        for (int j=1; j<=pmap_info->map_col; j++){
            int x, y, img_type;
            PosToMouse(MAP_POS(i, j), &x, &y);

            if (board[i][j].is_open == 0){//����û�б���ʱ

                switch (board[i][j].state){
                case 0://û�б��ʱ
                    if (game_state == 0)//��Ϸ���ڽ���ʱ
                        img_type = board[i][j].is_down ? 0 : BLANK;//δ�򿪵ĸ��ӱ�����ʱ��չʾΪ0�׸���δ���£�չʾΪδ�򿪸�
                    else if (game_state == 1)//��Ϸʧ�ܺ�
                        img_type = (board[i][j].num == 15) ? MINE : BLANK;//δ�򿪵ĺ��׸�չʾΪ�׸���δ���ף�չʾΪδ�򿪸�
                    else//��Ϸʤ����
                        img_type = BLANK;//δ�򿪸��չʾΪδ�򿪸�
                    break;
                case 1://��־Ϊ����ʱ
                    if (game_state == 1)//��Ϸʧ�ܺ�
                        img_type = (board[i][j].num != 15) ? MISTAKE : MINE;//��Ϊ���ĵĸ���û�к��ף�չʾΪ����������ף�չʾΪ�׸�
                    else//��Ϸ�������л�ʤ����
                        img_type = FLAG;//��Ϊ���ĵĸ���չʾΪ����
                    break;
                case 2://���Ϊ�ʺź�
                    img_type = (game_state == 1 && board[i][j].num == 15) ? MINE : QUESTION;//��Ϸʧ���Һ���ʱ��չʾΪ�׸񣬷���չʾΪ�ʺ�
                    break;
                }

            }else//���ӱ��򿪺�
                img_type = (board[i][j].num != 15) ? board[i][j].num : BLOOD;//�������ף�չʾΪ���ָ񣬷���չʾΪ���׸�

            putimage(x, y, game_img[img_type]);
        }
    }
}

//===================================================
//��������DrawEmoji
//���ܣ���������ͼƬ
//�����������ϷͼƬ����(PIMAGE*)���Ƿ�չʾ���ȵĲ���ֵ(bool)����Ϸ����״̬����ͼ������
//����ֵ����
//===================================================
void DrawEmoji(PIMAGE* game_img, bool is_surprised, int game_state, int map_col)
{
    int emoji_type;
    switch (game_state){
    case 0://��Ϸ��������
        emoji_type = is_surprised ? SURPRISE : SMILE;
        break;
    case 1://��Ϸʧ��
        emoji_type = DEAD;
        break;
    case 2://��Ϸʤ��
        emoji_type = WIN;
        break;
    }
    putimage_withalpha(NULL, game_img[emoji_type], 10+2+18*map_col+3+140 - 100, 15);
}
