#include <iostream>
#include <algorithm>
#include <time.h>
#include "..\src\BinarySearch"
#include "..\src\BinarySearchTree"

template <typename Val, class ForwardIter>
int lower_bound_search_len(ForwardIter first, ForwardIter last, Val key) {
    int ret = 0;
    while (first < last) {
        ForwardIter mid = first + (last - first) / 2;
        if (++ret, *mid < key)
            first = mid + 1;
        else
            last = mid;
    }
    return ret;
}

int main()
{
    system("chcp 65001"); // set terminal to UTF-8
    
    int data_sorted[1024], data_unsorted[1024];
    for (int i = 0; i < 1024; ++i)
        data_unsorted[i] = data_sorted[i] = 2 * i + 1;
    srand(time(0));
    std::random_shuffle(data_unsorted, data_unsorted + 1024);

    int data_fail[1025];
    for (int i = 0; i < 1025; ++i)
        data_fail[i] = 2 * i;

    BinaryTree::BST<int> tree_sorted, tree_unsorted;
    for (int i = 0; i < 1024; ++i) {
        tree_sorted.insert(data_sorted[i]);
        tree_unsorted.insert(data_unsorted[i]);
    }

    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 1024; ++i) {
        sum1 += tree_sorted.search_len(data_sorted[i]);
        sum2 += tree_unsorted.search_len(data_unsorted[i]);
    }
    std::cout << "tree_sorted ASL success: " << sum1 / 1024.0 << std::endl;
    std::cout << "tree_unsorted ASL success: " << sum2 / 1024.0 << std::endl;

    sum1 = sum2 = 0;
    for (int i = 0; i < 1025; ++i) {
        sum1 += tree_sorted.search_len(data_fail[i]);
        sum2 += tree_unsorted.search_len(data_fail[i]);
    }
    std::cout << "tree_sorted ASL fail: " << sum1 / 1025.0 << std::endl;
    std::cout << "tree_unsorted ASL fail: " << sum2 / 1025.0 << std::endl;

    sum1 = 0;
    for (int i = 0; i < 1024; ++i)
        sum1 += lower_bound_search_len(data_sorted, data_sorted + 1024, data_sorted[i]);
    std::cout << "lower_bound ASL success: " << sum1 / 1024.0 << std::endl;

    sum2 = 0;
    for (int i = 0; i < 1025; ++i)
        sum2 += lower_bound_search_len(data_sorted, data_sorted + 1024, data_fail[i]);
    std::cout << "lower_bound ASL fail: " << sum2 / 1025.0 << std::endl;
    return 0;
}