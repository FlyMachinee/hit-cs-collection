#include "load.h"

//===================================================
//函数名：LoadButtonImage
//功能：创建并加载按钮会使用到的图片
//输入参数：存放按钮图片的数组(PIMAGE*)
//返回值：无
//===================================================
void LoadButtonImage(PIMAGE* img_array)
{
    char name[2][16] = {"button_pop", "button_click"};
    for (int i=0; i<2; i++){
        char buf[64];
        sprintf(buf, "resource\\%s.png", name[i]);
        img_array[i] = newimage();
        if (grOk != getimage(img_array[i], buf)){
            MessageBoxA(getHWnd(), "图片资源加载失败！", "错误", MB_ICONWARNING | MB_APPLMODAL);
            exit(0);
        }
    }
}

//===================================================
//函数名：LoadGameImage
//功能：创建并加载游戏中会使用到的图片
//输入参数：存放按钮图片的数组(PIMAGE*)
//返回值：无
//===================================================
void LoadGameImage(PIMAGE* img_array)
{
    for (int i=0; i<19; i++)
        img_array[i] = newimage();

    for (int i=0; i<=8; i++){
        char str[40];
        sprintf(str, "resource\\%d.gif", i);
        if (grOk != getimage(img_array[i], str)){
            MessageBoxA(getHWnd(), "图片资源加载失败！", "错误", MB_ICONWARNING | MB_APPLMODAL);
            exit(0);
        }
    }
    char name[10][16] = {"blank.gif", "flag.gif", "question.gif", "mine.gif", "blood.gif", "mistake.gif", "smile.png", "surprise.png", "dead.png", "win.png"};
    for (int i=9; i<=18; i++){
        char buf[64];
        sprintf(buf, "resource\\%s", name[i-9]);
        if (grOk != getimage(img_array[i], buf)){
            MessageBoxA(getHWnd(), "图片资源加载失败！", "错误", MB_ICONWARNING | MB_APPLMODAL);
            exit(0);
        }
    }
}

//===================================================
//函数名：ReleaseImage
//功能：释放图片数组的内存
//输入参数：需要释放的图片数组(PIMAGE*)，图片数量(int)
//返回值：无
//===================================================
void ReleaseImage(PIMAGE* img_array, int n)
{
    for (int i=0; i<n; i++)
        delimage(img_array[i]);
}

//===================================================
//函数名：SaveGame
//功能：保存当前未完成的游戏
//输入参数：地图信息结构体的指针(MAP_INFO*)，地图本身(BLOCK(*)[32])
//返回值：0为保存成功，1为保存失败
//===================================================
int SaveGame(const MAP_INFO* pmap_info, const BLOCK board[][32])
{
    srand(time(0));
    FILE* fp = fopen("data\\save.txt", "w");
    if (fp == NULL){
        fclose(fp);
        MessageBoxA(getHWnd(), "存档保存失败", "警告", MB_ICONERROR | MB_APPLMODAL);
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
        MessageBoxA(getHWnd(), "存档保存成功", "成功", MB_ICONINFORMATION | MB_APPLMODAL);
        return 0;
    }
}

//===================================================
//函数名：LoadSave
//功能：加载存档信息
//输入参数：地图信息结构体的指针(MAP_INFO*)，地图本身(BLOCK(*)[32])
//返回值：0为加载成功，1为加载失败
//===================================================
int LoadSave(MAP_INFO* pmap_info, BLOCK board[][32])
{
    FILE* fp = fopen("data\\save.txt", "r");
    if (fp == NULL){
        fclose(fp);
        MessageBoxA(getHWnd(), "存档打开失败", "警告", MB_ICONERROR | MB_APPLMODAL);
        return 1;
    }else{
        int save_mines=0, save_flag=0, save_open=0;//记录存档实际含有的雷数，旗帜数与打开的格子数
        bool save_damaged = false;

        int a, b, c, d, e, f, g;
        if (7 != fscanf(fp, "%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &g) || a+b+c+d+e+f!=g)//读取地图基本信息
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
                if(1 != fscanf(fp, "%d", &key))//读取地图每格信息
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
            MessageBoxA(getHWnd(), "存档文件损坏，无法打开", "警告", MB_ICONERROR | MB_APPLMODAL);
            return 1;
        }else
            return 0;
    }
}


//===================================================
//函数名：RankUpdate
//功能：尝试更新排名信息
//输入参数：排名信息数组(RANK_INFO*)，地图信息结构体的指针(MAP_INFO*)，所用时间(int)
//返回值：无
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
//函数名：LoadRank
//功能：加载排名信息
//输入参数：排名信息数组(RANK_INFO*)
//返回值：无
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
//函数名：SaveRank
//功能：保存排名信息
//输入参数：排名信息数组(RANK_INFO*)
//返回值：无
//===================================================
void SaveRank(RANK_INFO* rank_info)
{
    FILE* fp = fopen("data\\rank.txt", "w");
    if (fp == NULL)
        MessageBoxA(getHWnd(), "排名保存失败", "警告", MB_ICONERROR | MB_APPLMODAL);
    else
        for (int i=0; i<3; i++){
            fprintf(fp, "%s\n", rank_info[i].username);
            fprintf(fp, "%d\n", rank_info[i].time);
        }
    fclose(fp);
}
