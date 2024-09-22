#ifndef STATIC_LINK_LIST_HPP_INCLUDED
#define STATIC_LINK_LIST_HPP_INCLUDED

#include "AbstractLinkList.hpp"

// 静态单向节点类
template <typename Elem>
class StaticNode
{
public:
    Elem data;
    int next;
};

// 静态单向链表类
template <typename Elem>
class StaticLinkList : public AbstractLinkList<Elem, int>
{
private:
    // 链表头指针
    int head_ptr;

    // 空闲空间池，由所有同类型静态链表类共享
    static StaticNode<Elem> *space;
    // 判断空间池是否存在，默认值为0
    static bool space_exist;
    // 空间池指针，用于管理空间
    static int space_ptr;
    // 空间池的大小
    static int space_size;

public:
    StaticLinkList();
    ~StaticLinkList();

    //-----------------------------------
    // 对父类的重写
    //-----------------------------------

    // 返回p指针指向节点的数据的引用
    Elem &data(int p) const;

    // 返回指定位置的指针域的引用（即后继）
    int &_next(int p) const;

    // 返回表头
    int begin() const;

    // 返回空指针
    int null() const;

    // 申请节点空间，返回节点的地址
    int newNode();

    // 释放节点空间
    void deleteNode(int p);

    //-----------------------------------
    // 子类独有的方法
    //-----------------------------------

    // 对空间池进行初始化
    static void initSpace(int max_size);

    // 清空空间池
    static void clearSpace();

    // 展示静态链表空间池
    static void showSpace(int len = space_size);
};

#include "StaticLinkList.cpp"

#endif