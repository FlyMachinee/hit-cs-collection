#include "SeqList.hpp"

//构造函数
template <typename Elem>
SeqList<Elem>::SeqList(int len)
{
    used_len = 0;
    malloc_len = (len >= 0 ? len : 0);
    head_ptr = (len >= 0 ? new Elem[malloc_len] : nullptr);
}

//析构函数
template <typename Elem>
SeqList<Elem>::~SeqList()
{
    if (head_ptr != nullptr)
    {
        delete[] head_ptr;
        head_ptr = nullptr;
    }
}

//返回p位置对应元素的引用
template <typename Elem>
Elem& SeqList<Elem>::at(int p) const
{
    if (p >= 0 && p < used_len)
        return head_ptr[p];
    else
        throw std::out_of_range("Invalid index");
}

//在顺序表中插入元素
template <typename Elem>
void SeqList<Elem>::insert(const Elem& obj, int p)
{
    if (p >= 0 && p <= used_len)
    {
        try_extend(1);
        
        //将第p及之后的元素向后移动一位
        for (int i = used_len; i > p; i--)
            head_ptr[i] = head_ptr[i - 1];

        //将obj插入到head_ptr中第p个位置
        head_ptr[p] = obj;

        used_len++;
    }
    else
        throw std::out_of_range("Invalid index");
}

template <typename Elem>
void SeqList<Elem>::remove(int p)
{
    if (p >= 0 && p < used_len)
    {
        //将第p之后的元素向前移动一位
        for (int i = p; i < used_len - 1; i++)
            head_ptr[i] = head_ptr[i + 1];
        
        used_len--;
    }
    else
        throw std::out_of_range("Invalid index");
}

//返回指定位置的前驱
template <typename Elem>
int SeqList<Elem>::prior(int p) const
{
    if (p > 0 && p <= used_len)
        return p - 1;
    else 
        return null();
}

//返回指定位置的后继
//！！！在顺序表中禁止使用后继作为左值！！！
template <typename Elem>
int SeqList<Elem>::next(int p) const
{
    if (p >= 0 && p < used_len)
        return p + 1;
    else 
        return null();
}

//返回表头
template <typename Elem>
int SeqList<Elem>::begin() const
{
    return 0;
}

//返回表尾
template <typename Elem>
int SeqList<Elem>::end() const
{
    return used_len;
}

//判断是否为空表
template <typename Elem>
bool SeqList<Elem>::empty() const
{
    return used_len == 0;
}

//清空列表
template <typename Elem>
void SeqList<Elem>::clear()
{
    used_len = 0;
}

//返回空下标
template <typename Elem>
int SeqList<Elem>::null() const
{
    return -1;
}

//返回当前数组长度
template <typename Elem>
int SeqList<Elem>::length() const
{
    return used_len;
}

//将数组增长len与现有长度一半的最大值的长度
template <typename Elem>
void SeqList<Elem>::extend(int len)
{
    if (len > 0)
    {
        //以16为基本单位，现有长度一半对比，申请内存
        malloc_len += std::max((len + 15) / 16 * 16, malloc_len / 2);

        Elem* new_head = new Elem[malloc_len];
        if (NULL == new_head)
        {
            std::cout << "Unable to extend the sequence list" << std::endl;
            throw std::bad_alloc();
        }

        //将原数组元素拷贝到新数组
        for (int i = 0; i < used_len; ++i)
            new_head[i] = head_ptr[i];
        
        //释放原数组
        delete[] head_ptr;
        head_ptr = new_head;        
    }
}

//尝试向数组增加len个元素，如果超出现有长度，调用extend方法
template <typename Elem>
void SeqList<Elem>::try_extend(int len)
{
    if (used_len + len > malloc_len)
        extend(len);
}

//顺序表就地倒置
template <typename Elem>
void SeqList<Elem>::reverse()
{
    if (!empty())
        //双指针交换
        for (int i = 0, j = used_len - 1; i < j; i++, j--)
            std::swap(at(i), at(j));
}

//顺序表循环移动k位，向左为正
template <typename Elem>
void SeqList<Elem>::cylic_move(int k)
{
    if (!empty())
    {
        k = ((k % used_len) + used_len) % used_len;
        // 求 k 对 len 在数学上的余数
        // e.g. 5 % 2 = 1, 7 % 4 = 3, -7 % 4 = 1

        //循环左移k位
        while (k > 0)
        {   
            //将表头元素复制, 追加至表尾
            this->push_back(at(0));
            //删除表头元素
            remove(0);
            k--;
        }
    }
}

//对排序好的两个顺序表进行合并
template <typename Elem>
void SeqList<Elem>::merge(const SeqList<Elem>& list2, bool (*cmp)(const Elem&, const Elem&))
{
    //对本对象扩容，使之能够装下list2
    try_extend(list2.used_len);
    
    //给本对象起别名list1
    SeqList<Elem>& list1 = *this;

    //将两个顺序表的元素根据cmp函数倒序复制到list1中
	int i = used_len - 1, j = list2.used_len - 1, k = used_len + list2.used_len - 1;
	while (i >= 0 && j >= 0)
	{
		if (cmp(list1[i], list2[j]))
			list1[k--] = list2[j--];
		else
			list1[k--] = list1[i--];
	}

    //将list2剩下的元素倒序复制至list1
	while (j >= 0)
		list1[k--] = list2[j--];

    used_len += list2.used_len;
}