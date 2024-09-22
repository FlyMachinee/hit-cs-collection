#include "AbstractLinearList.hpp"

//向线性表尾部添加元素
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::push_back(const Elem& obj)
{
    insert(obj, end());
}

//将指定数量的元素添加至线性表尾部
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::push_back(const Elem& obj, int n)
{
    for (int i = 0; i < n; i++)
        push_back(obj);
}

//将数组中指定数量的元素添加至线性表尾部
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::push_back(const Elem* arr, int n)
{
    for (int i = 0; i < n; i++)
        push_back(arr[i]);
}

//向线性表头部添加元素
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::push_front(const Elem& obj)
{
    insert(obj, begin());
}

//查找元素出现第一位置
template <typename Elem, typename Position>
Position AbstractLinearList<Elem, Position>::locate(const Elem& obj) const
{
    Position p = begin();
    while (p != end() && at(p) != obj)
        p = next(p);
    return p;
}

//遍历输出线性表全部成员
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::traverse(char separator) const
{
    //遍历线性表
    for (Position p = begin(); p != end(); p = next(p))
        std::cout << at(p) << separator;
}

//删除线性表中所有给定元素
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::remove_elem(const Elem& obj)
{
    Position p = begin();
    while (p != end())
    {
        if (at(p) == obj)
            remove(p);
        else
            p = next(p);
    }
}

//对排序好的线性表，删除所有重复元素
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::remove_duplicate()
{
    Position p = begin();
    while ((p != end()) && (next(p) != end()))
    {
        //比较当前元素是否与下个元素相等
        if (at(p) == at(next(p)))

            //若相等，删除当前元素
            remove(p);
        else
            p = next(p);
    }
}

//对线性表中所有元素，按顺序传入func执行操作
template <typename Elem, typename Position>
void AbstractLinearList<Elem, Position>::for_each(void (*func)(Elem&))
{
    for (Position p = begin(); p != end(); p = next(p))
        func(at(p));
}