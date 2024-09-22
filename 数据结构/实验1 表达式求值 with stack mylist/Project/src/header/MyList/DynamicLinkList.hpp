#ifndef DYNAMIC_LINK_LIST_HPP_INCLUDED
#define DYNAMIC_LINK_LIST_HPP_INCLUDED

#include "AbstractLinkList.hpp"
#include <cstdlib>

// 动态单向节点类
template <typename Elem>
class DynamicNode
{
public:
    Elem data;
    DynamicNode<Elem> *next;
};

// 动态单向链表类
template <typename Elem>
class DynamicLinkList : public AbstractLinkList<Elem, DynamicNode<Elem> *>
{
private:
    // 链表头指针
    DynamicNode<Elem> *head_ptr;

public:
    DynamicLinkList();
    ~DynamicLinkList();

    //-----------------------------------
    // 对父类的重写
    // 父类：抽象单向链表类
    //-----------------------------------

    // 返回p指针指向节点的数据的引用
    Elem &data(DynamicNode<Elem> *p) const;

    // 返回指定位置的指针域的引用（即后继）
    DynamicNode<Elem> *&_next(DynamicNode<Elem> *p) const;

    // 返回表头
    DynamicNode<Elem> *begin() const;

    // 返回空指针
    DynamicNode<Elem> *null() const;

    // 申请节点空间，返回节点的地址
    DynamicNode<Elem> *newNode();

    // 释放节点空间
    void deleteNode(DynamicNode<Elem> *p);
};

#include "DynamicLinkList.cpp"

#endif