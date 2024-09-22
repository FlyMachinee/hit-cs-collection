#include "StaticBinaryTree.hpp"

//对类中静态对象的初始化

// 空闲空间池，由所有同类型静态二叉树类共享
template <typename Elem>
BinaryTree::StaticNode<Elem>* BinaryTree::StaticBinaryTree<Elem>::space = nullptr;

// 判断空间池是否存在，默认值为0
template <typename Elem>
bool BinaryTree::StaticBinaryTree<Elem>::space_exist = false;

// 空间池指针，用于管理空间
template <typename Elem>
int BinaryTree::StaticBinaryTree<Elem>::space_ptr = -1;

// 空间池的大小
template <typename Elem>
int BinaryTree::StaticBinaryTree<Elem>::space_size = 0;

/**
 * @brief 构造函数 
 * 构造 以data为数据的节点 为根节点的树
 * @param data 根节点的数据
*/
template <typename Elem>
BinaryTree::StaticBinaryTree<Elem>::StaticBinaryTree(Elem data)
{
    init_space(512);
    _root = new_node();
    if (_root != null())
    {
        this->data(_root) = data;
        this->lchild(_root) = null();
        this->rchild(_root) = null();
    }
}

/**
 * @brief 构造函数 
 * 构造 以data为数据的节点 为根节点，以lchild为根节点的左孩子，以rchild为根节点的有孩子 的树
 * @param data 根节点的数据
 * @param lchild 根节点的左孩子
 * @param rchild 根节点的右孩子
*/
template <typename Elem>
BinaryTree::StaticBinaryTree<Elem>::StaticBinaryTree(Elem data, int lchild, int rchild)
{
    init_space(512);
    _root = new_node();
    if (_root != null())
    {
        this->data(_root) = data;
        this->lchild(_root) = lchild;
        this->rchild(_root) = rchild;
    }
}

/**
 * @brief 析构函数
*/
template <typename Elem>
BinaryTree::StaticBinaryTree<Elem>::~StaticBinaryTree()
{
    this->delete_tree(_root);
}

/**
 * @brief 申请新节点
 * @return 申请节点的地址
*/
template <typename Elem>
int BinaryTree::StaticBinaryTree<Elem>::new_node()
{
    if (!space_exist)
        init_space(512);

    // static_assert(!space_exist);

    if (!space_exist || (space[space_ptr].lchild == null()))
        return null();
    else
    {
        //p指向 空闲空间池链表 的 第一个节点
        int p = space[space_ptr].lchild;

        //空间池链表头节点 指向 空间池链表 的 第二个节点
        space[space_ptr].lchild = space[p].lchild;

        //返回 空间池链表 的 第一个节点 的 地址
        return p;
    }
}

/**
 * @brief 删除节点
 * @param p 要删除节点的地址
*/
template <typename Elem>
void BinaryTree::StaticBinaryTree<Elem>::delete_node(int p)
{
    if (space_exist)
    {
        //将被释放的节点 插入 空间池链表 的 表头
        space[p].lchild = space[space_ptr].lchild;
        space[space_ptr].lchild = p;
    }
}

/**
 * @brief 初始化空间池
 * @param max_size 空间池的大小
*/
template <typename Elem>
void BinaryTree::StaticBinaryTree<Elem>::init_space(int max_size)
{
    if (!space_exist)
    {
        space_size = max_size;
        
        //申请空间池空间
        space = new StaticNode<Elem>[max_size];

        //建立空间池链表
        for (int i = 0; i < max_size - 1; i++)
        {
            space[i].lchild = i + 1;
        }

        //空间池链表表尾置空
        space[max_size - 1].lchild = -1;

        //初始化空间池链表表头
        space_ptr = 0;

        space_exist = true;
    }
}

/**
 * @brief 清空空间池
*/
template <typename Elem>
void BinaryTree::StaticBinaryTree<Elem>::clear_space()
{
    if (space_exist)
    {
        delete[] space;
        space = nullptr;
        space_exist = false;
    }
}

/**
 * @brief 展示静态链表空间池
*/
template <typename Elem>
void BinaryTree::StaticBinaryTree<Elem>::show_space(int len)
{
    if (space_exist)
    {
        std::cout << "Space of <" << typeid(Elem).name() << ">" << std::endl;
        std::cout << "Size: " << space_size << std::endl;
        std::cout << "Index || Data\t|| LChild || RChild" << std::endl;
        for (int i = 0; i < len; ++i)
        {
            std::cout << std::setw(5) << std::right << i 
                      << " || " 
                      << std::setw(4) << std::left << space[i].data 
                      << "\t|| " 
                      << std::setw(6) << std::left << space[i].lchild 
                      << " || "
                      << std::setw(6) << std::left << space[i].rchild
                      << std::endl;
        }
    }
    else
        std::cout << "Space is not exist" << std::endl;
    
}