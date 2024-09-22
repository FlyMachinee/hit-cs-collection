#include "DynamicBinaryTree.hpp"

/**
 * @brief 构造函数 
 * 构造 以data为数据的节点 为根节点的树
 * @param data 根节点的数据
*/
template <typename Elem>
BinaryTree::DynamicBinaryTree<Elem>::DynamicBinaryTree(Elem data)
{
    _root = new DynamicNode<Elem>;
    _root->data = data;
    _root->lchild = nullptr;
    _root->rchild = nullptr;
}

/**
 * @brief 构造函数 
 * 构造 以data为数据的节点 为根节点，以lchild为根节点的左孩子，以rchild为根节点的有孩子 的树
 * @param data 根节点的数据
 * @param lchild 根节点的左孩子
 * @param rchild 根节点的右孩子
*/
template <typename Elem>
BinaryTree::DynamicBinaryTree<Elem>::DynamicBinaryTree(Elem data, DynamicNode<Elem> *lchild, DynamicNode<Elem> *rchild)
{
    _root = new DynamicNode<Elem>;
    _root->data = data;
    _root->lchild = lchild;
    _root->rchild = rchild;
}

/**
 * @brief 析构函数
*/
template <typename Elem>
BinaryTree::DynamicBinaryTree<Elem>::~DynamicBinaryTree()
{
    this->delete_tree(_root);
}
