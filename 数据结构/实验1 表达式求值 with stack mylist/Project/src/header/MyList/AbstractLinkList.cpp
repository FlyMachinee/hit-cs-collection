#include "AbstractLinkList.hpp"

//返回指定位置的指针域的值（即后继）
//_next返回左值，next返回右值（与父类兼容）
template <typename Elem, typename Position>
Position AbstractLinkList<Elem, Position>::next(Position p) const
{
    return _next(p);
}

//返回p指针所指向下一个节点的数据的引用
template <typename Elem, typename Position>
Elem& AbstractLinkList<Elem, Position>::at(Position p) const
{
    return data(_next(p));
}

//返回指定位置的前驱
template <typename Elem, typename Position>
Position AbstractLinkList<Elem, Position>::prior(Position p) const
{
    if (p == begin() || p == null())
        return null();
    else
    {
        //从表头开始，遍历链表
        Position q = begin();
        while (_next(q) != p && q != null())
            q = _next(q);
        return q;
    }
}

//返回表尾
template <typename Elem, typename Position>
Position AbstractLinkList<Elem, Position>::end() const
{
    //从表头开始，遍历链表
    Position p = begin();
    while (_next(p) != null())
        p = _next(p);
    return p;
}

//判断是否为空表
template <typename Elem, typename Position>
bool AbstractLinkList<Elem, Position>::empty() const
{
    return _next(begin()) == null();
}

//清空列表
template <typename Elem, typename Position>
void AbstractLinkList<Elem, Position>::clear()
{
    while (_next(begin()) != null())
        remove(begin());
}

//返回当前链表长度
template <typename Elem, typename Position>
int AbstractLinkList<Elem, Position>::length() const
{
    int len = 0;
    Position p = begin();
    while (_next(p) != null())
    {
        len++;
        p = _next(p);
    }
    return len;
}

//在链表中插入元素
template <typename Elem, typename Position>
void AbstractLinkList<Elem, Position>::insert(const Elem& obj, Position p)
{
    //创建新节点
    Position new_node = newNode();

    //给新节点添入数据
    data(new_node) = obj;

    //将新节点的指针域 指向 p的指针域 所指向的节点
    _next(new_node) = _next(p);
    
    //将p的指针域指向新节点
    _next(p) = new_node;
}

//删除元素
template <typename Elem, typename Position>
void AbstractLinkList<Elem, Position>::remove(Position p)
{
    if (p != null() && p != end())
    {
        Position temp = _next(p);

        //将 被删除的节点的前一个节点的指针域 指向 被删除的节点的后一个节点
        _next(p) = _next(temp);

        deleteNode(temp);
    }
}

//链表就地倒置
template <typename Elem, typename Position>
void AbstractLinkList<Elem, Position>::reverse()
{
    //p指向第一个节点
    Position p = _next(begin());

    //当p不为空（表存在）
    if (p != null())
    {
        //p_prior为 p指向的前一个元素 的指针
        Position p_prior = p;
        p = _next(p);

        //第一个节点指向空
        _next(p_prior) = null();

        while (p != null())
        {
            //p_next为 p指向的后一个元素 的指针
            Position p_next = _next(p);

            //让p指向的元素 指向前一个元素
            _next(p) = p_prior;

            //p_prior 与 p 的指向 均 向后移动一个节点
            p_prior = p;
            p = p_next; 
        }

        //当p为空时，p_prior正好指向表尾
        //让表头指向表尾
        _next(begin()) = p_prior;
    }
}

//链表表循环移动k位，向左为正
template <typename Elem, typename Position>
void AbstractLinkList<Elem, Position>::cylic_move(int k)
{
    int len = length();
    if (k % len != 0)
    {
        _next(end()) = _next(begin());
        // 尾节点指向第一个节点

        k = ((k % len) + len) % len;
        // 求 k 对 len 在数学上的余数
        // e.g. 5 % 2 = 1, 7 % 4 = 3, -7 % 4 = 1

        Position new_head = begin();
        for (int i = 0; i < k; i++)
        {
            new_head = _next(new_head);
        }
        // 此时new_head指向 新的第一个节点 的 前一个节点

        _next(begin()) = _next(new_head);
        // 头节点指向新的第一个节点

        _next(new_head) = null();
        // 新的第一个节点的前一个节点（即新的尾节点）指向空
    }
}

//对排序好的两个链表进行合并
template <typename Elem, typename Position>
void AbstractLinkList<Elem, Position>::merge(const AbstractLinkList<Elem, Position>& list, bool (*cmp)(const Elem&, const Elem&))
{
    Position p = _next(begin());
    Position q = _next(list.begin());

    //从本对象的表头开始，依次将两个链表按cmp顺序连在一起
    Position temp = begin();

    while (p != null() && q != null())
    {
        //谁更cmp，temp就与谁连接
        //被连接的一方应后移一个节点
        if (cmp(data(p), data(q)))
        {
            _next(temp) = p;
            p = _next(p);
        }
        else
        {
            _next(temp) = q;
            q = _next(q);
        }

        //temp向后移动，始终指向新链表的表尾
        temp = _next(temp);
    }

    //当一方链表为空时，temp连接另一方剩下的链表
    if (p == null())
        _next(temp) = q;
    else
        _next(temp) = p;

    //在链表的合并操作后，第二个表已失去意义，应置空
    _next(list.begin()) = null();
}