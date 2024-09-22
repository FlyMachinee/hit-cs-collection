#ifndef BUBBLE_SORT_CPP_INCLUDED
#define BUBBLE_SORT_CPP_INCLUDED

template <typename T> void bubble_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	if (len <= 1)
		return;
	
	bool no_swap = true;

	for (int i = 0; i < len - 1; i++)

		if (cmp(arr[i + 1], arr[i]))
		{
			my_swap(arr[i], arr[i + 1]);
			no_swap = false;
		}
	
	if (no_swap)
		return;
	else
		bubble_sort(arr, len - 1, cmp);
}

#endif
