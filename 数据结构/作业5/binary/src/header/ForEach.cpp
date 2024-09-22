#include "AbstractBinaryTree.hpp"

/**
 * @brief 遍历二叉树
 * 按照 type 的遍历方式，对二叉树所有非空节点的数据域施用 func_not_null
 * 当访问空节点时，调用 func_null
 * @param type 遍历方式
 * @param func_not_null 对非空节点的数据域施用的函数对象
 * @param func_null 访问空节点时调用的函数对象
 * @param p 二叉树的根节点 
*/
template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
for_each(TraverseType type, Func_1 func_not_null, Func_2 func_null, Position p)
{
    switch (type)
    {
    case PRE_ORDER:
        _pre_order_for_each(p, func_not_null, func_null);
        break;
    case IN_ORDER:
        _in_order_for_each(p, func_not_null, func_null);
        break;
    case POST_ORDER:
        _post_order_for_each(p, func_not_null, func_null);
        break;
    case LEVER_ORDER:
        _lever_order_for_each(p, func_not_null, func_null);
        break;
    }
}

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
template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
for_each_no_rec(TraverseType type, Func_1 func_not_null, Func_2 func_null, Position p)
{
    switch (type)
    {
    case PRE_ORDER:
        _pre_order_for_each_no_rec(p, func_not_null, func_null);
        break;
    case IN_ORDER:
        _in_order_for_each_no_rec(p, func_not_null, func_null);
        break;
    case POST_ORDER:
        _post_order_for_each_no_rec(p, func_not_null, func_null);
        break;
    case LEVER_ORDER:
        _lever_order_for_each(p, func_not_null, func_null);
        break;
    }
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_pre_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 先序遍历

    if (p != null())
    // 访问至非空节点，对其数据域施用 func_not_null
    {
        func_not_null(data(p));
        _pre_order_for_each(lchild(p), func_not_null, func_null);
        _pre_order_for_each(rchild(p), func_not_null, func_null);
    }
    else
    // 访问至空节点，调用 func_null
        func_null();
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_in_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 中序遍历

    if (p != null())
    // 访问至非空节点，对其数据域施用 func_not_null
    {
        _in_order_for_each(lchild(p), func_not_null, func_null);
        func_not_null(data(p));
        _in_order_for_each(rchild(p), func_not_null, func_null);
    }
    else
    // 访问至空节点，调用 func_null
        func_null();
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_post_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 后序遍历

    if (p != null())
    // 访问至非空节点，对其数据域施用 func_not_null
    {
        _post_order_for_each(lchild(p), func_not_null, func_null);
        _post_order_for_each(rchild(p), func_not_null, func_null);
        func_not_null(data(p));
    }
    else
    // 访问至空节点，调用 func_null
        func_null();
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_lever_order_for_each(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 层序遍历
    std::queue<Position> q;
    q.push(p);
    while (!q.empty())
    {
        Position temp = q.front();
        q.pop();

        if (temp != null())
        // 访问至非空节点，对其数据域施用 func_not_null
        {
            func_not_null(data(temp));
            q.push(lchild(temp));
            q.push(rchild(temp));
        }
        else
        // 访问至空节点，调用 func_null
            func_null();
    }
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_pre_order_for_each_no_rec(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 非递归先序遍历
    std::stack<Position> st;
    st.push(p);
    while (!st.empty())
    {
        Position cursor = st.top();
        st.pop();
        if (cursor != null())
        {
            func_not_null(data(cursor));
            st.push(rchild(cursor));
            st.push(lchild(cursor));
        }
        else
            func_null();
    }
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_in_order_for_each_no_rec(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 非递归中序遍历
    std::stack<Position> st;
    Position cursor = p;
    while (1)
    {
        while (cursor != null())
        {
            st.push(cursor);
            cursor = lchild(cursor);
        }
        func_null();

        if (st.empty())
            break;

        cursor = st.top();
        st.pop();
        func_not_null(data(cursor));
        cursor = rchild(cursor);
    }
}

template <typename Elem, typename Position>
template <typename Func_1, typename Func_2>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_post_order_for_each_no_rec(Position p, Func_1 func_not_null, Func_2 func_null)
{
    // 非递归后序遍历
    std::stack<std::pair<Position, bool>> st;
    Position cursor = p;
    while (cursor != null() || !st.empty())
    {
        while (cursor != null())
        {
            st.emplace(std::make_pair(cursor, false));
            cursor = lchild(cursor);
        }
        func_null();

        while (!st.empty() && st.top().second)
        {
            func_not_null(data(st.top().first));
            st.pop();
        }

        if (!st.empty())
        {
            st.top().second = true;
            cursor = rchild(st.top().first);
        }
    }

    /*

    // OLD VERSION
    // 可行，但过于复杂

    std::stack<Position> st;
    Position cursor = p, recent = null();   
    // recent 记录上一个调用 func_not_null 的节点 的指针
    while (cursor != null() || !st.empty())
    {
        if (cursor != null())
        {
            st.push(cursor);
            cursor = lchild(cursor);
        }
        else
        {
            func_null();
            while (!st.empty())
            {
                cursor = st.top();
                if (rchild(cursor) != null() && rchild(cursor) != recent)
                {
                    cursor = rchild(cursor);
                    break;
                }
                else
                {
                    if (rchild(cursor) == null())
                        func_null();
                    st.pop();
                    func_not_null(data(cursor));
                    recent = cursor;
                    cursor = null();
                }
            }
        }
    }    
    */
}