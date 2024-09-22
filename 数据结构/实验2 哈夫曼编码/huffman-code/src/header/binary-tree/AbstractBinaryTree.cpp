#include "AbstractBinaryTree.hpp"

/**
* @brief 删除以p为根节点的二叉树
* @param p 二叉树的根节点地址
*/
template <typename Elem, typename Position>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
delete_tree(Position& p)
{
    if (p != null())
    {
        delete_tree(lchild(p));
        delete_tree(rchild(p));
        delete_node(p);
        p = null();
    }
}

/**
 * @brief 判断二叉树是否为完全二叉树
 * @param p 二叉树的根节点地址
 * @return true，如果以p为根节点的二叉树为完全二叉树
*/
template <typename Elem, typename Position>
bool BinaryTree::AbstractBinaryTree<Elem, Position>::complete(Position p)
{
    // 计数器，记录在层序遍历中，遍历到的节点的序号
    // 根节点为1，根节点的左孩子为2，根节点的右孩子为3，以此类推
    int count = 0;

    // last_elem 为最后一个出现的非空节点的序号
    // first_null 为第一个出现的空节点的序号
    int last_elem = -1, first_null = INT_MAX;

    // 求解 last_elem 与 first_null
    _lever_order_for_each(
        // 遍历起点
        p,

        // 遍历到非空节点，更新 last_elem
        [&](Elem){last_elem = std::max(last_elem, ++count);},

        // 遍历到空节点，更新 first_null （实际上只会更新一次）
        [&](){first_null = std::min(first_null, ++count);}
    );

    // 层序遍历中 最后一个出现的非空节点 位于 第一个出现的空节点 之前， 即为完全二叉树
    return (last_elem + 1 == first_null);
}

/**
 * @brief 计算二叉树的宽度，非递归
 * @param p 二叉树的根节点，默认为该树的根节点
 * @return 以p为根节点的二叉树的宽度
*/
template <typename Elem, typename Position>
int BinaryTree::AbstractBinaryTree<Elem, Position>::width(Position p)
{
    // 存放每层节点数的vector
    std::vector<int> arr(16, 0);

    // 计数器，计算 在层序遍历中 遍历到的节点序号
    unsigned int count = 0;

    // 临时函数对象，计算以2为底的对数
    auto log_2 = ([](unsigned int num){
        int res = 0;
        while ((num >>= 1) > 0)
            ++res;
        return res;
    });
    
    // 计算每层的节点数
    _lever_order_for_each(
        root(),
        [&](Elem){++arr.at(log_2(++count));}, 
        [&](){++count;}
    );

    // 计算每层节点数的最大值
    int width = -1;
    for (auto cnt: arr)
    {
        width = std::max(width, cnt);
    }
    return width;
}

/**
 * @brief 计算二叉树的深度，递归求解
 * @return 该二叉树的深度
*/
template <typename Elem, typename Position>
int BinaryTree::AbstractBinaryTree<Elem, Position>::depth(Position p)
{
    if (p == null())
        return 0;
    else
        return 1 + std::max(depth(lchild(p)), depth(rchild(p)));
}

/**
 * @brief 根据先序遍历序列建立二叉树
 * @param in 输入流的来源
 * @param separator 每项之间的分割符（可为\0）
 * @param placeholder 空节点的占位字符（不可为\0）
*/
template <typename Elem, typename Position>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
create(std::istream& in, char separator, char placeholder)
{
    if (!empty())
        delete_tree(root());

    _create(in, root(), separator, placeholder);
}

template <typename Elem, typename Position>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
show(std::ostream& out)
{
    std::vector<std::pair<std::string, std::string>> buf;
    _show(buf, root(), 0);

    for (int i = buf.size() - 1; i >= 0; i--)
    {
        out << buf[i].first << buf[i].second << std::endl;
    }    
}




template <typename Elem, typename Position>
int BinaryTree::AbstractBinaryTree<Elem, Position>::
_show(std::vector<std::pair<std::string, std::string>>& buf, Position p, int depth)
{
    // 记录以p为根节点的树，的左子树，的最左侧在buf中对应的行号
    // 注意，该算法采用中序遍历，越左侧的节点越先访问，故 越“左”对应着行号越“小”
    int l_tree_left = buf.size();

    // 分别记录：左子树根节点所在行，p节点所在行，右子树根节点所在行
    int l_tree = -1, r_tree = -1, this_tree;

    // p节点对应数据
    std::string this_data;

    if (typeid(Elem) == typeid(char))
        this_data = std::string(1, data(p));
    else
        this_data = std::to_string(data(p));

    // 记录p节点对应数据在打印后的长度
    int this_data_length = this_data.size();

    // 准备好与左右子树相连的长横线
    std::string vertical_line;
    for (int i = 0; i < this_data_length; ++i)
        vertical_line += "─";

    // pair中，第一个分量存储前缀信息（空格，连接线），第二个分量存储数据

    // 中序遍历
    if (lchild(p) != null())
        l_tree = _show(buf, lchild(p), depth + 1);
    
    buf.push_back(std::make_pair("", this_data));
    this_tree = buf.size() - 1;

    if (rchild(p) != null())
        r_tree = _show(buf, rchild(p), depth + 1);

    // 记录以p为根节点的树，的右子树，的最右侧在buf中对应的行号
    int r_tree_right = buf.size() - 1;
    
    if (l_tree != -1)
    // 如果存在左子树
    {
        // 对左子树的左侧追加空格
        for (int i = l_tree_left; i <= l_tree - 1; ++i)
            buf[i].first = std::string(this_data_length + 2, ' ') + buf[i].first;

        // 注意，该算法采用中序遍历，越左侧的节点越先访问，故 越“左”对应着行号越“小”
        // 与左子树连接的折线与横线（横线长度应与p节点的数据长度相适应）
        buf[l_tree].first = "╰" + vertical_line + "╴" + buf[l_tree].first;

        // 与左子树连接的竖线，以及对应长度的空格（空格长度应与p节点的数据长度相适应）
        for (int i = l_tree + 1; i < this_tree; ++i)
            buf[i].first = "│" + std::string(this_data_length + 1, ' ') + buf[i].first;
    }
        
    if (r_tree != -1)
    // 如果存在右子树
    {
        // 与右子树连接的竖线，以及对应长度的空格（空格长度应与p节点的数据长度相适应）
        for (int i = this_tree + 1; i <= r_tree - 1; ++i)
            buf[i].first = "│" + std::string(this_data_length + 1, ' ') + buf[i].first;

        // 与右子树连接的折线与横线（横线长度应与p节点的数据长度相适应）
        buf[r_tree].first = "╭" + vertical_line + "╴" + buf[r_tree].first;

        // 对右子树的右侧追加空格
        for (int i = r_tree + 1; i <= r_tree_right; ++i)
            buf[i].first = std::string(this_data_length + 2, ' ') + buf[i].first;
    }
    
    // 返回p节点所在行
    return this_tree;
}

template <typename Elem, typename Position>
void BinaryTree::AbstractBinaryTree<Elem, Position>::
_create(std::istream& in, Position& p, char separator, char placeholder)
{
    // 防止死循环
    if (in.eof())
        return;
    
    // 销毁分隔符
    while (in.peek() == separator)
        in.get();

    if (in.peek() != placeholder)
    // 不为占位符
    {
        Elem data;
        in >> data;
        p = new_node();

        // 先创建自己
        this->data(p) = data;
        // 再创建左孩子
        _create(in, lchild(p), separator, placeholder);
        // 最后创建右孩子 （先序）
        _create(in, rchild(p), separator, placeholder);
    }
    else
    // 为占位符，设为空指针
    {
        in.get();
        p = null();
    }   
}