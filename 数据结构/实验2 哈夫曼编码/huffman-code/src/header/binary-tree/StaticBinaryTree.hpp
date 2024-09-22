#ifndef _STATIC_BINARY_TREE_HPP_INCLUDED_
#define _STATIC_BINARY_TREE_HPP_INCLUDED_

#include "AbstractBinaryTree.hpp"
#include <iomanip>

namespace BinaryTree
{
    // 静态二叉树节点
    template <typename Elem>
    class StaticNode
    {
    public:
        // 数据域
        Elem data;
        // 指向左孩子的指针域
        int lchild;
        // 指向右孩子的指针域
        int rchild;
    };
    
    /**
     * @brief 静态二叉树类
     * 二叉静态链表实现
    */
    template <typename Elem>
    class StaticBinaryTree : public AbstractBinaryTree<Elem, int>
    {
    private:
        // 指向根节点的指针
        int _root = -1;

        // 空闲空间池，由所有同类型静态二叉树类共享
        static StaticNode<Elem> *space;
        // 判断空间池是否存在，默认值为0
        static bool space_exist;
        // 空间池指针，用于管理空间
        static int space_ptr;
        // 空间池的大小
        static int space_size;

    public:

        /**
         * @brief 默认构造函数
         * 构造空树
        */
        StaticBinaryTree(): _root(-1){};

        /**
         * @brief 构造函数 
         * 构造以root为根节点的树
         * @param root 根节点
        */
        StaticBinaryTree(int root): _root(root){};

        /**
         * @brief 构造函数 
         * 构造 以data为数据的节点 为根节点的树
         * @param data 根节点的数据
        */
        StaticBinaryTree(Elem data);

        /**
         * @brief 构造函数 
         * 构造 以data为数据的节点 为根节点，以lchild为根节点的左孩子，以rchild为根节点的有孩子 的树
         * @param data 根节点的数据
         * @param lchild 根节点的左孩子
         * @param rchild 根节点的右孩子
        */
        StaticBinaryTree(Elem data, int lchild, int rchild);

        /**
         * @brief 析构函数
        */
        ~StaticBinaryTree();

        //-----------------------------------
        // 对父类的重写
        //-----------------------------------

        /**
         * @brief 获取指向根节点的指针
         * @return 指向根节点的指针的引用
        */
        inline int& root()
        {
            return _root;
        }

        /**
         * @brief 获取指针指向节点的左孩子指针域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的左孩子指针域的引用
        */
        inline int &lchild(int p)
        {
            return space[p].lchild;
        }

        /**
         * @brief 获取指针指向节点的右孩子指针域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的右孩子指针域的引用
        */
        inline int &rchild(int p)
        {
            return space[p].rchild;
        }

        /**
         * @brief 获取指针指向节点的数据域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的数据域的引用
        */
        inline Elem &data(int p)
        {
            return space[p].data;
        }

        /**
         * @brief 判断该二叉树是否为空树
         * @return true，如果该二叉树为空树
        */
        inline bool empty() const
        {
            return _root == -1;
        }

        /**
         * @brief 返回空指针
         * @return nullptr
        */
        inline int null() const
        {
            return -1;
        }

        /**
         * @brief 申请新节点
         * @return 申请节点的地址
        */
        int new_node();

        /**
         * @brief 删除节点
         * @param p 要删除节点的地址
        */
        void delete_node(int p);

        //-----------------------------------
        // 子类独有的方法
        //-----------------------------------

        /**
         * @brief 初始化空间池
         * @param max_size 空间池的大小
        */
        static void init_space(int max_size);

        /**
         * @brief 清空空间池
        */
        static void clear_space();

        /**
         * @brief 展示静态链表空间池
        */
        static void show_space(int len = space_size);
    };
}

#include "StaticBinaryTree.cpp"

#endif