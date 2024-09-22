## BinaryTree

本人数据结构课程的作业
使用C++实现的动态/静态二叉链表存储的二叉树模版

Project for DSA course.
Binary tree template implemented by C++.

## 模版类设计 Template class design

#### 总览 Overview

```
└──> AbstractBinaryTree (Abstract) // 抽象二叉树类
        │
        ├──> DynamicBinaryTree // 动态二叉树类
        │
        └──> StaticBinaryTree  // 静态二叉树类

───> DynamicNode // 动态二叉节点类
───> StaticNode  // 静态二叉节点类
```

#### 成员 Members

```
p.s. " = 0" 代表着纯虚函数 (pure virtual func)
└──> AbstractLinearList<Elem, Position>
        │
        │   [public:]
        ├── root = 0         // 获取指向根节点的指针
        ├── lchild = 0       // 获取指针指向节点的左孩子指针域的引用
        ├── rchild = 0       // 获取指针指向节点的右孩子指针域的引用
        ├── data = 0         // 获取指针指向节点的数据域的引用
        ├── empty = 0        // 判断该二叉树是否为空树
        ├── null = 0         // 返回空指针
        ├── new_node = 0     // 申请新节点
        ├── delete_node = 0  // 删除节点
        │
        ├── delete_tree      // 删除以p为根节点的二叉树
        ├── complete         // 判断二叉树是否为完全二叉树
        ├── width            // 计算二叉树的宽度，非递归
        ├── depth            // 计算以p为根节点的二叉树的深度，递归求解
        ├── show             // 打印二叉树
        ├── create           // 根据先序遍历序列建立二叉树
        ├── save             // 保存二叉树
        ├── for_each         // 遍历二叉树
        ├── for_each_no_rec  // 遍历二叉树，但为非递归实现版本
        │
        ├──> DynamicBinaryTree<Elem> : AbstractBinaryTree<Elem, DynamicNode<Elem>*>
        │        │
        │        │   [private:]
        │        ├── DynamicNode<Elem>* _root   // 指向根节点的指针
        │        │
        │        │   [public:]
        │        └── ...(8 overwrites)
        │
        └──> StaticBinaryTree<Elem> : AbstractBinaryTree<Elem, int>
                 │
                 │   [private:]
                 ├── int _root   // 指向根节点的指针
                 │
                 ├── StaticNode<Elem> *space  // 空闲空间池，由所有同类型静态二叉树类共享
                 ├── bool space_exist         // 判断空间池是否存在，默认值为0
                 ├── int space_ptr            // 空间池指针，用于管理空间
                 ├── int space_size           // 空间池的大小
                 │
                 │   [public:]
                 ├── ...(8 overwrites)
                 │
                 ├── init_space   // 初始化空间池
                 ├── clear_space  // 清空空间池
                 └── show_space   // 展示静态链表空间池

└──> DynamicNode<Elem> // 动态二叉节点类
        │
        ├── [public:]
        ├── Elem data
        ├── DynamicNode<Elem> *lchild
        └── DynamicNode<Elem> *rchild

└──> StaticNode<Elem>  // 静态二叉节点类
        │
        ├── [public:]
        ├── Elem data
        ├── DynamicNode<Elem> *lchild
        └── DynamicNode<Elem> *rchild

```