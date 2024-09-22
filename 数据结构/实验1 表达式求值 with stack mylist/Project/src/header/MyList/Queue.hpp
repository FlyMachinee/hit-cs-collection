#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include "DynamicLinkList.hpp"

//队列类（用带头结点的单向链表实现）
template <typename Elem>
class Queue
{
private:
    DynamicLinkList<Elem>* list;

    //动态链表类中没有尾指针成员，在队列中需要，故补充
    DynamicNode<Elem>* end = nullptr;

public:
    Queue();
    ~Queue();

    //------------------------------------
    //自身独有的方法
    //------------------------------------    

    // 尾插法，在队尾插入元素
    void push(const Elem& obj);

    // 从队头弹出元素
    void pop();

    // 读取队头元素
    const Elem& front() const;

    // 查看队列元素个数
    int size() const;

    // 判断队列是否为空
    bool empty() const;

    // 遍历元素输出，以separator为分隔符
    void traverse(char separator) const;
};

#include "Queue.cpp"

#endif