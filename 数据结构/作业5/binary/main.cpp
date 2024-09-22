#include <iostream>
#include ".\src\BinarySearch"
#include ".\src\BinarySearchTree"

int main()
{
    system("chcp 65001"); // set terminal to UTF-8
    int arr[] = { 1, 1, 2, 3, 4, 4, 5, 5, 7, 7, 7, 8, 8, 9, 9, 9, 9, 10 };
    int* first = ::My::lower_bound_rec(arr, arr + 18, 7, std::less<int>());
    int* last = ::My::upper_bound_rec(arr, arr + 18, 7, std::less<int>());
    std::cout << "7: [" << first - arr << ", " << last - arr << ')' << std::endl;
    first = ::My::lower_bound_rec(arr, arr + 18, 9, std::less<int>());
    last = ::My::upper_bound_rec(arr, arr + 18, 9, std::less<int>());
    std::cout << "9: [" << first - arr << ", " << last - arr << ')' << std::endl;
    return 0;
}