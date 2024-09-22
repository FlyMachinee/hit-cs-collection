#include "Queue.hpp"

// 构造函数
template <typename Elem>
Queue<Elem>::Queue()
{
    list = new DynamicLinkList<Elem>;
    end = list->begin();
}

// 析构函数
template <typename Elem>
Queue<Elem>::~Queue()
{
    if (list)
        delete list;
}

// 尾插法在队尾插入元素
template <typename Elem>
void Queue<Elem>::push(const Elem& obj)
{
    list->push_back(obj);
    end = list->_next(end);
}

// 从队头弹出元素
template <typename Elem>
void Queue<Elem>::pop()
{
    if (list->empty())
    {

    }
    else
    {
        list->remove(list->begin());
        if (list->empty())
            end = list->begin();
    }
}

// 读取队头元素
template <typename Elem>
const Elem& Queue<Elem>::front() const
{
    return list->at(list->begin());
}

// 查看队列元素个数
template <typename Elem>
int Queue<Elem>::size() const
{
    return list->length();
}

// 判断队列是否为空
template <typename Elem>
bool Queue<Elem>::empty() const
{
    return list->empty();
}

// 遍历元素输出，以separator为分隔符
template <typename Elem>
void Queue<Elem>::traverse(char separator) const
{
    list->traverse(separator);
}