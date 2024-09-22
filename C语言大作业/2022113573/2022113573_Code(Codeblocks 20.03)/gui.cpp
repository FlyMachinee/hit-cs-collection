#include "gui.h"
#include "load.h"
#include "calc.h"
#include <ege/sys_edit.h>

extern BLOCK board[26][32];//引用外部变量

//===================================================
//函数名：ShowMenu
//功能：显示菜单，及其按钮与对应功能
//输入参数：无
//返回值：用户触发按钮的id(int)
//===================================================
int ShowMenu(void)
{
    initgraph(MENU_WIDTH, MENU_HEIGHT, INIT_RENDERMANUAL | INIT_WITHLOGO);//初始化菜单窗口，为手动刷新模式
    setcaption("菜单");//设置标题

    PIMAGE menu_background = newimage();//创建并加载菜单背景图片
    getimage(menu_background, "resource\\menu_background.png");

    RectButton menu_button[2]={{88       , MENU_HEIGHT-45-100, 210, 100, false, "游 玩"},
                               {88+210+44, MENU_HEIGHT-45-100, 210, 100, false, "退 出"}};
    //创建按钮数组，0为游玩按钮，1为退出按钮

    int command = -1;//存储用户点击的按钮，-1为未操作，0为游玩，1为退出

    for (; command==-1; delay_fps(60)){//绘图循环
        mouse_msg msg;
        while (mousemsg()){
            msg = getmouse();
            command = MouseButtonEventProcess(msg, menu_button, 2);//处理鼠标事件
        }

		cleardevice();//清屏
        putimage(0, 0, menu_background);//绘制背景图片
		DrawButton(menu_button, 2, 50);//绘制按钮
    }
    closegraph();//关闭菜单窗口
    ReleaseImage(&menu_background, 1);//释放图片内存
    return command;
}

//===================================================
//函数名：GetInfo
//功能：显示选择菜单，及其按钮与对应功能，主要功能是获取游戏地图的数据
//输入参数：指向地图信息结构体的结构体指针
//返回值：0为开启新游戏，1为继续游戏
//===================================================
int GetInfo(MAP_INFO* pmap_info)
{
    initgraph(SELECT_WIDTH, SELECT_HEIGHT, INIT_RENDERMANUAL);//初始化窗口，为手动刷新模式
    setcaption("难度设置");//设置标题
    setbkcolor(EGERGB(204, 204, 204));//设置背景色

    sys_edit input_box[3];
    for (int i=0; i<3; i++){
        input_box[i].create(false);
        input_box[i].move(408, 54+i*(26+27));
        input_box[i].size(18 * 3, 18 + 8);
        input_box[i].setmaxlen(3);
        input_box[i].setfont(18, 0, "宋体");
        input_box[i].visible(true);
    }
    //创建并初始化输入框数组，0为输入地图行数，1为输入地图列数，2为输入地图雷数

    RectButton select_button[5]={{40     , 30,           100, 50, false, "初级"},
                                 {40     , 30+50+15,     100, 50, false, "中级"},
                                 {40     , 30+50*2+15*2, 100, 50, false, "高级"},
                                 {240-50 , 30+50+15,     100, 50, false, "自定义"},
                                 {620-130, 30+50+15,     100, 50, false, "读取存档"}};
    //创建按钮数组，0为初级按钮，1为中级按钮，2为高级按钮，3为自定义按钮，4为读取存档按钮

    int command;//存储用户点击的按钮，-1为未操作，0为初级按钮，1为中级按钮，2为高级按钮，3为自定义按钮，4为读取存档按钮
    bool input_no_error, save_no_error;//记录自定义内容是否输入正确
    do{
        input_no_error = save_no_error = true;
        command = -1;

        for (int i=0; i<3; i++)
            input_box[i].settext("");//清空输入框

        for (; command==-1; delay_fps(60)){//绘图循环
            mouse_msg msg;
            while (mousemsg()){
                msg = getmouse();//获取鼠标事件
                command = MouseButtonEventProcess(msg, select_button, 5);//处理鼠标按钮事件
            }

            cleardevice();//清屏

            DrawButton(select_button, 5, 25);//绘制按钮
            setbkmode(TRANSPARENT);//设置文字背景透明
            setfont(18, 0, "宋体");//设置字体
            settextjustify(RIGHT_TEXT, CENTER_TEXT);//对齐模式：水平右对齐，垂直居中
            outtextxy(408, 54+0*(26+27)+13, "高度(9-24)");
            outtextxy(408, 54+1*(26+27)+13, "宽度(9-30)");
            outtextxy(408, 54+2*(26+27)+13, "雷数(10-668)");
        }

        switch (command){//根据指令设置难度
        case 0://初级
            pmap_info->map_row = 9;
            pmap_info->map_col = 9;
            pmap_info->map_mines = 10;
            break;
        case 1://中级
            pmap_info->map_row = 16;
            pmap_info->map_col = 16;
            pmap_info->map_mines = 40;
            break;
        case 2://高级
            pmap_info->map_row = 16;
            pmap_info->map_col = 30;
            pmap_info->map_mines = 99;
            break;
        case 3://自定义
            char str_buffer[8];
            for (int i=0; i<3; i++){//获取三个输入框的内容
                input_box[i].gettext(8, str_buffer);
                int num;

                if (1 != sscanf(str_buffer, "%d", &num)){
                    input_no_error = false;
                    break;
                }

                if (i==0){
                    if (num<9 || num>24){//行数超出范围
                        input_no_error = false;
                        break;
                    }else
                        pmap_info->map_row = num;
                }else if (i==1){
                    if (num<9 || num>30){//列数超出范围
                        input_no_error = false;
                        break;
                    }else
                        pmap_info->map_col = num;
                }else{
                    if (num<10 || num>668 || num >= pmap_info->map_row * pmap_info->map_col){//雷数超出范围
                        input_no_error = false;
                        break;
                    }else
                        pmap_info->map_mines = num;
                }
            }
            break;
        case 4://继续上局
            save_no_error = !LoadSave(pmap_info, board);
            break;
        }

        if (!input_no_error)//出错时，弹出提示框
            MessageBoxA(getHWnd(), "数字不在范围内，或输入了错误的字符！", "输入错误", MB_ICONWARNING | MB_APPLMODAL);
    }while (!input_no_error || !save_no_error);
    closegraph();//关闭窗口

    return command==4 ? 1 : 0;//0为开启新游戏，1为继续游戏
}

//===================================================
//函数名：GameStart
//功能：包括扫雷游戏的主要内容
//输入参数：指向地图信息结构体的结构体指针，游戏类型(0为开启新游戏；1为继续上局游戏，需读取文件)
//返回值：0为退出，1为返回难度设置界面
//===================================================
int GameStart(MAP_INFO* pmap_info, int game_type)
{
    int game_width=10+2+18*pmap_info->map_col+3+140;
    int game_height=std::max(10+2+18*pmap_info->map_row+3+10, 263);

    initgraph(game_width, game_height, INIT_RENDERMANUAL);//初始化菜单窗口，为手动刷新模式
    setcaption("游戏");//设置标题
    setbkcolor(EGERGB(204, 204, 204));//设置背景色

    PIMAGE game_img[18];//创建并加载菜单背景图片
    LoadGameImage(game_img);

    RectButton game_button[6]={{game_width-125,  90, 50, 25, false, "重置"},
                               {game_width-65 ,  90, 50, 25, false, "返回"},
                               {game_width-125, 130, 50, 25, false, "保存"},
                               {game_width-65 , 130, 50, 25, false, "退出"},
                               {game_width-125, 170, 50, 25, false, "帮助"},
                               {game_width-65 , 170, 50, 25, false, "高分榜"}};
    //创建按钮数组，0为重试按钮，1为返回难度选择按钮，2为保存按钮，3为退出按钮，4为帮助按钮，5为打开排行榜按钮

    RANK_INFO rank_info[3];//定义排名信息数组
    LoadRank(rank_info);

    int command;//存储用户点击的按钮，-1为未操作，0为重试，1为返回，2为保存，3为退出，4为帮助，5为排行榜
    MAP_POS act_pos;//存储用户点击鼠标位置对应的地图坐标
    int game_state;//定义游戏运行状态，0为游戏中，1为死亡，2为胜利
    bool mine_is_set;

    do{//游戏循环
        command = -1;
        game_state = 0;
        int current_runtime = 0;
        bool mouse_is_down=false, dead_sound_is_played=false, game_is_saved=false;
        int start_time = -1, end_time;//记录游戏开始时间与结束时间

        if (game_type == 0){//进行默认游戏
            mine_is_set = false;
            pmap_info->map_flag = pmap_info->map_open = pmap_info->run_time = 0;
            InitialMap();
        }else{//使用存档游戏
            mine_is_set = true;
            game_type = 0;
        }
        current_runtime = pmap_info->run_time;
        PlaySound(TEXT("resource\\start.wav"),nullptr,SND_ASYNC);

        for (; command!=0 && command!=1 && command!=3; delay_fps(60)){//绘图循环
            command = -1;

            mouse_msg msg;
            while (mousemsg()){
                msg = getmouse();//获取鼠标事件

                // 判断鼠标按下与否
                if (msg.is_down())
                    mouse_is_down = true;
                if (msg.is_up())
                    mouse_is_down = false;

                command = MouseButtonEventProcess(msg, game_button, 6);//处理鼠标按钮事件
                if (game_state == 0)
                    act_pos = MouseMapEventProcess(msg, &mine_is_set, &game_state, pmap_info);//处理鼠标网格事件
            }

            if (start_time==-1 && mine_is_set)
                start_time = time(0);//游戏开始后(用户点击、埋雷后)，记录开始时间

            if (game_state == 0 && pmap_info->map_mines == pmap_info->map_row*pmap_info->map_col - pmap_info->map_open){
                //游戏没有失败，且地图中剩余的格数等于雷数
                game_state = 2;//游戏胜利
                end_time = time(0);//记录游戏结束时间
                PlaySound(TEXT("resource\\winner.wav"),nullptr,SND_ASYNC);
                RankUpdate(rank_info, pmap_info, end_time-start_time);
            }

            if (game_state == 1 && !dead_sound_is_played){//游戏失败后，且死亡音效没有播放
                end_time = time(0);//记录游戏结束时间
                PlaySound(TEXT("resource\\dead.wav"),nullptr,SND_ASYNC);//播放死亡音效
                dead_sound_is_played = true;
            }

            cleardevice();//清屏
            DrawBoundary(pmap_info);//绘制分界线
            DrawImage(game_img, pmap_info, game_state);//绘制格子图片
            DrawEmoji(game_img, act_pos.is_legal(pmap_info) && mouse_is_down, game_state, pmap_info->map_col);//绘制emoji
            DrawButton(game_button, 6, 18);//绘制按钮

            setbkmode(TRANSPARENT);//设置文字背景透明
            setcolor(BLACK);//设置字体颜色
            setfont(18, 0, "微软雅黑");//设置字体
            settextjustify(CENTER_TEXT, CENTER_TEXT);//文字以坐标为中心来显示
            xyprintf(game_width-70, 220, "时间：%d", mine_is_set ? ((game_state==0 ? time(0) : end_time) - start_time + current_runtime) : 0);//绘制所用时间
            xyprintf(game_width-70, 240, "剩余：%d", pmap_info->map_mines - pmap_info->map_flag);//绘制剩余雷数(实际雷数-旗帜数)

            switch (command){
            case 2://选择了保存按钮
                if (game_state==0 && mine_is_set){//当游戏正在进行，且没有结束时，才能进行保存
                    pmap_info->run_time += time(0) - start_time;//写入游戏时间
                    SaveGame(pmap_info, board);
                    game_is_saved = true;
                }else
                    MessageBoxA(getHWnd(), "只能保存已经开始，且尚未结束的游戏！", "警告", MB_ICONWARNING | MB_APPLMODAL);
                break;
            case 3://选择了退出按钮
                if (game_state==0 && mine_is_set && !game_is_saved)
                    if (IDYES == MessageBoxA(getHWnd(), "游戏尚未保存，需要保存游戏吗？", "注意", MB_ICONQUESTION | MB_APPLMODAL | MB_YESNO)){
                        pmap_info->run_time += time(0) - start_time;//写入游戏时间
                        SaveGame(pmap_info, board);
                }
                break;
            case 4://选择了帮助按钮
                MessageBoxA(getHWnd(), "游戏操作:\n鼠标左键单击未打开格子:\n"
                                        "\t打开格子(不必担心第一步踩雷)\n"
                                        "鼠标左键单击数字:\n"
                                        "\t当周边旗帜数等于数字时,打开周边格子\n"
                                        "鼠标右键单击未打开格子:\n"
                                        "\t改变标记(无->旗帜->问号,循环)\n\n"
                                        "所有操作仅当按键抬起时才会操作(有后悔的机会)\n"
                                        "祝您游戏愉快!", "帮助", MB_ICONASTERISK | MB_APPLMODAL);
                break;
            case 5://选择了高分榜按钮
                char buffer[256];
                sprintf(buffer, "难度  用户名      \t时间\n"
                                "初级  %-16s\t%d\n"
                                "中级  %-16s\t%d\n"
                                "高级  %-16s\t%d", \
                    rank_info[0].username, rank_info[0].time, \
                    rank_info[1].username, rank_info[1].time, \
                    rank_info[2].username, rank_info[2].time);
                MessageBoxA(getHWnd(), buffer, "高分榜", MB_APPLMODAL);
            }
        }
    }while (command == 0);//选择继续时，重新开始循环

    closegraph();//关闭菜单窗口
    ReleaseImage(game_img, 18);//释放图片内存
    return command;
}

//===================================================
//函数名：IsInBottonRange
//功能：判断坐标是否在按钮范围内
//输入参数：需要判断的坐标(x，y值)(int, int)，与需要判断的按钮(RectButton*)
//返回值：(bool)表明坐标是否在按钮范围内
//===================================================
bool IsInBottonRange(int x, int y, const RectButton* button)
{
    return (x >= button->x) && (x < button->x + button->width) && (y >= button->y) && (y < button->y + button->height);
}

//===================================================
//函数名：DrawButton
//功能：按指定字体大小绘制所有按钮
//输入参数：按钮数组(RectButton*)，按钮数量(int)，字体大小(int)
//返回值：无
//===================================================
void DrawButton(const RectButton* button, int n, int font_size)
{
    extern PIMAGE button_img[2];

    setbkmode(TRANSPARENT);//设置文字背景透明
    setcolor(BLACK);//设置字体颜色
    setfont(font_size, 0, "微软雅黑");//设置字体
    settextjustify(CENTER_TEXT, CENTER_TEXT);//文字以坐标为中心来显示

    for (int i = 0; i < n; i++) {
        int x = button[i].x + button[i].width/2;//按钮中心的x坐标
        int y = button[i].y + button[i].height/2;//按钮中心的y坐标

		if (button[i].is_press){
			putimage(button[i].x, button[i].y, button[i].width, button[i].height, button_img[1], 0, 0, 759, 381);
			outtextxy(x, y+button[i].height/18, button[i].label);
            //绘制按下的按钮
		}else{
			putimage(button[i].x, button[i].y, button[i].width, button[i].height, button_img[0], 0, 0, 759, 381);
			outtextxy(x, y, button[i].label);
            //绘制弹起的按钮
		}
	}
}

//===================================================
//函数名：SearchButton
//功能：搜索输入坐标所对应的按钮id
//输入参数：坐标x，y(int, int)，按钮数组(RectButton*)，按钮数量(int)
//返回值：输入坐标所对应的按钮id(int)，-1为无对应按钮
//===================================================
int SearchButton(int x, int y, const RectButton* button, int n)
{
	for (int i = 0; i < n; i++){
		if (IsInBottonRange(x, y, button + i)){
			return i;//退出，已经检测到，后面的按钮不再检测
		}
	}
	return -1;
}

//===================================================
//函数名：MouseButtonEventProcess
//功能：处理鼠标事件，反映在按钮上
//输入参数：按钮数组(RectButton*)，按钮数量(int)
//返回值：用户选择的按钮id(int)，NONE(-1)为未选择
//===================================================
int MouseButtonEventProcess(mouse_msg msg, RectButton* button, int n)
{
    static bool mouse_is_down = false;
    static int pressed_button = NONE;
    int id = NONE;

    // 判断鼠标左键按下与否
	if (msg.is_left()){
		if (msg.is_down())
            mouse_is_down = true;
        if (msg.is_up())
            mouse_is_down = false;
    }
    if (mouse_is_down){
        int select_button = SearchButton(msg.x, msg.y, button, n);//搜索鼠标按下时对应的按钮

        if (select_button != pressed_button){//若不是先前按下的按钮
            if (pressed_button != NONE)
                button[pressed_button].is_press = false;//先前按下的按钮弹起
            pressed_button = select_button;
            if (pressed_button != NONE)
                button[pressed_button].is_press = true;//现在对应的按钮按下
        }
    }else{//鼠标弹起时，返回对应的按钮id值
        id = pressed_button;
        if (pressed_button != NONE)
            button[pressed_button].is_press = false;//按钮弹起
        pressed_button = NONE;//显然这时没有按钮被按下
    }
    return id;
}

//===================================================
//函数名：MouseMapEventProcess
//功能：处理鼠标事件，反映在地图上
//输入参数：鼠标消息，雷是否已埋下，指向游戏状态的指针，指向地图信息结构体的结构体指针
//返回值：鼠标消息中鼠标位置对应的地图坐标(MAP_POS)
//===================================================
MAP_POS MouseMapEventProcess(mouse_msg msg, bool* map_is_set, int* game_state, MAP_INFO* pmap_info)
{
    static bool mouse_is_down = false;
    static MAP_POS pressed_pos(0, 0);
    static MAP_POS act_pos(0, 0);

    // 判断鼠标按下与否
	if (msg.is_down())
        mouse_is_down = true;
    if (msg.is_up())
        mouse_is_down = false;

    if (mouse_is_down){
        MAP_POS select_pos = MouseToPos(msg);//搜索鼠标按下时对应的地图坐标

        if (select_pos != pressed_pos){//若不是先前按下的地图坐标
			if (pressed_pos.is_legal(pmap_info))
                board[pressed_pos.row][pressed_pos.col].is_down = 0;//先前按下的地图坐标对应网格弹起
            pressed_pos = select_pos;
            if (pressed_pos.is_legal(pmap_info))
                board[pressed_pos.row][pressed_pos.col].is_down = 1;//现在对应的地图坐标对应网格按下
        act_pos = pressed_pos;
		}
	}else{//鼠标弹起时，根据键位(左右)来执行操作，并返回操作的地图坐标
        act_pos = pressed_pos;
        if (pressed_pos.is_legal(pmap_info)){
            board[pressed_pos.row][pressed_pos.col].is_down = 0;//网格弹起
            pressed_pos = MAP_POS(0, 0);//显然这时没有网格被按下

            if (msg.is_left()){//鼠标左键打开未打开的格子，或者打开周边格子，当且仅当周边旗帜数等于该格周边的雷数
                if (!*map_is_set){
                    SetMines(act_pos, pmap_info);
                    *map_is_set = true;
                }
                if (board[act_pos.row][act_pos.col].is_open == 0)
                    OpenBlock(act_pos, game_state, pmap_info);
                else
                    OpenSurround(act_pos, game_state, pmap_info);
            }else if (msg.is_right())//鼠标右键改变标记
                ChangeState(&board[act_pos.row][act_pos.col], &(pmap_info->map_flag));
        }
    }
    return act_pos;
}

//===================================================
//函数名：DrawBoundary
//功能：绘制网格
//输入参数：指向地图信息结构体的结构体指针
//返回值：无
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
    drawlines(4, point_pair1);//画左上边界线

    for (int i=0; i<=map_col; i++)
        line(12+i*18, 12, 12+i*18, 12+map_row*18);//画竖网格线
    for (int i=0; i<=map_row; i++)
        line(12, 12+i*18, 12+map_col*18, 12+i*18);//画横网格线

    setcolor(EGERGB(255, 255, 255));
    int point_pair2[16]={11, 10+2+18*map_row+1, 12+map_col*18+2, 10+2+18*map_row+1,
                        10, 10+2+18*map_row+2, 12+map_col*18+2, 10+2+18*map_row+2,
                        12+map_col*18+1, 11, 12+map_col*18+1, 10+2+18*map_row+2,
                        12+map_col*18+2, 10, 12+map_col*18+2, 10+2+18*map_row+2};
    drawlines(4, point_pair2);//画右下边界线
}

//===================================================
//函数名：DrawImage
//功能：绘制网格图片
//输入参数：游戏图片数组(PIMAGE*)，指向地图信息结构体的结构体指针，游戏运行状态
//返回值：无
//===================================================
void DrawImage(PIMAGE* game_img, MAP_INFO* pmap_info, int game_state)
{
    for (int i=1; i<=pmap_info->map_row; i++){
        for (int j=1; j<=pmap_info->map_col; j++){
            int x, y, img_type;
            PosToMouse(MAP_POS(i, j), &x, &y);

            if (board[i][j].is_open == 0){//格子没有被打开时

                switch (board[i][j].state){
                case 0://没有标记时
                    if (game_state == 0)//游戏还在进行时
                        img_type = board[i][j].is_down ? 0 : BLANK;//未打开的格子被按下时，展示为0雷格，若未按下，展示为未打开格
                    else if (game_state == 1)//游戏失败后
                        img_type = (board[i][j].num == 15) ? MINE : BLANK;//未打开的含雷格展示为雷格，若未含雷，展示为未打开格
                    else//游戏胜利后
                        img_type = BLANK;//未打开格均展示为未打开格
                    break;
                case 1://标志为旗帜时
                    if (game_state == 1)//游戏失败后
                        img_type = (board[i][j].num != 15) ? MISTAKE : MINE;//标为旗帜的格子没有含雷，展示为错误格，若含雷，展示为雷格
                    else//游戏正常运行或胜利后
                        img_type = FLAG;//标为旗帜的格子展示为旗帜
                    break;
                case 2://标记为问号后
                    img_type = (game_state == 1 && board[i][j].num == 15) ? MINE : QUESTION;//游戏失败且含雷时，展示为雷格，否则展示为问号
                    break;
                }

            }else//格子被打开后
                img_type = (board[i][j].num != 15) ? board[i][j].num : BLOOD;//若不是雷，展示为数字格，否则展示为红雷格

            putimage(x, y, game_img[img_type]);
        }
    }
}

//===================================================
//函数名：DrawEmoji
//功能：绘制网格图片
//输入参数：游戏图片数组(PIMAGE*)，是否展示惊讶的布尔值(bool)，游戏运行状态，地图的列数
//返回值：无
//===================================================
void DrawEmoji(PIMAGE* game_img, bool is_surprised, int game_state, int map_col)
{
    int emoji_type;
    switch (game_state){
    case 0://游戏正常进行
        emoji_type = is_surprised ? SURPRISE : SMILE;
        break;
    case 1://游戏失败
        emoji_type = DEAD;
        break;
    case 2://游戏胜利
        emoji_type = WIN;
        break;
    }
    putimage_withalpha(NULL, game_img[emoji_type], 10+2+18*map_col+3+140 - 100, 15);
}
