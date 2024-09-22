#ifndef ABSTRACT_LINEAR_LIST_HPP_INCLUDED
#define ABSTRACT_LINEAR_LIST_HPP_INCLUDED

#include <iostream>

// 抽象线性表类
template <typename Elem, typename Position>
class AbstractLinearList
{
public:
    // 纯虚析构函数
    virtual ~AbstractLinearList() = 0;

    //------------------------------------------------
    // 以下方法必须由子类重写
    // 子类：顺序表类，抽象链表类
    //------------------------------------------------

    // 返回p位置对应元素的引用
    virtual Elem &at(Position p) const = 0;

    // 在线性表中插入元素
    virtual void insert(const Elem &obj, Position p) = 0;

    // 在线性表中删除元素
    virtual void remove(Position p) = 0;

    // 返回指定位置的前驱
    virtual Position prior(Position p) const = 0;

    // 返回指定位置的指针域的值（即后继）
    // ！！！在顺序表中禁止使用后继作为左值！！！
    virtual Position next(Position p) const = 0;

    // 返回表头
    virtual Position begin() const = 0;

    // 返回表尾
    virtual Position end() const = 0;

    // 判断是否为空表
    virtual bool empty() const = 0;

    // 清空列表
    virtual void clear() = 0;

    // 返回空Position
    virtual Position null() const = 0;

    // 返回当前线性表长度
    virtual int length() const = 0;

    //-----------------------------------------------
    // 以下为一些由上述方法实现的方法
    // 实现于 "AbstractLinearList.cpp" 文件中
    // 内部调用的具体方法由子类实现
    //-----------------------------------------------

    Elem &operator[](Position p) const
    {
        return at(p);
    }

    // 向线性表尾部添加元素
    void push_back(const Elem &obj);

    // 将指定数量的元素添加至线性表尾部
    void push_back(const Elem &obj, int n);

    // 将数组中指定数量的元素添加至线性表尾部
    void push_back(const Elem *arr, int n);

    // 向线性表头部添加元素
    void push_front(const Elem &obj);

    // 查找元素出现第一位置
    Position locate(const Elem &obj) const;

    // 遍历输出线性表全部成员
    void traverse(char separator) const;

    // 删除线性表中所有给定元素
    void remove_elem(const Elem &obj);

    // 对排序好的线性表，删除所有重复元素
    void remove_duplicate();

    // 对线性表中所有元素，按顺序传入func执行操作
    void for_each(void (*func)(Elem &));
};

template <typename Elem, typename Position>
AbstractLinearList<Elem, Position>::~AbstractLinearList() {}

#include "AbstractLinearList.cpp"

#endif