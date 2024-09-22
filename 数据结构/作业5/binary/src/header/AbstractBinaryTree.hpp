#ifndef _ABSTRACT_BINARY_TREE_HPP_INCLUDED_
#define _ABSTRACT_BINARY_TREE_HPP_INCLUDED_

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

namespace BinaryTree
{
    // 二叉树的遍历方式
    enum TraverseType{
        PRE_ORDER = 0,  // 先序 DLR
        IN_ORDER,       // 中序 LDR
        POST_ORDER,     // 后序 LRD
        LEVER_ORDER     // 层序 LEVER
    };
    
    /**
     * @brief 抽象二叉树类
     * 二叉链表实现
    */
    template <typename Elem, typename Position>
    class AbstractBinaryTree
    {
    public:
        virtual ~AbstractBinaryTree() = 0;

        // ---------------------------
        // 需要子类重写的方法
        // ---------------------------
        
        /**
         * @brief 获取指向根节点的指针
         * @return 指向根节点的指针的引用
        */
        virtual Position& root() = 0;

        /**
         * @brief 获取指针指向节点的左孩子指针域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的左孩子指针域的引用
        */
        virtual Position& lchild(Position p) = 0;

        /**
         * @brief 获取指针指向节点的右孩子指针域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的右孩子指针域的引用
        */
        virtual Position& rchild(Position p) = 0;

        /**
         * @brief 获取指针指向节点的数据域的引用
         * @param p 指向节点的指针
         * @return p 指向节点的数据域的引用
        */
        virtual Elem& data(Position p) = 0;

        /**
         * @brief 判断该二叉树是否为空树
         * @return true，如果该二叉树为空树
        */
        virtual bool empty() const = 0;

        /**
         * @brief 返回空指针
         * @return 空指针
        */
        virtual Position null() const = 0;

        /**
         * @brief 申请新节点
         * @return 指向 申请的节点 的指针
        */
        virtual Position new_node() = 0;

        /**
         * @brief 删除节点
         * @param p 指向 要删除的节点 的指针
        */
        virtual void delete_node(Position p) = 0;

        // ---------------------------
        // 由上述方法得以实现的方法
        // ---------------------------

        /**
         * @brief 删除以p为根节点的二叉树
         * @param p 二叉树的根节点地址
        */
        void delete_tree(Position& p);
    
        /**
         * @brief 判断二叉树是否为完全二叉树
         * @param p 二叉树的根节点地址
         * @return true，如果以p为根节点的二叉树为完全二叉树
        */
        bool complete(Position p);

        /**
         * @brief 判断该二叉树是否为完全二叉树
         * @return true，如果该二叉树为完全二叉树
        */
        inline bool complete()
        {
            return complete(root());
        }

        /**
         * @brief 计算二叉树的宽度，非递归
         * @param p 二叉树的根节点
         * @return 以p为根节点的二叉树的宽度
        */
        int width(Position p);

        /**
         * @brief 计算该二叉树的宽度，非递归
         * @return 该二叉树的宽度
        */
        inline int width()
        {
            return width(root());
        }

        /**
         * @brief 计算以p为根节点的二叉树的深度，递归求解
         * @param p 二叉树的根节点
         * @return 以p为根节点的二叉树的深度
        */
        int depth(Position p);

        /**
         * @brief 计算该二叉树的深度，递归求解
         * @return 该二叉树的深度
        */
        inline int depth()
        {
            return depth(root());
        }      

        /**
         * @brief 打印二叉树
         * @param out 接收结果的输出流
        */
        void show(std::ostream& out);

        /**
         * @brief 根据先序遍历序列建立二叉树
         * @param in 输入流的来源
         * @param separator 每项之间的分割符（可为\0）
         * @param placeholder 空节点的占位字符（不可为\0）
        */
        void create(std::istream& in, char separator, char placeholder);


        /**
         * @brief 保存二叉树
         * 将该二叉树根据 type（默认为PRE_ORDER）的遍历方式输出至输出流
         * @param separator 每项之间的分割符（可为\0）
         * @param placeholder 空节点的表示字符（不可为\0）
        */
        inline void save(std::ostream& out, char separator, char placeholder, TraverseType type = PRE_ORDER)
        {
            for_each(
                type,
                [&](Elem e){out << e << separator;},
                [&](){out << placeholder << separator;},
                root()
            );
            out << std::endl;
        }


        /**
         * @brief 遍历二叉树
         * 按照 type 的遍历方式，对二叉树所有非空节点的数据域施用 func_not_null
         * 当访问空节点时，调用 func_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
         * @param func_null 访问空节点时调用的函数对象
         * @param p 二叉树的根节点 
        */
        template <typename Func_1, typename Func_2>
        void for_each(TraverseType type, Func_1 func_not_null, Func_2 func_null, Position p);


        /**
         * @brief 遍历二叉树
         * 效果同 for_each，但为非递归实现版本
         * 按照 type 的遍历方式，对二叉树所有非空节点的数据域施用 func_not_null
         * 当访问空节点时，调用 func_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
         * @param func_null 访问空节点时调用的函数对象
         * @param p 二叉树的根节点
        */
        template <typename Func_1, typename Func_2>
        void for_each_no_rec(TraverseType type, Func_1 func_not_null, Func_2 func_null, Position p);


        /**
         * @brief 遍历二叉树
         * 按照 type 的遍历方式，对该二叉树所有非空节点的数据域施用 func_not_null
         * 当访问空节点时，调用 func_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
         * @param func_null 访问空节点时调用的函数对象
        */
        template <typename Func_1, typename Func_2>
        inline void for_each(TraverseType type, Func_1 func_not_null, Func_2 func_null)
        {
            for_each(type, func_not_null, func_null, root());
        }


        /**
         * @brief 遍历二叉树
         * 按照 type 的遍历方式，对二叉树所有非空节点的数据域施用 func_not_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
         * @param p 二叉树的根节点
        */
        template <typename Func>
        inline void for_each(TraverseType type, Func func_not_null, Position p)
        {
            for_each(type, func_not_null, [](){;}, p);
        }


        /**
         * @brief 遍历二叉树
         * 按照 type 的遍历方式，对该二叉树所有非空节点的数据域施用 func_not_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
        */
        template <typename Func>
        inline void for_each(TraverseType type, Func func_not_null)
        {
            for_each(type, func_not_null, [](){;}, root());
        }


        /**
         * @brief 遍历二叉树
         * 效果同 for_each，但为非递归实现版本
         * 按照 type 的遍历方式，对该二叉树所有非空节点的数据域施用 func_not_null
         * 当访问空节点时，调用 func_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
         * @param func_null 访问空节点时调用的函数对象
        */
        template <typename Func_1, typename Func_2>
        inline void for_each_no_rec(TraverseType type, Func_1 func_not_null, Func_2 func_null)
        {
            for_each_no_rec(type, func_not_null, func_null, root());
        }


        /**
         * @brief 遍历二叉树
         * 效果同 for_each，但为非递归实现版本
         * 按照 type 的遍历方式，对二叉树所有非空节点的数据域施用 func_not_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
         * @param p 二叉树的根节点，默认为该树的根节点
        */
        template <typename Func_1>
        inline void for_each_no_rec(TraverseType type, Func_1 func_not_null, Position p)
        {
            for_each_no_rec(type, func_not_null, [](){;}, p);
        }


        /**
         * @brief 遍历二叉树
         * 效果同 for_each，但为非递归实现版本
         * 按照 type 的遍历方式，对该二叉树所有非空节点的数据域施用 func_not_null
         * @param type 遍历方式
         * @param func_not_null 对非空节点的数据域施用的函数对象
        */
        template <typename Func_1>
        inline void for_each_no_rec(TraverseType type, Func_1 func_not_null)
        {
            for_each_no_rec(type, func_not_null, [](){;}, root());
        }

    private:

        template <typename Func_1, typename Func_2>
        void _pre_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null);

        template <typename Func_1, typename Func_2>
        void _in_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null);

        template <typename Func_1, typename Func_2>
        void _post_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null);

        template <typename Func_1, typename Func_2>
        void _lever_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null);

        template <typename Func_1, typename Func_2>
        void _pre_order_for_each_no_rec(Position p, Func_1 func_not_null, Func_2 func_null);

        template <typename Func_1, typename Func_2>
        void _in_order_for_each_no_rec(Position p, Func_1 func_not_null, Func_2 func_null);

        template <typename Func_1, typename Func_2>
        void _post_order_for_each_no_rec(Position p, Func_1 func_not_null, Func_2 func_null);

        void _create(std::istream& in, Position& p, char separator, char placeholder);

        /**
         * @brief 打印二叉树至暂存的vector
         * @param buf 用于暂存结果的vector
         * @param p 二叉树的根节点
         * @param depth 节点p所处的深度
         * @return p节点对应行在buf中的下标
        */
        int _show(std::vector<std::pair<std::string, std::string>>& buf, Position p, int depth);
    };

    // 纯虚析构函数
    template <typename Elem, typename Position>
    AbstractBinaryTree<Elem, Position>::~AbstractBinaryTree(){}
}

#include "AbstractBinaryTree.cpp"
#include "ForEach.cpp"   

#endif