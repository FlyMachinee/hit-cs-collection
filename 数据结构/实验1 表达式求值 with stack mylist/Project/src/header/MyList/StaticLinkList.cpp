#include "StaticLinkList.hpp"
#include <iomanip>

//对类中静态对象的初始化
template <typename Elem>
StaticNode<Elem>* StaticLinkList<Elem>::space = NULL;
template <typename Elem>
bool StaticLinkList<Elem>::space_exist = false;
template <typename Elem>
int StaticLinkList<Elem>::space_ptr = -1;
template <typename Elem>
int StaticLinkList<Elem>::space_size = 0;

//构造函数
template <typename Elem>
StaticLinkList<Elem>::StaticLinkList()
{
    initSpace(512);
    head_ptr = newNode();
    if (head_ptr != null())
        _next(head_ptr) = null();
}

//析构函数
template <typename Elem>
StaticLinkList<Elem>::~StaticLinkList()
{
    if (space_exist)
    {
        while (head_ptr != null())
        {
            int p = head_ptr;
            head_ptr = _next(head_ptr);
            deleteNode(p);
        }
    }
}

//返回p指针指向节点的数据的引用
template <typename Elem>
Elem& StaticLinkList<Elem>::data(int p) const
{
    return space[p].data;
}

//返回指定位置的指针域的引用（即后继）
template <typename Elem>
int& StaticLinkList<Elem>::_next(int p) const
{
    return space[p].next;
}

//返回表头
template <typename Elem>
int StaticLinkList<Elem>::begin() const
{
    if (space_exist)
        return head_ptr;
    else
        return null();
}

//返回空指针
template <typename Elem>
int StaticLinkList<Elem>::null() const
{
    return -1;
}

//申请节点空间，返回节点的地址
template <typename Elem>
int StaticLinkList<Elem>::newNode()
{
    if (!space_exist || (_next(space_ptr) == null()))
        return null();
    else
    {
        //p指向 空闲空间池链表 的 第一个节点
        int p = _next(space_ptr);

        //空间池链表头节点 指向 空间池链表 的 第二个节点
        _next(space_ptr) = _next(p);

        //返回 空间池链表 的 第一个节点 的 地址
        return p;
    }
}

//释放节点空间
template <typename Elem>
void StaticLinkList<Elem>::deleteNode(int p)
{   
    if (space_exist)
    {
        //将被释放的节点 插入 空间池链表 的 表头
        _next(p) = _next(space_ptr);
        _next(space_ptr) = p;
    }
}

//对空间池进行初始化
template <typename Elem>
void StaticLinkList<Elem>::initSpace(int max_size)
{
    if (!space_exist)
    {
        space_size = max_size;
        
        //申请空间池空间
        space = new StaticNode<Elem>[max_size];

        //建立空间池链表
        for (int i = 0; i < max_size - 1; i++)
        {
            space[i].next = i + 1;
        }

        //空间池链表表尾置空
        space[max_size - 1].next = -1;

        //初始化空间池链表表头
        space_ptr = 0;

        space_exist = true;
    }
}

//清空空间池
template <typename Elem>
void StaticLinkList<Elem>::clearSpace()
{
    if (space_exist)
    {
        delete[] space;
        space = nullptr;
        space_exist = false;
    }
}

//展示静态链表空间池
template <typename Elem>
void StaticLinkList<Elem>::showSpace(int len)
{
    if (space_exist)
    {
        std::cout << "Space of <" << typeid(Elem).name() << ">" << std::endl;
        std::cout << "Size: " << space_size << std::endl;
        std::cout << "Index || Content\t|| Pointer" << std::endl;
        for (int i = 0; i < len; i++)
        {
            std::cout << std::setw(5) << std::left << i << " || " 
                      << std::setw(8) << std::left << space[i].data 
                      << "\t|| " << space[i].next << std::endl;
        }
    }
    else
        std::cout << "Space is not exist" << std::endl;
}