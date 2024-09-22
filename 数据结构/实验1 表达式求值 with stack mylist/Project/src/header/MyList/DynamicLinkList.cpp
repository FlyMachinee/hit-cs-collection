#include "DynamicLinkList.hpp"

//构造函数
template <typename Elem>
DynamicLinkList<Elem>::DynamicLinkList()
{
    head_ptr = newNode();
    head_ptr->next = null();
}

//析构函数
template <typename Elem>
DynamicLinkList<Elem>::~DynamicLinkList()
{
    while (head_ptr != null())
    {
        DynamicNode<Elem>* p = head_ptr;
        head_ptr = head_ptr->next;
        deleteNode(p);
    }
}

//返回p指针指向节点的数据的引用
template <typename Elem>
Elem& DynamicLinkList<Elem>::data(DynamicNode<Elem>* p) const
{
    return p->data;
}

//返回指定位置的指针域的引用（即后继）
template <typename Elem>
DynamicNode<Elem>*& DynamicLinkList<Elem>::_next(DynamicNode<Elem>* p) const
{
    return p->next;
}

//返回表头
template <typename Elem>
DynamicNode<Elem>* DynamicLinkList<Elem>::begin() const
{
    return head_ptr;
}

//返回空指针
template <typename Elem>
DynamicNode<Elem>* DynamicLinkList<Elem>::null() const
{
    return nullptr;
}

//申请节点空间，返回节点的地址
template <typename Elem>
DynamicNode<Elem>* DynamicLinkList<Elem>::newNode()
{
    DynamicNode<Elem>* p = new DynamicNode<Elem>;
    return p;
}

//释放节点空间
template <typename Elem>
void DynamicLinkList<Elem>::deleteNode(DynamicNode<Elem>* p)
{   
    if (p != null())
        delete p;
}