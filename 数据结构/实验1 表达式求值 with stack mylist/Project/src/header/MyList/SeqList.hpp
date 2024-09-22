#ifndef SEQLIST_HPP_INCLUDED
#define SEQLIST_HPP_INCLUDED

#include "AbstractLinearList.hpp"

// 顺序表类
template <typename Elem>
class SeqList : public AbstractLinearList<Elem, int>
{
private:
    // 已经使用的长度
    int used_len;
    // 申请内存的长度
    int malloc_len;
    // 申请顺序表数组地址的指针
    Elem *head_ptr;

public:
    SeqList(int len = 64);
    ~SeqList();

    //-----------------------------------
    // 对父类的重写
    //-----------------------------------

    // 返回p位置对应元素的引用
    Elem &at(int p) const;

    // 在顺序表中插入元素
    void insert(const Elem &obj, int p);

    // 在顺序表中删除元素
    void remove(int p);

    // 返回指定位置的前驱
    int prior(int p) const;

    // 返回指定位置的后继
    // ！！！在顺序表中禁止使用后继作为左值！！！
    int next(int p) const;

    // 返回表头
    int begin() const;

    // 返回表尾
    int end() const;

    // 判断是否为空表
    bool empty() const;

    // 清空列表
    void clear();

    // 返回空下标
    int null() const;

    // 返回当前数组长度
    int length() const;

    //------------------------------------
    // 自身独有的方法
    //------------------------------------

    // 将数组增长len与现有长度一半的最大值的长度
    void extend(int len = 16);

    // 尝试向数组增加len个元素，如果超出现有长度，调用extend
    void try_extend(int len);

    // 顺序表就地倒置
    void reverse();

    // 顺序表循环移动k位，向左为正
    void cylic_move(int k);

    // 对排序好的两个顺序表进行合并
    void merge(const SeqList<Elem> &list, bool (*cmp)(const Elem &, const Elem &));
};

#include "SeqList.cpp"

#endif