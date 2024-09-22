#include "hanoi.h"

//文件名:stack.cpp
//内容：定义了MyStack类中的方法



//***************************************
//方法名：MyStack
//类：MyStack
//形参：
//返回值：
//作用：构造函数
//***************************************
MyStack::MyStack()
{
    memset(data, 0, MAX_STACK * sizeof(int));
    top = 0;
}


//***************************************
//方法名：init
//类：MyStack
//形参：
//返回值：
//作用：初始化栈，即：栈清空，栈顶归零
//***************************************
void MyStack::init()
{
    memset(data, 0, MAX_STACK * sizeof(int));
    top = 0;
}


//***************************************
//方法名：init
//类：MyStack
//形参：int lvl(初始化的层数)
//返回值：
//作用：初始化栈，即：清空栈，再将lvl, lvl-1, lvl-2, ..., 3, 2, 1，这lvl个int值进行依次入栈
//***************************************
void MyStack::init(int lvl)
{
    init();
    for (int i = lvl; i >= 1; i--)
        push(i);
}


//***************************************
//方法名：getTop
//类：MyStack
//形参：
//返回值：栈顶元素，若栈空则返回-1
//作用：返回栈顶元素，若栈空则返回-1
//***************************************
int MyStack::getTop()
{
    if (top != 0)
        return data[top - 1];
    else
        return -1;
}


//***************************************
//方法名：pop
//类：MyStack
//形参：
//返回值：栈顶元素，若栈空则返回-1
//作用：弹栈，清空栈顶，并返回栈顶元素，若栈空则返回-1
//***************************************
int MyStack::pop()
{
    if (top == 0)
    {
        return -1;
    }
    else
    {
        int tmp = data[--top];
        data[top] = 0;
        return tmp;
    }
}


//***************************************
//方法名：push
//类：MyStack
//形参：int ele
//返回值：压栈成功返回0，栈满返回-1
//作用：将ele值进行压栈，压栈成功返回0，栈满返回-1
//***************************************
int MyStack::push(int ele)
{
    if (top == MAX_STACK)
    {
        return -1;
    }
    else
    {
        data[top++] = ele;
        return 0;
    }
}


//***************************************
//方法名：showHorizontal
//类：MyStack
//形参：
//返回值：
//作用：将栈横向打印出来，从左至右，由栈底至栈顶，0元素视为" "
//***************************************
void MyStack::showHorizontal()
{
    for (int i = 0; i < 10; i++)
        if (data[i] == 0)
            cout << "  ";
        else
            cout << setw(2) << data[i];
}


//***************************************
//方法名：showVertical
//类：MyStack
//形参：int x, int y, 打印光标坐标
//返回值：
//作用：在光标处将栈纵向打印出来，从上至下，由栈顶至栈底，0元素视为" "
//***************************************
void MyStack::showVertical(int x, int y)
{
    for (int i = 9; i >= 0; i--)
    {
        cct_gotoxy(x, y + (9 - i));
        if (data[i] != 0)
            cout << "  " << data[i];
        else
            cout << "     ";
    }
}
