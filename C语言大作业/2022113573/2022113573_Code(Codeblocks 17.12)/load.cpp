#include "load.h"

//===================================================
//��������LoadButtonImage
//���ܣ����������ذ�ť��ʹ�õ���ͼƬ
//�����������Ű�ťͼƬ������(PIMAGE*)
//����ֵ����
//===================================================
void LoadButtonImage(PIMAGE* img_array)
{
    char name[2][16] = {"button_pop", "button_click"};
    for (int i=0; i<2; i++){
        char buf[64];
        sprintf(buf, "resource\\%s.png", name[i]);
        img_array[i] = newimage();
        if (grOk != getimage(img_array[i], buf)){
            MessageBoxA(getHWnd(), "ͼƬ��Դ����ʧ�ܣ�", "����", MB_ICONWARNING | MB_APPLMODAL);
            exit(0);
        }
    }
}

//===================================================
//��������LoadGameImage
//���ܣ�������������Ϸ�л�ʹ�õ���ͼƬ
//�����������Ű�ťͼƬ������(PIMAGE*)
//����ֵ����
//===================================================
void LoadGameImage(PIMAGE* img_array)
{
    for (int i=0; i<19; i++)
        img_array[i] = newimage();

    for (int i=0; i<=8; i++){
        char str[40];
        sprintf(str, "resource\\%d.gif", i);
        if (grOk != getimage(img_array[i], str)){
            MessageBoxA(getHWnd(), "ͼƬ��Դ����ʧ�ܣ�", "����", MB_ICONWARNING | MB_APPLMODAL);
            exit(0);
        }
    }
    char name[10][16] = {"blank.gif", "flag.gif", "question.gif", "mine.gif", "blood.gif", "mistake.gif", "smile.png", "surprise.png", "dead.png", "win.png"};
    for (int i=9; i<=18; i++){
        char buf[64];
        sprintf(buf, "resource\\%s", name[i-9]);
        if (grOk != getimage(img_array[i], buf)){
            MessageBoxA(getHWnd(), "ͼƬ��Դ����ʧ�ܣ�", "����", MB_ICONWARNING | MB_APPLMODAL);
            exit(0);
        }
    }
}

//===================================================
//��������ReleaseImage
//���ܣ��ͷ�ͼƬ������ڴ�
//�����������Ҫ�ͷŵ�ͼƬ����(PIMAGE*)��ͼƬ����(int)
//����ֵ����
//===================================================
void ReleaseImage(PIMAGE* img_array, int n)
{
    for (int i=0; i<n; i++)
        delimage(img_array[i]);
}

//===================================================
//��������SaveGame
//���ܣ����浱ǰδ��ɵ���Ϸ
//�����������ͼ��Ϣ�ṹ���ָ��(MAP_INFO*)����ͼ����(BLOCK(*)[32])
//����ֵ��0Ϊ����ɹ���1Ϊ����ʧ��
//===================================================
int SaveGame(const MAP_INFO* pmap_info, const BLOCK board[][32])
{
    srand(time(0));
    FILE* fp = fopen("data\\save.txt", "w");
    if (fp == NULL){
        fclose(fp);
        MessageBoxA(getHWnd(), "�浵����ʧ��", "����", MB_ICONERROR | MB_APPLMODAL);
        return 1;
    }else{
        fprintf(fp, "%d\n", EncryptNum(pmap_info->map_row));
        fprintf(fp, "%d\n", EncryptNum(pmap_info->map_col));
        fprintf(fp, "%d\n", EncryptNum(pmap_info->map_mines));
        fprintf(fp, "%d\n", EncryptNum(pmap_info->map_flag));
        fprintf(fp, "%d\n", EncryptNum(pmap_info->map_open));
        fprintf(fp, "%d\n", EncryptNum(pmap_info->run_time));
        fprintf(fp, "%d\n", EncryptNum(pmap_info->map_row) + EncryptNum(pmap_info->map_col) + EncryptNum(pmap_info->map_mines)\
                          + EncryptNum(pmap_info->map_flag) + EncryptNum(pmap_info->map_open) + EncryptNum(pmap_info->run_time));
        for (int i=1; i<=pmap_info->map_row; i++){
            for (int j=1; j<=pmap_info->map_col; j++){
                fprintf(fp, "%d\n", EncryptBlock(board[i][j]));
            }
        }
        fclose(fp);
        MessageBoxA(getHWnd(), "�浵����ɹ�", "�ɹ�", MB_ICONINFORMATION | MB_APPLMODAL);
        return 0;
    }
}

//===================================================
//��������LoadSave
//���ܣ����ش浵��Ϣ
//�����������ͼ��Ϣ�ṹ���ָ��(MAP_INFO*)����ͼ����(BLOCK(*)[32])
//����ֵ��0Ϊ���سɹ���1Ϊ����ʧ��
//===================================================
int LoadSave(MAP_INFO* pmap_info, BLOCK board[][32])
{
    FILE* fp = fopen("data\\save.txt", "r");
    if (fp == NULL){
        fclose(fp);
        MessageBoxA(getHWnd(), "�浵��ʧ��", "����", MB_ICONERROR | MB_APPLMODAL);
        return 1;
    }else{
        int save_mines=0, save_flag=0, save_open=0;//��¼�浵ʵ�ʺ��е���������������򿪵ĸ�����
        bool save_damaged = false;

        int a, b, c, d, e, f, g;
        if (7 != fscanf(fp, "%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &g) || a+b+c+d+e+f!=g)//��ȡ��ͼ������Ϣ
            save_damaged = true;
        else{
            pmap_info->map_row = DecryptNum(a);
            pmap_info->map_col = DecryptNum(b);
            pmap_info->map_mines = DecryptNum(c);
            pmap_info->map_flag = DecryptNum(d);
            pmap_info->map_open = DecryptNum(e);
            pmap_info->run_time = DecryptNum(f);
        }

        for (int i=1; i<=pmap_info->map_row && !save_damaged; i++){
            for (int j=1; j<=pmap_info->map_col && !save_damaged; j++){

                int key;
                if(1 != fscanf(fp, "%d", &key))//��ȡ��ͼÿ����Ϣ
                    save_damaged = true;
                board[i][j] = DecryptBlock(key);

                if (board[i][j].num == 15)
                    save_mines++;
                if (board[i][j].is_open == 1)
                    save_open++;
                if (board[i][j].state == 1)
                    save_flag++;
            }
        }

        if (save_mines!=pmap_info->map_mines || save_open!=pmap_info->map_open || save_flag!=pmap_info->map_flag)
            save_damaged = true;
        fclose(fp);

        if (save_damaged){
            MessageBoxA(getHWnd(), "�浵�ļ��𻵣��޷���", "����", MB_ICONERROR | MB_APPLMODAL);
            return 1;
        }else
            return 0;
    }
}


//===================================================
//��������RankUpdate
//���ܣ����Ը���������Ϣ
//���������������Ϣ����(RANK_INFO*)����ͼ��Ϣ�ṹ���ָ��(MAP_INFO*)������ʱ��(int)
//����ֵ����
//===================================================
void RankUpdate(RANK_INFO rank_info[3], const MAP_INFO* pmap_info, int time)
{
    int difficulty;
    if (pmap_info->map_row==9 && pmap_info->map_col==9 && pmap_info->map_mines==10)
        difficulty=0;
    else if (pmap_info->map_row==16 && pmap_info->map_col==16 && pmap_info->map_mines==40)
        difficulty=1;
    else if (pmap_info->map_row==16 && pmap_info->map_col==30 && pmap_info->map_mines==99)
        difficulty=2;
    else
        return;

    if (time <= rank_info[difficulty].time){
        char username[33];
        DWORD dwSize_username = 33;
        GetUserNameA(username, &dwSize_username);
        rank_info[difficulty].time = time;
        strcpy(rank_info[difficulty].username, username);
        SaveRank(rank_info);
    }
}


//===================================================
//��������LoadRank
//���ܣ�����������Ϣ
//���������������Ϣ����(RANK_INFO*)
//����ֵ����
//===================================================
void LoadRank(RANK_INFO* rank_info)
{
    FILE* fp = fopen("data\\rank.txt", "r");
    if (fp == NULL){
        for (int i=0; i<3; i++){
            strcpy(rank_info[i].username, "-");
            rank_info[i].time = 99999;
        }
    }else{
        for (int i=0; i<3; i++){
            fscanf(fp, "%s", rank_info[i].username);
            fscanf(fp, "%d", &rank_info[i].time);
        }
    }
    fclose(fp);
}

//===================================================
//��������SaveRank
//���ܣ�����������Ϣ
//���������������Ϣ����(RANK_INFO*)
//����ֵ����
//===================================================
void SaveRank(RANK_INFO* rank_info)
{
    FILE* fp = fopen("data\\rank.txt", "w");
    if (fp == NULL)
        MessageBoxA(getHWnd(), "��������ʧ��", "����", MB_ICONERROR | MB_APPLMODAL);
    else
        for (int i=0; i<3; i++){
            fprintf(fp, "%s\n", rank_info[i].username);
            fprintf(fp, "%d\n", rank_info[i].time);
        }
    fclose(fp);
}
