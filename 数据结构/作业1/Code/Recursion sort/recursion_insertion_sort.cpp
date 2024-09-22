#ifndef INSERTION_SORT_CPP_INCLUDED
#define INSERTION_SORT_CPP_INCLUDED

template <typename T> void insertion_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	if (len <= 1)
		return;
	
	insertion_sort(arr, len - 1, cmp);
	
	T temp = arr[len - 1];
	int i = len - 2;
	while (cmp(temp, arr[i]) && i >= 0)
	{
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = temp;
}

#endif
