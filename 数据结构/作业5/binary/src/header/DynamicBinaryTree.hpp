#ifndef _DYNAMIC_BINARY_TREE_HPP_INCLUDED_
#define _DYNAMIC_BINARY_TREE_HPP_INCLUDED_

#include "AbstractBinaryTree.hpp"

namespace BinaryTree
{
    // 动态二叉树节点
    template <typename Elem>
    class DynamicNode
    {
    public:
        // 数据域
        Elem data;
        // 指向左孩子的指针域
        DynamicNode* lchild;
        // 指向右孩子的指针域
        DynamicNode* rchild;

        DynamicNode() : lchild(nullptr), rchild(nullptr) {};

        DynamicNode(Elem _data, DynamicNode* _lchild, DynamicNode* _rchild) : data(_data), lchild(_lchild), rchild(_rchild) {};
    };

    /**
     * @brief 动态二叉树类
     * 二叉动态链表实现
    */
    template <typename Elem>
    class DynamicBinaryTree: public AbstractBinaryTree<Elem, DynamicNode<Elem>*>
    {
    private:
        // 指向根节点的指针
        DynamicNode<Elem>* _root = nullptr;

    public:

        /**
         * @brief 默认构造函数
         * 构造空树
        */
        DynamicBinaryTree(): _root(nullptr){};

        /**
         * @brief 构造函数 
         * 构造以root为根节点的树
         * @param root 根节点
        */
        DynamicBinaryTree(DynamicNode<Elem>* root): _root(root){};

        /**
         * @brief 构造函数 
         * 构造 以data为数据的节点 为根节点的树
         * @param data 根节点的数据
        */
        DynamicBinaryTree(Elem data);

        /**
         * @brief 构造函数 
         * 构造 以data为数据的节点 为根节点，以lchild为根节点的左孩子，以rchild为根节点的有孩子 的树
         * @param data 根节点的数据
         * @param lchild 根节点的左孩子
         * @param rchild 根节点的右孩子
        */
        DynamicBinaryTree(Elem data, DynamicNode<Elem>* lchild, DynamicNode<Elem>* rchild);

        /**
         * @brief 析构函数
        */
        ~DynamicBinaryTree();

        //-----------------------------------
        // 对父类的重写
        //-----------------------------------

        /**
         * @brief 获取指向根节点的指针
         * @return 指向根节点的指针的引用
        */
        inline DynamicNode<Elem>*& root()
        {
            return _root;
        }

        /**
         * @brief 获取指针指向节点的左孩子指针域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的左孩子指针域的引用
        */
        inline DynamicNode<Elem>*& lchild(DynamicNode<Elem>* p)
        {
            return p->lchild;
        }

        /**
         * @brief 获取指针指向节点的右孩子指针域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的右孩子指针域的引用
        */
        inline DynamicNode<Elem>*& rchild(DynamicNode<Elem>* p)
        {
            return p->rchild;
        }

        /**
         * @brief 获取指针指向节点的数据域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的数据域的引用
        */
        inline Elem& data(DynamicNode<Elem>* p)
        {
            return p->data;
        }

        /**
         * @brief 判断该二叉树是否为空树
         * @return true，如果该二叉树为空树
        */
        inline bool empty() const
        {
            return _root == nullptr;
        }

        /**
         * @brief 返回空指针
         * @return nullptr
        */
        inline DynamicNode<Elem>* null() const
        {
            return nullptr;
        }

        /**
         * @brief 申请新节点
         * @return 指向 申请的节点 的指针
        */
        inline DynamicNode<Elem>* new_node()
        {
            return new DynamicNode<Elem>;
        }

        /**
         * @brief 删除节点
         * @param p 指向 要删除的节点 的指针
        */
        inline void delete_node(DynamicNode<Elem>* p)
        {
            if (p)
                delete p;
        }
    };
}

#include "DynamicBinaryTree.cpp"

#endif