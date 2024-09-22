#ifndef BUBBLE_SORT_CPP_INCLUDED
#define BUBBLE_SORT_CPP_INCLUDED

template <typename T> void bubble_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j < len - 1 - i; j++)
			if (cmp(arr[j + 1], arr[j]))
				my_swap(arr[j], arr[j + 1]);
}

#endif
