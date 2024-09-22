#ifndef LINKLIST_HPP_INCLUDED
#define LINKLIST_HPP_INCLUDED

#include "AbstractLinearList.hpp"
#include <cstdlib>

// 抽象单向链表类
template <typename Elem, typename Position>
class AbstractLinkList : public AbstractLinearList<Elem, Position>
{
public:
    // 纯虚析构函数
    virtual ~AbstractLinkList() = 0;

    //-----------------------------------
    // 以下方法须由子类重写
    // 子类：动态链表类，静态链表类
    //-----------------------------------

    // 返回p指针指向节点的数据的引用
    virtual Elem &data(Position p) const = 0;

    // 返回指定位置的指针域的引用（即后继）
    //_next返回左值，next返回右值（与父类兼容）
    // 在链表类中均使用_next
    virtual Position &_next(Position p) const = 0;

    // 返回表头
    virtual Position begin() const = 0;

    // 返回空指针
    virtual Position null() const = 0;

    // 申请节点空间，返回节点的地址
    virtual Position newNode() = 0;

    // 释放节点空间
    virtual void deleteNode(Position p) = 0;

    //------------------------------------
    // 由上述方法可实现的方法
    // 具体方法内部调用的方法由子类实现
    //------------------------------------

    // 返回指定位置的指针域的值（即后继）
    //_next返回左值，next返回右值（与父类兼容）
    Position next(Position p) const;

    // 返回p指针所指向下一个节点的数据的引用
    Elem &at(Position p) const;

    // 返回指定位置的前驱
    Position prior(Position p) const;

    // 返回表尾
    Position end() const;

    // 判断是否为空表
    bool empty() const;

    // 清空列表
    void clear();

    // 返回当前链表长度
    int length() const;

    // 在链表中插入元素
    void insert(const Elem &obj, Position p);

    // 删除元素
    void remove(Position p);

    // 链表就地倒置
    void reverse();

    // 链表表循环移动k位，向左为正
    void cylic_move(int k);

    // 对排序好的两个链表进行合并
    void merge(const AbstractLinkList<Elem, Position> &list, bool (*cmp)(const Elem &, const Elem &));
};

template <typename Elem, typename Position>
AbstractLinkList<Elem, Position>::~AbstractLinkList() {}

#include "AbstractLinkList.cpp"

#endif