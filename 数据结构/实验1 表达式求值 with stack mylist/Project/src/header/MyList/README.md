# MyList

本人数据结构课程的作业，也是第一次用git/github，还请多多指教
使用C++实现的各种线性表模版

---

## 使用 Usage

直接包含头文件，即 `#include "MyList.hpp"` 即可，也可根据实际需要包含特定头文件

---

## 模版类设计 Template class design
#### 总览 Overview
```
└--> AbstractLinearList (Abstract) // 抽象线性表类
        |
        ├--> SeqList // 顺序表类
        |
        └--> AbstractLinkList (Abstract) // 抽象链表类
                |
                ├--> DynamicLinkList // 动态链表类
                |
                └--> StaticLinkList // 静态链表类

---> DynamicNode // 动态单向节点类
---> StaticNode  // 静态单向节点类
---> Stack       // 栈类（顺序表实现）
---> Queue       // 队列类（用带头结点的单向链表实现）
```
#### 逻辑 Logics
- 顺序表下标从0开始，`begin()`指向第一个元素，`end()`指向最后一个元素的下一个位置
- 链表带头节点，`begin()`指向头结点，`end()`指向最后一个数据节点
- 对链表而言，`.at(p)`等价于`p->next->data`
#### 成员 Members
```
p.s. " = 0" 代表着纯虚函数 (pure virtual func)
└--> AbstractLinearList<Elem, Position>
        |
        ├-- [public:]
        ├-- at = 0           // 返回p位置对应元素的引用
        ├-- insert = 0       // 在线性表中插入元素
        ├-- remove = 0       // 在线性表中删除元素
        ├-- prior = 0        // 返回指定位置的前驱
        ├-- next = 0         // 返回指定位置的指针域的值（即后继）
        ├-- begin = 0        // 返回表头
        ├-- end = 0          // 返回表尾
        ├-- empty = 0        // 判断是否为空表
        ├-- clear = 0        // 清空列表
        ├-- null = 0         // 返回空Position
        ├-- length = 0       // 返回当前线性表长度
        ├-- operator[]
        ├-- push_back (3 overloads)  // 向线性表尾部添加元素
        ├-- push_front       // 向线性表头部添加元素
        ├-- locate           // 查找元素出现第一位置
        ├-- traverse         // 遍历输出线性表全部成员
        ├-- remove_elem      // 删除线性表中所有给定元素
        ├-- remove_duplicate // 对排序好的线性表，删除所有重复元素
        ├-- for_each         // 对线性表中所有元素，按顺序传入func执行操作
        |
        ├--> SeqList<Elem> : AbstractLinearList<Elem, int>
        |        |
        |        ├-- [private:]
        |        ├-- int used_len     // 已经使用的长度
        |        ├-- int malloc_len   // 申请内存的长度
        |        ├-- Elem* head_ptr   // 申请顺序表数组地址的指针
        |        |
        |        ├-- [public:]
        |        ├-- ...(11 overwrites)
        |        ├-- extend       // 将数组增长len与现有长度一半的最大值的长度
        |        ├-- try_extend   // 尝试向数组增加len个元素，如果超出现有长度，调用extend
        |        ├-- reverse      // 顺序表就地倒置
        |        ├-- cylic_move   // 顺序表循环移动k位，向左为正
        |        └-- merge        // 对排序好的两个顺序表进行合并
        |
        └--> AbstractLinkList<Elem, Position> : AbstractLinearList<Elem, Position>
                 |
                 ├-- [public:]
                 ├-- data = 0        // 返回p指针指向节点的数据的引用
                 ├-- _next = 0       // 返回指定位置的指针域的引用（即后继）
                 ├-- begin = 0       // 返回表头
                 ├-- null = 0        // 返回空指针
                 ├-- newNode = 0     // 申请节点空间，返回节点的地址
                 ├-- deleteNode = 0  // 释放节点空间
                 |
                 |   (9 overwrites)
                 ├-- next    // 返回指定位置的指针域的值（即后继）
                 ├-- at      // 返回p指针所指向下一个节点的数据的引用
                 ├-- prior   // 返回指定位置的前驱
                 ├-- end     // 返回表尾
                 ├-- empty   // 判断是否为空表
                 ├-- clear   // 清空列表
                 ├-- length  // 返回当前链表长度
                 ├-- insert  // 在链表中插入元素
                 ├-- remove  // 删除元素
                 |
                 ├-- reverse     // 链表就地倒置
                 ├-- cylic_move  // 链表表循环移动k位，向左为正
                 ├-- merge       // 对排序好的两个链表进行合并
                 |
                 ├--> DynamicLinkList<Elem> : AbstractLinkList<Elem, DynamicNode<Elem>*>
                 |       |
                 |       ├-- [private:]
                 |       ├-- DynamicNode<Elem>* head_ptr  // 链表头指针
                 |       |
                 |       ├-- [public:]
                 |       └-- ...(6 overwrites)
                 |
                 └--> StaticLinkList<Elem> : AbstractLinkList<Elem, int>
                         |
                         ├-- [private:]
                         ├-- int head_ptr  // 链表头指针
                         |
                         ├-- static StaticNode<Elem> *space // 空闲空间池，由所有同类型静态链表类共享
                         ├-- static bool space_exist        // 判断空间池是否存在，默认值为0
                         ├-- static int space_ptr           // 空间池指针，用于管理空间
                         ├-- static int space_size          // 空间池的大小
                         |
                         ├-- [public:]
                         ├-- ...(6 overwrites)
                         |
                         ├-- static initSpace    // 对空间池进行初始化
                         ├-- static clearSpace   // 清空空间池
                         └-- static showSpace    // 展示静态链表空间池

└--> DynamicNode<Elem> // 动态单向节点类
        |
        ├-- [public:]
        ├-- Elem data
        └-- DynamicNode<Elem> *next

└--> StaticNode<Elem> // 静态单向节点类
        |
        ├-- [public:]
        ├-- Elem data
        └-- int next
                 
└--> Stack<Elem>
        |
        ├-- [private:]
        ├-- SeqList<Elem>* arr
        |
        ├-- [public:]
        ├-- push      // 入栈
        ├-- pop       // 出栈
        ├-- top       // 栈顶元素
        ├-- empty     // 是否为空
        ├-- size      // 栈大小
        └-- traverse  // 遍历元素输出，以separator为分隔符

└--> Queue<Elem>
        |
        ├-- [private:]
        ├-- DynamicLinkList<Elem>* list
        ├-- DynamicNode<Elem>* end
        |
        ├-- [public:]
        ├-- push      // 尾插法，在队尾插入元素
        ├-- pop       // 从队头弹出元素
        ├-- front     // 读取队头元素
        ├-- empty     // 判断队列是否为空
        ├-- size      // 查看队列元素个数
        └-- traverse  // 遍历元素输出，以separator为分隔符

```

---

## 项目结构 Project structure

```
├--README.md
└--src // 源代码目录
    ├--AbstractLinearList.cpp
    ├--AbstractLinearList.hpp
    ├--AbstractLinkList.cpp
    ├--AbstractLinkList.hpp
    ├--DynamicLinkList.cpp
    ├--DynamicLinkList.hpp
    ├--MyList.hpp
    ├--Queue.cpp
    ├--Queue.hpp
    ├--SeqList.cpp
    ├--SeqList.hpp
    ├--Stack.cpp
    ├--Stack.hpp
    ├--StaticLinkList.cpp
    ├--StaticLinkList.hpp
    |
    └--test.cpp // 测试文件
```
