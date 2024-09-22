#ifndef HEAP_SORT_CPP_INCLUDED
#define HEAP_SORT_CPP_INCLUDED

template <typename T> void heapify (T* arr, int len, int father, bool (*cmp)(const T &a, const T &b))
{
	int child = father * 2 + 1;
	while (child < len)
	{
		if (child + 1 < len && cmp(arr[child], arr[child + 1]))
			child++;

		if (cmp(arr[child], arr[father]))
			return;
		else
		{
			my_swap(arr[child], arr[father]);
			father = child;
			child = father * 2 + 1;
		}
	}
}

template <typename T> void heap_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	for (int i = (len - 1) / 2; i >= 0; i--)
		heapify(arr, len, i, cmp);

	for (int i = len - 1; i >= 0; i--)
	{
		my_swap(arr[0], arr[i]);
		heapify(arr, i, 0, cmp);
	}
}

#endif

