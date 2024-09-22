#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "SeqList.hpp"

// 顺序表实现栈
template <typename Elem>
class Stack
{
private:
    SeqList<Elem>* arr = nullptr;

public:
    Stack();
    ~Stack();

    //------------------------------------
    //自身独有的方法
    //------------------------------------    

    // 入栈
    void push(const Elem& obj);

    // 出栈
    void pop();

    // 栈顶元素
    const Elem& top() const;

    // 是否为空
    bool empty() const;

    // 栈大小
    int size() const;

    // 遍历元素输出，以separator为分隔符
    void traverse(char separator) const;
};

#include "Stack.cpp"

#endif